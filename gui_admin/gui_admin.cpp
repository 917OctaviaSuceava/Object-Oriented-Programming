#include "gui_admin.h"
#include <QDebug>

AdminGUI::AdminGUI(int f, Service &s, QWidget *parent): QDialog{parent}, service{s}
{
    format = f;
    undoStack = new QUndoStack(this);

    this->service.load(R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\repo.txt)");
    this->show_window();
    this->connect_signals_slots();
    this->populate_list();
}

AdminGUI::~AdminGUI()
{

}


void AdminGUI::show_window()
{
    QWidget *window = new QWidget{this};
    this->movies_list = new QListWidget{};
    this->movies_list->setSelectionMode(QAbstractItemView::SingleSelection);
    window->resize(1200,600);
    window->setWindowTitle("Administrator Mode");

    QVBoxLayout *layout = new QVBoxLayout(window);

    QWidget* movie_data = new QWidget{};
    QFormLayout *form_layout = new QFormLayout{movie_data};
    this->title = new QLineEdit{};
    this->year= new QLineEdit{};
    this->likes = new QLineEdit{};
    this->genre = new QLineEdit{};
    this->trailer = new QLineEdit{};

    QLabel *title_label = new QLabel{"&TITLE: "};
    title_label->setBuddy(this->title);
    QLabel *year_label = new QLabel{"&YEAR: "};
    year_label->setBuddy(this->year);
    QLabel *likes_label = new QLabel{"&LIKES: "};
    likes_label->setBuddy(this->likes);
    QLabel *genre_label = new QLabel{"&GENRE: "};
    genre_label->setBuddy(this->genre);
    QLabel *trailer_label = new QLabel{"&TRAILER: "};
    trailer_label->setBuddy(this->trailer);

    form_layout->addRow(title_label, this->title);
    form_layout->addRow(year_label, this->year);
    form_layout->addRow(likes_label, this->likes);
    form_layout->addRow(genre_label, this->genre);
    form_layout->addRow(trailer_label, this->trailer);

    QWidget *buttons_widget = new QWidget{};
    QHBoxLayout *h_layout = new QHBoxLayout{buttons_widget};

    h_layout->addWidget(movie_data);

    QWidget *all_buttons = new QWidget{};
    QVBoxLayout *v_layout = new QVBoxLayout{all_buttons};

    this->add_movie = new QPushButton("ADD");
    this->delete_movie = new QPushButton("DELETE");
    this->update_movie = new QPushButton("UPDATE");

    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);

    QWidget *command_buttons = new QWidget{};
    QHBoxLayout *command_layout = new QHBoxLayout{command_buttons};
    command_layout->addWidget(add_movie);
    command_layout->addWidget(delete_movie);
    command_layout->addWidget(update_movie);
    /*
    h_layout->addWidget(this->add_movie);
    h_layout->addWidget(this->delete_movie);
    h_layout->addWidget(this->update_movie);*/

    QWidget *undo_redo = new QWidget{};
    QHBoxLayout *ur_layout = new QHBoxLayout{undo_redo};
    undo = new QPushButton("UNDO");
    redo = new QPushButton("REDO");
    undo->addAction(undoAction);
    redo->addAction(redoAction);

    ur_layout->addWidget(undo);
    ur_layout->addWidget(redo);

    v_layout->addWidget(command_buttons);
    v_layout->addWidget(undo_redo);

    h_layout->addWidget(all_buttons);

    layout->addWidget(this->movies_list);

    //layout->addWidget(movie_data);
    //layout->addWidget(all_buttons);
    layout->addWidget(buttons_widget);

}


void AdminGUI::connect_signals_slots()
{
    QObject::connect(this, &AdminGUI::movies_updated, this, &AdminGUI::populate_list);

    QObject::connect(this->delete_movie, &QPushButton::clicked, this, &AdminGUI::delete_button);
    QObject::connect(this->add_movie, &QPushButton::clicked, this, &AdminGUI::add_button);
    QObject::connect(this->update_movie, &QPushButton::clicked, this, &AdminGUI::update_button);

    QObject::connect(this->movies_list, &QListWidget::itemSelectionChanged, this, [this]() {this->item_changed(); });

    QObject::connect(this, SIGNAL(add_movie_signal(std::string,int,int,std::string,std::string)),
            this, SLOT(gui_add(std::string,int,int,std::string,std::string)));

    QObject::connect(this, SIGNAL(update_movie_signal(std::string,std::string,int,int,std::string,std::string)),
                     this, SLOT(gui_update(std::string,std::string,int,int,std::string,std::string)));
}

void AdminGUI::delete_button()
{
    int index = this->get_index();
    if (index < 0 || index >= service.get_elems().size())
        return;

    QString tr = this->trailer->text();

    //undoStack->push()

    service.service_delete(tr.toStdString(), R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\repo.txt)");
    emit movies_updated();
}

void AdminGUI::update_button()
{
    QString added_title = this->title->text();
    QString added_year = this->year->text();
    QString added_likes= this->likes->text();
    QString added_genre = this->genre->text();
    QString added_trailer = this->trailer->text();

    emit update_movie_signal(old_trailer, added_title.toStdString(), added_year.toInt(),
                             added_likes.toInt(), added_genre.toStdString(), added_trailer.toStdString());
}

void AdminGUI::gui_update(std::string tr, std::string added_title, int added_year, int added_likes, std::string added_genre, std::string added_trailer)
{

    service.service_update(tr, Movie{added_title, added_genre, added_year, added_likes, added_trailer},
                           R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\repo.txt)");
    emit movies_updated();
}

void AdminGUI::add_button()
{
    QString added_title = this->title->text();
    QString added_year = this->year->text();
    QString added_likes= this->likes->text();
    QString added_genre = this->genre->text();
    QString added_trailer = this->trailer->text();

    emit add_movie_signal(added_title.toStdString(), added_year.toInt(), added_likes.toInt(),
                          added_genre.toStdString(), added_trailer.toStdString());
}

void AdminGUI::gui_add(std::string title1, int year1, int likes1, std::string genre1, std::string trailer1)
{
    this->service.service_add(Movie{title1, genre1, year1, likes1, trailer1}, R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\repo.txt)");
    emit movies_updated();
}

int AdminGUI::get_index()
{
    if(this->movies_list->count() == 0)
        return -1;
    QModelIndexList index = this->movies_list->selectionModel()->selectedIndexes();

    if (index.size() == 0)
    {
        this->title->clear();
        this->genre->clear();
        this->likes->clear();
        this->trailer->clear();
        this->year->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void AdminGUI::item_changed()
{
    int id = this->get_index();
    if (id == -1)
        return;
    if (id >= this->service.get_elems().size())
        return;

    Movie movie = this->service.get_elems()[id];
    old_trailer = movie.get_trailer();

    this->title->setText(QString::fromStdString(movie.get_title()));
    this->likes->setText(QString::fromStdString(to_string(movie.get_likes())));
    this->year->setText(QString::fromStdString(to_string(movie.get_year())));
    this->genre->setText(QString::fromStdString(movie.get_genre()));
    this->trailer->setText(QString::fromStdString(movie.get_trailer()));
}

void AdminGUI::populate_list()
{
    //this->service.load(R"(C:\Users\Octavia\CLionProjects\untitled8\repo.txt)");
    if(movies_list->count() > 0)
        movies_list->clear();
    QFont f{"Verdana", 9};
    for(auto i: this->service.get_elems())
    {
        QString item = QString::fromStdString("TITLE: " + i.get_title() + " | " +
                                              "YEAR: " + to_string(i.get_year()) +
                                              " | " + "LIKES: " +
                                              to_string(i.get_likes()) + " | " +
                                              "GENRE: " +
                                              i.get_genre() + " | " +
                                              "TRAILER: " + i.get_trailer());
        QListWidgetItem* item1 = new QListWidgetItem{item};
        item1->setFont(f);
        movies_list->addItem(item1);
    }
    if(this->service.get_elems().size() > 0)
        movies_list->setCurrentRow(0);
}