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

void MainWindow::on_input_1_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 1;
        update_(new_game);
    }
}

void MainWindow::on_input_2_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 2;
        update_(new_game);
    }
}

void MainWindow::on_input_3_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 3;
        update_(new_game);
    }
}

void MainWindow::on_input_4_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 4;
        update_(new_game);
    }
}

void MainWindow::on_input_5_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 5;
        update_(new_game);
    }
}

void MainWindow::on_input_6_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 6;
        update_(new_game);
    }
}

void MainWindow::on_input_7_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 7;
        update_(new_game);
    }
}

void MainWindow::on_input_8_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 8;
        update_(new_game);
    }
}

void MainWindow::on_input_9_clicked()
{
    int x , y;
    x=new_game.location[0];
    y=new_game.location[1];
    if(new_game.sudokuboard[x][y].point_type == true){
        new_game.sudokuboard[x][y].value = 9;
        update_(new_game);
    }
}

