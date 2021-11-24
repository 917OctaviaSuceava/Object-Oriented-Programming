#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include "../gui_admin/gui_admin.h"
#include "../gui_user/gui_user.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
