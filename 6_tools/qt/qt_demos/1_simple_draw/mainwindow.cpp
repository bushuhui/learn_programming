
#include <stdio.h>
#include <stdlib.h>

#include <QThread>
#include <QtGui>
#include <QDebug>

#include "mainwindow.h"



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // create background image
    int imgW = 800, imgH = 600;
    m_img = new QImage(imgW, imgH, QImage::Format_RGB888);
    m_img->fill(QColor(0xff, 0xff, 0xff));

    // set window properties
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    // set focus to self
    setFocus();
}


void MainWindow::timerEvent(QTimerEvent *event)
{

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QPainter    painter;

    // 'o' - random draw rectangles
    if( event->key() == Qt::Key_O ) {
        painter.begin(m_img);
        painter.setRenderHint(QPainter::Antialiasing, true);

        double      x1, y1, x2, y2, w, h;

        for(int i=0; i<1000; i++) {
            painter.setPen(QColor(rand()%255, rand()%255, rand()%255, rand()%255));

            x1 = rand() % 800; y1 = rand() % 600;
            x2 = rand() % 800; y2 = rand() % 600;
            w = x2 - x1;
            h = y2 - y1;
            painter.drawRect(x1, y1, w, h);
        }

        painter.end();
    }

    // 'c' - clean canvas
    if( event->key() == Qt::Key_C ) {
        m_img->fill(QColor(0xff, 0xff, 0xff));
    }

    // 'q' - quit the program
    if( event->key() == Qt::Key_Q ) {
        this->close();
    }

    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
}

void MainWindow::paintEvent(QPaintEvent * /* event */)
{
    QPainter    painter(this);

    // draw offline image to screen
    painter.drawImage(QPoint(0, 0), *m_img);
}
