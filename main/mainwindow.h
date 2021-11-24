#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Qt>
#include <QMainWindow>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QFrame>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton* administrator;
    QPushButton* user;
    QRadioButton *format1;
    QRadioButton *format2;
    int f;
    void init();
    void click_admin();
    void click_user();
    void click_html();
    void click_csv();
};
#endif // MAINWINDOW_H
