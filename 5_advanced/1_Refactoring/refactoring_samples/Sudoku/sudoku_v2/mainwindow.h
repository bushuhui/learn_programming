#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMutex>
#include <QFileDialog>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QPainter>

#include <iostream>
#include <fstream>

#include "sudoku.h"

// extern data
// FIXME: this variable is only used in MainWindow, therefore can be a member variable of MainWindow
// update:done
//extern Sudoku new_game;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QPushButton *> Botton_list;

    //these fun are used to show the game
    void update_(Sudoku new_game);
    void Input_number(int input_number);

private slots:

    //these buttons are in the game control ,function is the same with its name
    void on_Newgame_clicked();
    void on_Computerplay_clicked();
    void on_Quit_clicked();
    void on_Save_clicked();
    void on_Load_clicked();
    void on_board_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);

    // these are buttons in the keypad ,to input numbers or delete numbers
    void on_keypad_clicked();
    void on_input_delete_clicked();
    void on_input_define_clicked();


    void updateTime();
    void on_B_time_clicked();

protected:
    // to get the keyboard order
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    Sudoku new_game;
    int input_number;
    QTimer * timer;
    QTime * TimeRecord;
    bool isStart;
};
#endif // MAINWINDOW_H
