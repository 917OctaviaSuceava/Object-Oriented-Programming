#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "gui_admin.h"
#include "../gui_user/gui_user.h"
MainWindow::MainWindow(QWidget *parent): QWidget{parent}
{
    this->init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    QWidget *window = new QWidget{this};
    window->resize(300,300);
    window->setWindowTitle("Choose Mode");

    //QWidget *format = new QWidget{};
    QFont f{ "Courier New", 10 };
    QLabel *label = new QLabel(this);

    label->setText("Choose the format:");
    label->setFont(f);
    label->setAlignment(Qt::AlignCenter);
    this->format1 = new QRadioButton("HTML");
    this->format1->setFont(f);
    this->format2 = new QRadioButton("CSV");
    this->format2->setFont(f);

    QLabel *label1 = new QLabel(this);

    label1->setText("Choose the mode:");
    label1->setFont(f);
    label1->setAlignment(Qt::AlignCenter);

    this->administrator = new QPushButton("ADMINISTRATOR");
    this->administrator->setFont(f);
    this->user = new QPushButton("USER");
    this->user->setFont(f);

    QVBoxLayout *layout = new QVBoxLayout(window);
    layout->addWidget(label);
    layout->addWidget(format1);
    layout->addWidget(format2);
    layout->addWidget(label1);
    layout->addWidget(this->administrator);
    layout->addWidget(this->user);


    QObject::connect(this->administrator, &QPushButton::clicked, this, &MainWindow::click_admin);
    QObject::connect(this->user, &QPushButton::clicked, this, &MainWindow::click_user);
    QObject::connect(this->format1, &QPushButton::clicked, this, &MainWindow::click_html);
    QObject::connect(this->format2, &QPushButton::clicked, this, &MainWindow::click_csv);
}

void MainWindow::click_csv()
{
    f = 2;
}

void MainWindow::click_html()
{
    f = 1;
}

void MainWindow::click_admin()
{
    std::vector<Movie> movies;
    Repository repo{};

    FileRepo *file_repo;
    if(f == 1)
    {
      file_repo = new HTML;
    }
    else{
         file_repo = new CSV;
     }
    Service service{repo, *file_repo};

    AdminGUI m{f, service};
    m.show();

    m.setModal(true);
    m.exec();
}

void MainWindow::click_user()
{
    std::vector<Movie> movies;
    Repository user_repo{};
    //Repository admin_repo{};
    FileRepo *file_repo;
    if(f == 1) {
       file_repo = new HTML;
    }
    else{
         file_repo = new CSV;
    }
    Service user_service{user_repo, *file_repo};
    UserGUI m1{f, user_service};
    m1.setModal(true);
    m1.exec();
}
