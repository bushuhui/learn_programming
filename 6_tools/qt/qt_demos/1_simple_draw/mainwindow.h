
#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMutex>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    QImage          *m_img;
};

