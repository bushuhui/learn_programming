#include <QApplication>
#include <QtGui>

#include "mainwindow.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    // create main window
    MainWindow  win;
    win.setWindowTitle("Simpel Draw");
    //win.setFixedSize(800, 600);
    win.show();

    // begin Qt GUI loop
    app.exec();

    return 0;
}
