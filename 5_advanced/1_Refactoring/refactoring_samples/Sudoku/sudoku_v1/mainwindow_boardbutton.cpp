#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

// get which one is choose

void MainWindow::on_B_1_0_0_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 0;
}
void MainWindow::on_B_1_0_1_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 1;
}
void MainWindow::on_B_1_0_2_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 2;
}
void MainWindow::on_B_2_0_3_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 3;
}
void MainWindow::on_B_2_0_4_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 4;
}
void MainWindow::on_B_2_0_5_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 5;
}
void MainWindow::on_B_3_0_6_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 6;
}
void MainWindow::on_B_3_0_7_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 7;
}
void MainWindow::on_B_3_0_8_clicked()
{
    new_game.location[0] = 0;
    new_game.location[1] = 8;
}
void MainWindow::on_B_1_1_0_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 0;
}
void MainWindow::on_B_1_1_1_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 1;
}
void MainWindow::on_B_1_1_2_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 2;
}
void MainWindow::on_B_2_1_3_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 3;
}
void MainWindow::on_B_2_1_4_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 4;
}
void MainWindow::on_B_2_1_5_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 5;
}
void MainWindow::on_B_3_1_6_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 6;
}
void MainWindow::on_B_3_1_7_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 7;
}
void MainWindow::on_B_3_1_8_clicked()
{
    new_game.location[0] = 1;
    new_game.location[1] = 8;
}
void MainWindow::on_B_1_2_0_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 0;
}
void MainWindow::on_B_1_2_1_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 1;
}
void MainWindow::on_B_1_2_2_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 2;
}
void MainWindow::on_B_2_2_3_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 3;
}
void MainWindow::on_B_2_2_4_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 4;
}
void MainWindow::on_B_2_2_5_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 5;
}
void MainWindow::on_B_3_2_6_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 6;
}
void MainWindow::on_B_3_2_7_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 7;
}
void MainWindow::on_B_3_2_8_clicked()
{
    new_game.location[0] = 2;
    new_game.location[1] = 8;
}
void MainWindow::on_B_4_3_0_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 0;
}
void MainWindow::on_B_4_3_1_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 1;
}
void MainWindow::on_B_4_3_2_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 2;
}
void MainWindow::on_B_5_3_3_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 3;
}
void MainWindow::on_B_5_3_4_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 4;
}
void MainWindow::on_B_5_3_5_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 5;
}
void MainWindow::on_B_6_3_6_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 6;
}
void MainWindow::on_B_6_3_7_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 7;
}
void MainWindow::on_B_6_3_8_clicked()
{
    new_game.location[0] = 3;
    new_game.location[1] = 8;
}
void MainWindow::on_B_4_4_0_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 0;
}
void MainWindow::on_B_4_4_1_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 1;
}
void MainWindow::on_B_4_4_2_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 2;
}
void MainWindow::on_B_5_4_3_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 3;
}
void MainWindow::on_B_5_4_4_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 4;
}
void MainWindow::on_B_5_4_5_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 5;
}
void MainWindow::on_B_6_4_6_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 6;
}
void MainWindow::on_B_6_4_7_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 7;
}
void MainWindow::on_B_6_4_8_clicked()
{
    new_game.location[0] = 4;
    new_game.location[1] = 8;
}
void MainWindow::on_B_4_5_0_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 0;
}
void MainWindow::on_B_4_5_1_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 1;
}
void MainWindow::on_B_4_5_2_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 2;
}
void MainWindow::on_B_5_5_3_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 3;
}
void MainWindow::on_B_5_5_4_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 4;
}
void MainWindow::on_B_5_5_5_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 5;
}
void MainWindow::on_B_6_5_6_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 6;
}
void MainWindow::on_B_6_5_7_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 7;
}
void MainWindow::on_B_6_5_8_clicked()
{
    new_game.location[0] = 5;
    new_game.location[1] = 8;
}
void MainWindow::on_B_7_6_0_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 0;
}
void MainWindow::on_B_7_6_1_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 1;
}
void MainWindow::on_B_7_6_2_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 2;
}
void MainWindow::on_B_8_6_3_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 3;
}
void MainWindow::on_B_8_6_4_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 4;
}
void MainWindow::on_B_8_6_5_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 5;
}
void MainWindow::on_B_9_6_6_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 6;
}
void MainWindow::on_B_9_6_7_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 7;
}
void MainWindow::on_B_9_6_8_clicked()
{
    new_game.location[0] = 6;
    new_game.location[1] = 8;
}
void MainWindow::on_B_7_7_0_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 0;
}
void MainWindow::on_B_7_7_1_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 1;
}
void MainWindow::on_B_7_7_2_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 2;
}
void MainWindow::on_B_8_7_3_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 3;
}
void MainWindow::on_B_8_7_4_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 4;
}
void MainWindow::on_B_8_7_5_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 5;
}
void MainWindow::on_B_9_7_6_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 6;
}
void MainWindow::on_B_9_7_7_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 7;
}
void MainWindow::on_B_9_7_8_clicked()
{
    new_game.location[0] = 7;
    new_game.location[1] = 8;
}
void MainWindow::on_B_7_8_0_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 0;
}
void MainWindow::on_B_7_8_1_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 1;
}
void MainWindow::on_B_7_8_2_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 2;
}
void MainWindow::on_B_8_8_3_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 3;
}
void MainWindow::on_B_8_8_4_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 4;
}
void MainWindow::on_B_8_8_5_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 5;
}
void MainWindow::on_B_9_8_6_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 6;
}
void MainWindow::on_B_9_8_7_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 7;
}
void MainWindow::on_B_9_8_8_clicked()
{
    new_game.location[0] = 8;
    new_game.location[1] = 8;
}

