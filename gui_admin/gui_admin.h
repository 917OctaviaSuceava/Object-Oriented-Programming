#ifndef GUI_ADMIN_H
#define GUI_ADMIN_H

#endif // GUI_ADMIN_H
//#include <QWidget>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QModelIndex>
#include <QUndoCommand>
#include <QUndoStack>
#include <QUndoView>
#include <QShortcut>
#include <QAction>
//#include "domain.h"
#include "../service/service.h"
class AdminGUI: public QDialog
{
    Q_OBJECT
public:
    //std::vector<Movie> movies,
    AdminGUI(int f, Service &s, QWidget *parent = 0);

    ~AdminGUI();

private:
    //std::vector<Movie> movies;
    Service service;
    int format;
    std::string old_trailer;

    QListWidget *movies_list;

    QPushButton *add_movie;
    QPushButton *delete_movie;
    QPushButton *update_movie;
    QPushButton *undo;
    QPushButton *redo;

    QLineEdit *title;
    QLineEdit *year;
    QLineEdit *likes;
    QLineEdit *genre;
    QLineEdit *trailer;

    QAction *undoAction = nullptr;
    QAction *redoAction = nullptr;

    QUndoStack *undoStack = nullptr;

    void show_window();
    void populate_list();
    int get_index();
    void item_changed();

    void connect_signals_slots();

signals:
    void movies_updated();
    void add_movie_signal(std::string title1, int year1, int likes1, std::string genre1, std::string trailer1);
    void update_movie_signal(std::string trailer_update, std::string title1, int year1, int likes1, std::string genre1, std::string trailer1);

public slots:
    void add_button();
    void delete_button();
    void gui_add(std::string title1, int year1, int likes1, std::string genre1, std::string trailer1);
    void gui_update(std::string trailer_update, std::string title1, int year1, int likes1, std::string genre1, std::string trailer1);
    void update_button();

};

