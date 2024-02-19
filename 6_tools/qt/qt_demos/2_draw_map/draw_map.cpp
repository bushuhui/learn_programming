/****************************************************************************
****************************************************************************/

#include <QApplication>
#include <QtGui>
#include <QMainWindow>

#include "map_viewer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // set random seed
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MapViewer *widget = new MapViewer;

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);
    mainWindow.show();

    return app.exec();
}
