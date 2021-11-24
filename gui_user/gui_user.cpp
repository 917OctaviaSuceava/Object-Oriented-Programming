#include "gui_user.h"

UserGUI::UserGUI(int &f, Service &s, QWidget *parent): QDialog{parent}, service{s}
{
    format = f;
    this->service.load(R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\repo.txt)");
    std::ofstream ofs;
    ofs.open(R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\watch_list.txt)", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    if(service.get_watch_list().size() > 0)
        service.get_watch_list().clear();
    this->show_window();
    this->connect_slots_signals();
    this->get_movies();
}

UserGUI::~UserGUI()
{

}

void UserGUI::connect_slots_signals()
{
    QObject::connect(this, &UserGUI::movies_updated, this, &UserGUI::update_watch_list);

    QObject::connect(seeUnfiltered, &QPushButton::clicked, this, &UserGUI::get_movies);
    QObject::connect(seeByGenre, &QPushButton::clicked, this, &UserGUI::see_by_genre);
    QObject::connect(addWatchList, &QPushButton::clicked, this, &UserGUI::add_to_watch_list);
    QObject::connect(deleteMovie,&QPushButton::clicked,this,&UserGUI::delete_user);
    QObject::connect(seeWatchList,&QPushButton::clicked,this,&UserGUI::see_in_format);

    QObject::connect(this, SIGNAL(add_to_watch_list_signal(std::string, int, int, std::string, std::string)),
                     this, SLOT(add(std::string, int, int, std::string, std::string)));
}

void UserGUI::show_window()
{
    QWidget *window = new QWidget{this};
    movies_list = new QListWidget{};
    watch_list = new QListWidget{};
    movies_list->setSelectionMode(QAbstractItemView::SingleSelection);
    watch_list->setSelectionMode(QAbstractItemView::SingleSelection);

    window->resize(1500,700);
    window->setWindowTitle("User Mode");
    seeByGenre = new QPushButton("SEE BY GENRE");
    //QPushButton *button2 = new QPushButton("See watch list");
    seeWatchList = new QPushButton("SEE IN FORMAT");
    addWatchList = new QPushButton("ADD TO WATCH LIST");
    deleteMovie = new QPushButton("DELETE FROM WATCH LIST");
    seeUnfiltered = new QPushButton("SEE INITIAL LIST");

    QWidget* movies_data = new QWidget{};
    QHBoxLayout *h_layout = new QHBoxLayout(movies_data);
    h_layout->addWidget(movies_list);
    h_layout->addWidget(watch_list);

    QVBoxLayout *layout = new QVBoxLayout(window);

    QWidget* movie_data = new QWidget{};
    QFormLayout *form_layout = new QFormLayout{movie_data};

    QLabel *genre_label = new QLabel{"&ENTER GENRE: "};
    this->genre = new QLineEdit{};
    genre_label->setBuddy(this->genre);
    form_layout->addRow(genre_label, this->genre);

    layout->addWidget(movies_data);
    layout->addWidget(movie_data);

    layout->addWidget(seeByGenre);
    layout->addWidget(seeWatchList);
    layout->addWidget(addWatchList);
    layout->addWidget(deleteMovie);
    layout->addWidget(seeUnfiltered);
}


int UserGUI::get_watch_list_index()
{
    if(this->watch_list->count() == 0)
        return -1;
    QModelIndexList index = this->watch_list->selectionModel()->selectedIndexes();
    int idx = index.at(0).row();
    return idx;
}

void UserGUI::see_in_format() const
{
    if(format == 1)
        ShellExecute(nullptr, "open", R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\watch_list.html)", nullptr, nullptr,
                     SW_SHOWNORMAL);
    else if(format == 2)
    {
        std::string f;
        std::string path=R"(C:\Users\Octavia\Documents\GitHub\a89-917OctaviaSuceava\watch_list.html)";
        f +=  "notepad \"" + path + "\"";
        system(f.c_str());
    }
}

void UserGUI::delete_user()
{
    int id = this->get_watch_list_index();
    if (id == -1)
        return;
    if (id >= this->service.get_watch_list().size())
        return;
    Movie movie = this->service.get_watch_list()[id];
    service.delete_from_watch_list(movie.get_trailer());

    emit movies_updated();
}

int UserGUI::get_index()
{
    if(this->movies_list->count() == 0)
        return -1;
    QModelIndexList index = this->movies_list->selectionModel()->selectedIndexes();
    int idx = index.at(0).row();
    return idx;
}

void UserGUI::add_to_watch_list()
{
    int id = this->get_index();
    if (id == -1)
        return;
    if (id >= filtered_movies.size())
        return;
    Movie movie = filtered_movies[id];
    emit add_to_watch_list_signal(movie.get_title(), movie.get_year(), movie.get_likes(),
                                  movie.get_genre(),movie.get_trailer());
}

void UserGUI::add(std::string title1, int year1, int likes1, std::string genre1, std::string trailer1)
{
    this->service.add_watch_list(Movie{title1, genre1, year1, likes1, trailer1},
                                 R"(C:\Users\Octavia\CLionProjects\untitled8\watch_list.txt)");

    emit movies_updated();
}

void UserGUI::update_watch_list()
{
    if(watch_list->count() > 0)
        watch_list->clear();
    QFont f{"Verdana", 9};
    for(auto i: this->service.get_watch_list())
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
        watch_list->addItem(item1);
    }
    if(watch_list->count() > 0)
        watch_list->setCurrentRow(0);
}

void UserGUI::see_by_genre()
{
    if(movies_list->count() > 0)
        movies_list->clear();
    QString g = genre->text();
    QFont f{"Verdana", 9};
    if(filtered_movies.size() > 0)
        filtered_movies.clear();
    for(auto i: this->service.get_elems())
    {
        if(i.get_genre() == g.toStdString())
        {
            filtered_movies.push_back(i);
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
    }
}


void UserGUI::get_unfiltered()
{
    if(movies_list->count() > 0)
        movies_list->clear();
    QFont f{"Verdana", 9};
    if(filtered_movies.size() > 0)
        filtered_movies.clear();
    for(auto i: this->service.get_elems())
    {
        filtered_movies.push_back(i);
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
    if(movies_list->count() > 0)
        movies_list->setCurrentRow(0);
}

void UserGUI::get_movies()
{
    if(movies_list->count() > 0)
        movies_list->clear();
    QFont f{"Verdana", 9};
    if(filtered_movies.size() > 0)
        filtered_movies.clear();
    for(auto i: this->service.get_elems())
    {
        filtered_movies.push_back(i);
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
    if(movies_list->count() > 0)
        movies_list->setCurrentRow(0);
}
