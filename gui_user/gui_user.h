#ifndef GUI_USER_H
#define GUI_USER_H

#endif // GUI_USER_H
#pragma once
#include <Windows.h>
#include <iostream>
#include <shellapi.h>
#include <cstdlib>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QDialog>
#include <QRadioButton>
#include "../service/service.h"
using namespace std;
class UserGUI: public QDialog
{
    Q_OBJECT
public:
    UserGUI(int &f, Service &s, QWidget *parent = 0);
    ~UserGUI();
private:
    std::vector<Movie> filtered_movies;
    Service service;
    int format;
    QListWidget *movies_list;
    QListWidget *watch_list;

    QLineEdit *genre;

    QPushButton *seeByGenre;
    QPushButton *seeWatchList;
    QPushButton *deleteMovie;
    QPushButton *seeUnfiltered;
    QPushButton *addWatchList;

    void show_window();
    void get_movies();
    void connect_slots_signals();

signals:
    void add_to_watch_list_signal(std::string title1, int year1, int likes1, std::string genre1, std::string trailer1);
    void movies_updated();
    void repo_updated();

public slots:
    void see_by_genre();
    void get_unfiltered();
    void add_to_watch_list();
    void add(std::string title1, int year1, int likes1, std::string genre1, std::string trailer1);

    int get_index();

    void update_watch_list();

    int get_watch_list_index();

    void delete_user();

    void see_in_format() const;


};
