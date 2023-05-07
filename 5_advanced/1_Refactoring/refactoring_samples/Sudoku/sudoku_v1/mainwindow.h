#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMutex>
#include <QFileDialog>

#include <iostream>
#include <fstream>

#include"sudoku.h"

// extern data
extern Sudoku new_game;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //these fun are used to show the game
    void update_numbers(Sudoku new_game);
    void update_background(Sudoku new_game);
    void update_(Sudoku new_game);

private slots:

    //these buttons are in the game control ,function is the same with its name
    void on_Newgame_clicked();
    void on_Computerplay_clicked();
    void on_Quit_clicked();
    void on_Save_clicked();
    void on_Load_clicked();


    //these buttons are in the board
    // the name means B_"which square"_"x_lab"_"y_lab"
    void on_B_1_0_0_clicked();
    void on_B_1_0_1_clicked();
    void on_B_1_0_2_clicked();
    void on_B_2_0_3_clicked();
    void on_B_2_0_4_clicked();
    void on_B_2_0_5_clicked();
    void on_B_3_0_6_clicked();
    void on_B_3_0_7_clicked();
    void on_B_3_0_8_clicked();
    void on_B_1_1_0_clicked();
    void on_B_1_1_1_clicked();
    void on_B_1_1_2_clicked();
    void on_B_2_1_3_clicked();
    void on_B_2_1_4_clicked();
    void on_B_2_1_5_clicked();
    void on_B_3_1_6_clicked();
    void on_B_3_1_7_clicked();
    void on_B_3_1_8_clicked();
    void on_B_1_2_0_clicked();
    void on_B_1_2_1_clicked();
    void on_B_1_2_2_clicked();
    void on_B_2_2_3_clicked();
    void on_B_2_2_4_clicked();
    void on_B_2_2_5_clicked();
    void on_B_3_2_6_clicked();
    void on_B_3_2_7_clicked();
    void on_B_3_2_8_clicked();
    void on_B_4_3_0_clicked();
    void on_B_4_3_1_clicked();
    void on_B_4_3_2_clicked();
    void on_B_5_3_3_clicked();
    void on_B_5_3_4_clicked();
    void on_B_5_3_5_clicked();
    void on_B_6_3_6_clicked();
    void on_B_6_3_7_clicked();
    void on_B_6_3_8_clicked();
    void on_B_4_4_0_clicked();
    void on_B_4_4_1_clicked();
    void on_B_4_4_2_clicked();
    void on_B_5_4_3_clicked();
    void on_B_5_4_4_clicked();
    void on_B_5_4_5_clicked();
    void on_B_6_4_6_clicked();
    void on_B_6_4_7_clicked();
    void on_B_6_4_8_clicked();
    void on_B_4_5_0_clicked();
    void on_B_4_5_1_clicked();
    void on_B_4_5_2_clicked();
    void on_B_5_5_3_clicked();
    void on_B_5_5_4_clicked();
    void on_B_5_5_5_clicked();
    void on_B_6_5_6_clicked();
    void on_B_6_5_7_clicked();
    void on_B_6_5_8_clicked();
    void on_B_7_6_0_clicked();
    void on_B_7_6_1_clicked();
    void on_B_7_6_2_clicked();
    void on_B_8_6_3_clicked();
    void on_B_8_6_4_clicked();
    void on_B_8_6_5_clicked();
    void on_B_9_6_6_clicked();
    void on_B_9_6_7_clicked();
    void on_B_9_6_8_clicked();
    void on_B_7_7_0_clicked();
    void on_B_7_7_1_clicked();
    void on_B_7_7_2_clicked();
    void on_B_8_7_3_clicked();
    void on_B_8_7_4_clicked();
    void on_B_8_7_5_clicked();
    void on_B_9_7_6_clicked();
    void on_B_9_7_7_clicked();
    void on_B_9_7_8_clicked();
    void on_B_7_8_0_clicked();
    void on_B_7_8_1_clicked();
    void on_B_7_8_2_clicked();
    void on_B_8_8_3_clicked();
    void on_B_8_8_4_clicked();
    void on_B_8_8_5_clicked();
    void on_B_9_8_6_clicked();
    void on_B_9_8_7_clicked();
    void on_B_9_8_8_clicked();


    // these are buttons in the keypad ,to input numbers or delete numbers
    void on_input_1_clicked();
    void on_input_2_clicked();
    void on_input_3_clicked();
    void on_input_4_clicked();
    void on_input_5_clicked();
    void on_input_6_clicked();
    void on_input_7_clicked();
    void on_input_8_clicked();
    void on_input_9_clicked();
    void on_input_delete_clicked();
    void on_input_define_clicked();


protected:
    // to get the keyboard order
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
