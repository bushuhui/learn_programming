#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

void MainWindow::on_input_delete_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 0;
        update_(new_game);
    }
}

void MainWindow::on_input_define_clicked()
{
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9 ; j ++){
            if(new_game.sudokuboard[i][j].point_type == true){
                new_game.sudokuboard[i][j].value = 0;
            }
        }
    }
    new_game.b_sign = false ;
    update_(new_game);
}

void MainWindow::Input_number(int input_number)
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
            new_game.sudokuboard[x][y].value = input_number;
    }
}

void MainWindow::on_keypad_clicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    QList <QPushButton *> Button_list;
    Button_list = ui -> groupBox_Keypad -> findChildren <QPushButton *>();

    for(int i = 0;i < Button_list.size() ;i ++){
        if( Button_list[i]->objectName() == btn->objectName()){
            Input_number(i - 1);// because the buttonlist include the "delete" and "clear" button;
            update_(new_game);
        }
    }
    isStart = false;
    on_B_time_clicked();
}
