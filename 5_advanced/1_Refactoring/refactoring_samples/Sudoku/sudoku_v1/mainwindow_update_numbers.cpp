#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

void MainWindow::update_numbers(Sudoku new_game)
{
    //QPalette pe1;
    //pe1.setColor(QPalette::ButtonText,Qt::black);
    QFont boldFont ;
    boldFont.setBold(true);

    if(new_game.sudokuboard[0][0].point_type == false){
        ui -> B_1_0_0 -> setText(QString::number(new_game.sudokuboard[0][0].value));
        ui -> B_1_0_0 -> setFont(boldFont);
        ui -> B_1_0_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][0].value != 0){
            ui -> B_1_0_0 -> setText(QString::number(new_game.sudokuboard[0][0].value));
            ui -> B_1_0_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_0_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][1].point_type == false){
        ui -> B_1_0_1 -> setText(QString::number(new_game.sudokuboard[0][1].value));
        ui -> B_1_0_1 -> setFont(boldFont);
        ui -> B_1_0_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][1].value != 0){
            ui -> B_1_0_1 -> setText(QString::number(new_game.sudokuboard[0][1].value));
            ui -> B_1_0_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_0_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][2].point_type == false){
        ui -> B_1_0_2 -> setText(QString::number(new_game.sudokuboard[0][2].value));
        ui -> B_1_0_2 -> setFont(boldFont);
        ui -> B_1_0_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][2].value != 0){
            ui -> B_1_0_2 -> setText(QString::number(new_game.sudokuboard[0][2].value));
            ui -> B_1_0_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_0_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][3].point_type == false){
        ui -> B_2_0_3 -> setText(QString::number(new_game.sudokuboard[0][3].value));
        ui -> B_2_0_3 -> setFont(boldFont);
        ui -> B_2_0_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][3].value != 0){
            ui -> B_2_0_3 -> setText(QString::number(new_game.sudokuboard[0][3].value));
            ui -> B_2_0_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_0_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][4].point_type == false){
        ui -> B_2_0_4 -> setText(QString::number(new_game.sudokuboard[0][4].value));
        ui -> B_2_0_4 -> setFont(boldFont);
        ui -> B_2_0_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][4].value != 0){
            ui -> B_2_0_4 -> setText(QString::number(new_game.sudokuboard[0][4].value));
            ui -> B_2_0_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_0_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][5].point_type == false){
        ui -> B_2_0_5 -> setText(QString::number(new_game.sudokuboard[0][5].value));
        ui -> B_2_0_5 -> setFont(boldFont);
        ui -> B_2_0_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][5].value != 0){
            ui -> B_2_0_5 -> setText(QString::number(new_game.sudokuboard[0][5].value));
            ui -> B_2_0_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_0_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][6].point_type == false){
        ui -> B_3_0_6 -> setText(QString::number(new_game.sudokuboard[0][6].value));
        ui -> B_3_0_6 -> setFont(boldFont);
        ui -> B_3_0_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][6].value != 0){
            ui -> B_3_0_6 -> setText(QString::number(new_game.sudokuboard[0][6].value));
            ui -> B_3_0_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_0_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][7].point_type == false){
        ui -> B_3_0_7 -> setText(QString::number(new_game.sudokuboard[0][7].value));
        ui -> B_3_0_7 -> setFont(boldFont);
        ui -> B_3_0_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][7].value != 0){
            ui -> B_3_0_7 -> setText(QString::number(new_game.sudokuboard[0][7].value));
            ui -> B_3_0_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_0_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[0][8].point_type == false){
        ui -> B_3_0_8 -> setText(QString::number(new_game.sudokuboard[0][8].value));
        ui -> B_3_0_8 -> setFont(boldFont);
        ui -> B_3_0_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[0][8].value != 0){
            ui -> B_3_0_8 -> setText(QString::number(new_game.sudokuboard[0][8].value));
            ui -> B_3_0_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_0_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][0].point_type == false){
        ui -> B_1_1_0 -> setText(QString::number(new_game.sudokuboard[1][0].value));
        ui -> B_1_1_0 -> setFont(boldFont);
        ui -> B_1_1_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][0].value != 0){
            ui -> B_1_1_0 -> setText(QString::number(new_game.sudokuboard[1][0].value));
            ui -> B_1_1_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_1_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][1].point_type == false){
        ui -> B_1_1_1 -> setText(QString::number(new_game.sudokuboard[1][1].value));
        ui -> B_1_1_1 -> setFont(boldFont);
        ui -> B_1_1_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][1].value != 0){
            ui -> B_1_1_1 -> setText(QString::number(new_game.sudokuboard[1][1].value));
            ui -> B_1_1_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_1_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][2].point_type == false){
        ui -> B_1_1_2 -> setText(QString::number(new_game.sudokuboard[1][2].value));
        ui -> B_1_1_2 -> setFont(boldFont);
        ui -> B_1_1_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][2].value != 0){
            ui -> B_1_1_2 -> setText(QString::number(new_game.sudokuboard[1][2].value));
            ui -> B_1_1_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_1_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][3].point_type == false){
        ui -> B_2_1_3 -> setText(QString::number(new_game.sudokuboard[1][3].value));
        ui -> B_2_1_3 -> setFont(boldFont);
        ui -> B_2_1_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][3].value != 0){
            ui -> B_2_1_3 -> setText(QString::number(new_game.sudokuboard[1][3].value));
            ui -> B_2_1_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_1_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][4].point_type == false){
        ui -> B_2_1_4 -> setText(QString::number(new_game.sudokuboard[1][4].value));
        ui -> B_2_1_4 -> setFont(boldFont);
        ui -> B_2_1_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][4].value != 0){
            ui -> B_2_1_4 -> setText(QString::number(new_game.sudokuboard[1][4].value));
            ui -> B_2_1_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_1_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][5].point_type == false){
        ui -> B_2_1_5 -> setText(QString::number(new_game.sudokuboard[1][5].value));
        ui -> B_2_1_5 -> setFont(boldFont);
        ui -> B_2_1_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][5].value != 0){
            ui -> B_2_1_5 -> setText(QString::number(new_game.sudokuboard[1][5].value));
            ui -> B_2_1_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_1_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][6].point_type == false){
        ui -> B_3_1_6 -> setText(QString::number(new_game.sudokuboard[1][6].value));
        ui -> B_3_1_6 -> setFont(boldFont);
        ui -> B_3_1_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][6].value != 0){
            ui -> B_3_1_6 -> setText(QString::number(new_game.sudokuboard[1][6].value));
            ui -> B_3_1_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_1_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][7].point_type == false){
        ui -> B_3_1_7 -> setText(QString::number(new_game.sudokuboard[1][7].value));
        ui -> B_3_1_7 -> setFont(boldFont);
        ui -> B_3_1_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][7].value != 0){
            ui -> B_3_1_7 -> setText(QString::number(new_game.sudokuboard[1][7].value));
            ui -> B_3_1_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_1_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[1][8].point_type == false){
        ui -> B_3_1_8 -> setText(QString::number(new_game.sudokuboard[1][8].value));
        ui -> B_3_1_8 -> setFont(boldFont);
        ui -> B_3_1_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[1][8].value != 0){
            ui -> B_3_1_8 -> setText(QString::number(new_game.sudokuboard[1][8].value));
            ui -> B_3_1_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_1_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][0].point_type == false){
        ui -> B_1_2_0 -> setText(QString::number(new_game.sudokuboard[2][0].value));
        ui -> B_1_2_0 -> setFont(boldFont);
        ui -> B_1_2_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][0].value != 0){
            ui -> B_1_2_0 -> setText(QString::number(new_game.sudokuboard[2][0].value));
            ui -> B_1_2_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_2_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][1].point_type == false){
        ui -> B_1_2_1 -> setText(QString::number(new_game.sudokuboard[2][1].value));
        ui -> B_1_2_1 -> setFont(boldFont);
        ui -> B_1_2_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][1].value != 0){
            ui -> B_1_2_1 -> setText(QString::number(new_game.sudokuboard[2][1].value));
            ui -> B_1_2_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_2_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][2].point_type == false){
        ui -> B_1_2_2 -> setText(QString::number(new_game.sudokuboard[2][2].value));
        ui -> B_1_2_2 -> setFont(boldFont);
        ui -> B_1_2_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][2].value != 0){
            ui -> B_1_2_2 -> setText(QString::number(new_game.sudokuboard[2][2].value));
            ui -> B_1_2_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_1_2_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][3].point_type == false){
        ui -> B_2_2_3 -> setText(QString::number(new_game.sudokuboard[2][3].value));
        ui -> B_2_2_3 -> setFont(boldFont);
        ui -> B_2_2_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][3].value != 0){
            ui -> B_2_2_3 -> setText(QString::number(new_game.sudokuboard[2][3].value));
            ui -> B_2_2_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_2_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][4].point_type == false){
        ui -> B_2_2_4 -> setText(QString::number(new_game.sudokuboard[2][4].value));
        ui -> B_2_2_4 -> setFont(boldFont);
        ui -> B_2_2_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][4].value != 0){
            ui -> B_2_2_4 -> setText(QString::number(new_game.sudokuboard[2][4].value));
            ui -> B_2_2_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_2_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][5].point_type == false){
        ui -> B_2_2_5 -> setText(QString::number(new_game.sudokuboard[2][5].value));
        ui -> B_2_2_5 -> setFont(boldFont);
        ui -> B_2_2_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][5].value != 0){
            ui -> B_2_2_5 -> setText(QString::number(new_game.sudokuboard[2][5].value));
            ui -> B_2_2_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_2_2_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][6].point_type == false){
        ui -> B_3_2_6 -> setText(QString::number(new_game.sudokuboard[2][6].value));
        ui -> B_3_2_6 -> setFont(boldFont);
        ui -> B_3_2_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][6].value != 0){
            ui -> B_3_2_6 -> setText(QString::number(new_game.sudokuboard[2][6].value));
            ui -> B_3_2_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_2_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][7].point_type == false){
        ui -> B_3_2_7 -> setText(QString::number(new_game.sudokuboard[2][7].value));
        ui -> B_3_2_7 -> setFont(boldFont);
        ui -> B_3_2_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][7].value != 0){
            ui -> B_3_2_7 -> setText(QString::number(new_game.sudokuboard[2][7].value));
            ui -> B_3_2_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_2_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[2][8].point_type == false){
        ui -> B_3_2_8 -> setText(QString::number(new_game.sudokuboard[2][8].value));
        ui -> B_3_2_8 -> setFont(boldFont);
        ui -> B_3_2_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[2][8].value != 0){
            ui -> B_3_2_8 -> setText(QString::number(new_game.sudokuboard[2][8].value));
            ui -> B_3_2_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_3_2_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][0].point_type == false){
        ui -> B_4_3_0 -> setText(QString::number(new_game.sudokuboard[3][0].value));
        ui -> B_4_3_0 -> setFont(boldFont);
        ui -> B_4_3_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][0].value != 0){
            ui -> B_4_3_0 -> setText(QString::number(new_game.sudokuboard[3][0].value));
            ui -> B_4_3_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_3_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][1].point_type == false){
        ui -> B_4_3_1 -> setText(QString::number(new_game.sudokuboard[3][1].value));
        ui -> B_4_3_1 -> setFont(boldFont);
        ui -> B_4_3_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][1].value != 0){
            ui -> B_4_3_1 -> setText(QString::number(new_game.sudokuboard[3][1].value));
            ui -> B_4_3_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_3_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][2].point_type == false){
        ui -> B_4_3_2 -> setText(QString::number(new_game.sudokuboard[3][2].value));
        ui -> B_4_3_2 -> setFont(boldFont);
        ui -> B_4_3_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][2].value != 0){
            ui -> B_4_3_2 -> setText(QString::number(new_game.sudokuboard[3][2].value));
            ui -> B_4_3_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_3_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][3].point_type == false){
        ui -> B_5_3_3 -> setText(QString::number(new_game.sudokuboard[3][3].value));
        ui -> B_5_3_3 -> setFont(boldFont);
        ui -> B_5_3_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][3].value != 0){
            ui -> B_5_3_3 -> setText(QString::number(new_game.sudokuboard[3][3].value));
            ui -> B_5_3_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_3_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][4].point_type == false){
        ui -> B_5_3_4 -> setText(QString::number(new_game.sudokuboard[3][4].value));
        ui -> B_5_3_4 -> setFont(boldFont);
        ui -> B_5_3_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][4].value != 0){
            ui -> B_5_3_4 -> setText(QString::number(new_game.sudokuboard[3][4].value));
            ui -> B_5_3_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_3_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][5].point_type == false){
        ui -> B_5_3_5 -> setText(QString::number(new_game.sudokuboard[3][5].value));
        ui -> B_5_3_5 -> setFont(boldFont);
        ui -> B_5_3_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][5].value != 0){
            ui -> B_5_3_5 -> setText(QString::number(new_game.sudokuboard[3][5].value));
            ui -> B_5_3_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_3_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][6].point_type == false){
        ui -> B_6_3_6 -> setText(QString::number(new_game.sudokuboard[3][6].value));
        ui -> B_6_3_6 -> setFont(boldFont);
        ui -> B_6_3_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][6].value != 0){
            ui -> B_6_3_6 -> setText(QString::number(new_game.sudokuboard[3][6].value));
            ui -> B_6_3_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_3_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][7].point_type == false){
        ui -> B_6_3_7 -> setText(QString::number(new_game.sudokuboard[3][7].value));
        ui -> B_6_3_7 -> setFont(boldFont);
        ui -> B_6_3_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][7].value != 0){
            ui -> B_6_3_7 -> setText(QString::number(new_game.sudokuboard[3][7].value));
            ui -> B_6_3_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_3_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[3][8].point_type == false){
        ui -> B_6_3_8 -> setText(QString::number(new_game.sudokuboard[3][8].value));
        ui -> B_6_3_8 -> setFont(boldFont);
        ui -> B_6_3_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[3][8].value != 0){
            ui -> B_6_3_8 -> setText(QString::number(new_game.sudokuboard[3][8].value));
            ui -> B_6_3_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_3_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][0].point_type == false){
        ui -> B_4_4_0 -> setText(QString::number(new_game.sudokuboard[4][0].value));
        ui -> B_4_4_0 -> setFont(boldFont);
        ui -> B_4_4_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][0].value != 0){
            ui -> B_4_4_0 -> setText(QString::number(new_game.sudokuboard[4][0].value));
            ui -> B_4_4_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_4_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][1].point_type == false){
        ui -> B_4_4_1 -> setText(QString::number(new_game.sudokuboard[4][1].value));
        ui -> B_4_4_1 -> setFont(boldFont);
        ui -> B_4_4_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][1].value != 0){
            ui -> B_4_4_1 -> setText(QString::number(new_game.sudokuboard[4][1].value));
            ui -> B_4_4_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_4_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][2].point_type == false){
        ui -> B_4_4_2 -> setText(QString::number(new_game.sudokuboard[4][2].value));
        ui -> B_4_4_2 -> setFont(boldFont);
        ui -> B_4_4_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][2].value != 0){
            ui -> B_4_4_2 -> setText(QString::number(new_game.sudokuboard[4][2].value));
            ui -> B_4_4_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_4_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][3].point_type == false){
        ui -> B_5_4_3 -> setText(QString::number(new_game.sudokuboard[4][3].value));
        ui -> B_5_4_3 -> setFont(boldFont);
        ui -> B_5_4_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][3].value != 0){
            ui -> B_5_4_3 -> setText(QString::number(new_game.sudokuboard[4][3].value));
            ui -> B_5_4_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_4_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][4].point_type == false){
        ui -> B_5_4_4 -> setText(QString::number(new_game.sudokuboard[4][4].value));
        ui -> B_5_4_4 -> setFont(boldFont);
        ui -> B_5_4_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][4].value != 0){
            ui -> B_5_4_4 -> setText(QString::number(new_game.sudokuboard[4][4].value));
            ui -> B_5_4_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_4_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][5].point_type == false){
        ui -> B_5_4_5 -> setText(QString::number(new_game.sudokuboard[4][5].value));
        ui -> B_5_4_5 -> setFont(boldFont);
        ui -> B_5_4_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][5].value != 0){
            ui -> B_5_4_5 -> setText(QString::number(new_game.sudokuboard[4][5].value));
            ui -> B_5_4_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_4_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][6].point_type == false){
        ui -> B_6_4_6 -> setText(QString::number(new_game.sudokuboard[4][6].value));
        ui -> B_6_4_6 -> setFont(boldFont);
        ui -> B_6_4_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][6].value != 0){
            ui -> B_6_4_6 -> setText(QString::number(new_game.sudokuboard[4][6].value));
            ui -> B_6_4_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_4_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][7].point_type == false){
        ui -> B_6_4_7 -> setText(QString::number(new_game.sudokuboard[4][7].value));
        ui -> B_6_4_7 -> setFont(boldFont);
        ui -> B_6_4_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][7].value != 0){
            ui -> B_6_4_7 -> setText(QString::number(new_game.sudokuboard[4][7].value));
            ui -> B_6_4_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_4_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[4][8].point_type == false){
        ui -> B_6_4_8 -> setText(QString::number(new_game.sudokuboard[4][8].value));
        ui -> B_6_4_8 -> setFont(boldFont);
        ui -> B_6_4_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[4][8].value != 0){
            ui -> B_6_4_8 -> setText(QString::number(new_game.sudokuboard[4][8].value));
            ui -> B_6_4_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_4_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][0].point_type == false){
        ui -> B_4_5_0 -> setText(QString::number(new_game.sudokuboard[5][0].value));
        ui -> B_4_5_0 -> setFont(boldFont);
        ui -> B_4_5_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][0].value != 0){
            ui -> B_4_5_0 -> setText(QString::number(new_game.sudokuboard[5][0].value));
            ui -> B_4_5_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_5_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][1].point_type == false){
        ui -> B_4_5_1 -> setText(QString::number(new_game.sudokuboard[5][1].value));
        ui -> B_4_5_1 -> setFont(boldFont);
        ui -> B_4_5_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][1].value != 0){
            ui -> B_4_5_1 -> setText(QString::number(new_game.sudokuboard[5][1].value));
            ui -> B_4_5_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_5_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][2].point_type == false){
        ui -> B_4_5_2 -> setText(QString::number(new_game.sudokuboard[5][2].value));
        ui -> B_4_5_2 -> setFont(boldFont);
        ui -> B_4_5_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][2].value != 0){
            ui -> B_4_5_2 -> setText(QString::number(new_game.sudokuboard[5][2].value));
            ui -> B_4_5_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_4_5_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][3].point_type == false){
        ui -> B_5_5_3 -> setText(QString::number(new_game.sudokuboard[5][3].value));
        ui -> B_5_5_3 -> setFont(boldFont);
        ui -> B_5_5_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][3].value != 0){
            ui -> B_5_5_3 -> setText(QString::number(new_game.sudokuboard[5][3].value));
            ui -> B_5_5_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_5_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][4].point_type == false){
        ui -> B_5_5_4 -> setText(QString::number(new_game.sudokuboard[5][4].value));
        ui -> B_5_5_4 -> setFont(boldFont);
        ui -> B_5_5_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][4].value != 0){
            ui -> B_5_5_4 -> setText(QString::number(new_game.sudokuboard[5][4].value));
            ui -> B_5_5_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_5_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][5].point_type == false){
        ui -> B_5_5_5 -> setText(QString::number(new_game.sudokuboard[5][5].value));
        ui -> B_5_5_5 -> setFont(boldFont);
        ui -> B_5_5_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][5].value != 0){
            ui -> B_5_5_5 -> setText(QString::number(new_game.sudokuboard[5][5].value));
            ui -> B_5_5_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_5_5_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][6].point_type == false){
        ui -> B_6_5_6 -> setText(QString::number(new_game.sudokuboard[5][6].value));
        ui -> B_6_5_6 -> setFont(boldFont);
        ui -> B_6_5_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][6].value != 0){
            ui -> B_6_5_6 -> setText(QString::number(new_game.sudokuboard[5][6].value));
            ui -> B_6_5_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_5_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][7].point_type == false){
        ui -> B_6_5_7 -> setText(QString::number(new_game.sudokuboard[5][7].value));
        ui -> B_6_5_7 -> setFont(boldFont);
        ui -> B_6_5_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][7].value != 0){
            ui -> B_6_5_7 -> setText(QString::number(new_game.sudokuboard[5][7].value));
            ui -> B_6_5_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_5_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[5][8].point_type == false){
        ui -> B_6_5_8 -> setText(QString::number(new_game.sudokuboard[5][8].value));
        ui -> B_6_5_8 -> setFont(boldFont);
        ui -> B_6_5_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[5][8].value != 0){
            ui -> B_6_5_8 -> setText(QString::number(new_game.sudokuboard[5][8].value));
            ui -> B_6_5_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_6_5_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][0].point_type == false){
        ui -> B_7_6_0 -> setText(QString::number(new_game.sudokuboard[6][0].value));
        ui -> B_7_6_0 -> setFont(boldFont);
        ui -> B_7_6_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][0].value != 0){
            ui -> B_7_6_0 -> setText(QString::number(new_game.sudokuboard[6][0].value));
            ui -> B_7_6_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_6_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][1].point_type == false){
        ui -> B_7_6_1 -> setText(QString::number(new_game.sudokuboard[6][1].value));
        ui -> B_7_6_1 -> setFont(boldFont);
        ui -> B_7_6_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][1].value != 0){
            ui -> B_7_6_1 -> setText(QString::number(new_game.sudokuboard[6][1].value));
            ui -> B_7_6_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_6_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][2].point_type == false){
        ui -> B_7_6_2 -> setText(QString::number(new_game.sudokuboard[6][2].value));
        ui -> B_7_6_2 -> setFont(boldFont);
        ui -> B_7_6_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][2].value != 0){
            ui -> B_7_6_2 -> setText(QString::number(new_game.sudokuboard[6][2].value));
            ui -> B_7_6_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_6_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][3].point_type == false){
        ui -> B_8_6_3 -> setText(QString::number(new_game.sudokuboard[6][3].value));
        ui -> B_8_6_3 -> setFont(boldFont);
        ui -> B_8_6_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][3].value != 0){
            ui -> B_8_6_3 -> setText(QString::number(new_game.sudokuboard[6][3].value));
            ui -> B_8_6_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_6_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][4].point_type == false){
        ui -> B_8_6_4 -> setText(QString::number(new_game.sudokuboard[6][4].value));
        ui -> B_8_6_4 -> setFont(boldFont);
        ui -> B_8_6_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][4].value != 0){
            ui -> B_8_6_4 -> setText(QString::number(new_game.sudokuboard[6][4].value));
            ui -> B_8_6_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_6_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][5].point_type == false){
        ui -> B_8_6_5 -> setText(QString::number(new_game.sudokuboard[6][5].value));
        ui -> B_8_6_5 -> setFont(boldFont);
        ui -> B_8_6_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][5].value != 0){
            ui -> B_8_6_5 -> setText(QString::number(new_game.sudokuboard[6][5].value));
            ui -> B_8_6_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_6_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][6].point_type == false){
        ui -> B_9_6_6 -> setText(QString::number(new_game.sudokuboard[6][6].value));
        ui -> B_9_6_6 -> setFont(boldFont);
        ui -> B_9_6_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][6].value != 0){
            ui -> B_9_6_6 -> setText(QString::number(new_game.sudokuboard[6][6].value));
            ui -> B_9_6_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_6_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][7].point_type == false){
        ui -> B_9_6_7 -> setText(QString::number(new_game.sudokuboard[6][7].value));
        ui -> B_9_6_7 -> setFont(boldFont);
        ui -> B_9_6_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][7].value != 0){
            ui -> B_9_6_7 -> setText(QString::number(new_game.sudokuboard[6][7].value));
            ui -> B_9_6_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_6_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[6][8].point_type == false){
        ui -> B_9_6_8 -> setText(QString::number(new_game.sudokuboard[6][8].value));
        ui -> B_9_6_8 -> setFont(boldFont);
        ui -> B_9_6_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[6][8].value != 0){
            ui -> B_9_6_8 -> setText(QString::number(new_game.sudokuboard[6][8].value));
            ui -> B_9_6_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_6_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][0].point_type == false){
        ui -> B_7_7_0 -> setText(QString::number(new_game.sudokuboard[7][0].value));
        ui -> B_7_7_0 -> setFont(boldFont);
        ui -> B_7_7_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][0].value != 0){
            ui -> B_7_7_0 -> setText(QString::number(new_game.sudokuboard[7][0].value));
            ui -> B_7_7_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_7_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][1].point_type == false){
        ui -> B_7_7_1 -> setText(QString::number(new_game.sudokuboard[7][1].value));
        ui -> B_7_7_1 -> setFont(boldFont);
        ui -> B_7_7_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][1].value != 0){
            ui -> B_7_7_1 -> setText(QString::number(new_game.sudokuboard[7][1].value));
            ui -> B_7_7_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_7_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][2].point_type == false){
        ui -> B_7_7_2 -> setText(QString::number(new_game.sudokuboard[7][2].value));
        ui -> B_7_7_2 -> setFont(boldFont);
        ui -> B_7_7_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][2].value != 0){
            ui -> B_7_7_2 -> setText(QString::number(new_game.sudokuboard[7][2].value));
            ui -> B_7_7_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_7_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][3].point_type == false){
        ui -> B_8_7_3 -> setText(QString::number(new_game.sudokuboard[7][3].value));
        ui -> B_8_7_3 -> setFont(boldFont);
        ui -> B_8_7_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][3].value != 0){
            ui -> B_8_7_3 -> setText(QString::number(new_game.sudokuboard[7][3].value));
            ui -> B_8_7_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_7_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][4].point_type == false){
        ui -> B_8_7_4 -> setText(QString::number(new_game.sudokuboard[7][4].value));
        ui -> B_8_7_4 -> setFont(boldFont);
        ui -> B_8_7_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][4].value != 0){
            ui -> B_8_7_4 -> setText(QString::number(new_game.sudokuboard[7][4].value));
            ui -> B_8_7_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_7_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][5].point_type == false){
        ui -> B_8_7_5 -> setText(QString::number(new_game.sudokuboard[7][5].value));
        ui -> B_8_7_5 -> setFont(boldFont);
        ui -> B_8_7_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][5].value != 0){
            ui -> B_8_7_5 -> setText(QString::number(new_game.sudokuboard[7][5].value));
            ui -> B_8_7_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_7_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][6].point_type == false){
        ui -> B_9_7_6 -> setText(QString::number(new_game.sudokuboard[7][6].value));
        ui -> B_9_7_6 -> setFont(boldFont);
        ui -> B_9_7_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][6].value != 0){
            ui -> B_9_7_6 -> setText(QString::number(new_game.sudokuboard[7][6].value));
            ui -> B_9_7_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_7_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][7].point_type == false){
        ui -> B_9_7_7 -> setText(QString::number(new_game.sudokuboard[7][7].value));
        ui -> B_9_7_7 -> setFont(boldFont);
        ui -> B_9_7_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][7].value != 0){
            ui -> B_9_7_7 -> setText(QString::number(new_game.sudokuboard[7][7].value));
            ui -> B_9_7_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_7_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[7][8].point_type == false){
        ui -> B_9_7_8 -> setText(QString::number(new_game.sudokuboard[7][8].value));
        ui -> B_9_7_8 -> setFont(boldFont);
        ui -> B_9_7_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[7][8].value != 0){
            ui -> B_9_7_8 -> setText(QString::number(new_game.sudokuboard[7][8].value));
            ui -> B_9_7_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_7_8 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][0].point_type == false){
        ui -> B_7_8_0 -> setText(QString::number(new_game.sudokuboard[8][0].value));
        ui -> B_7_8_0 -> setFont(boldFont);
        ui -> B_7_8_0 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][0].value != 0){
            ui -> B_7_8_0 -> setText(QString::number(new_game.sudokuboard[8][0].value));
            ui -> B_7_8_0 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_8_0 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][1].point_type == false){
        ui -> B_7_8_1 -> setText(QString::number(new_game.sudokuboard[8][1].value));
        ui -> B_7_8_1 -> setFont(boldFont);
        ui -> B_7_8_1 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][1].value != 0){
            ui -> B_7_8_1 -> setText(QString::number(new_game.sudokuboard[8][1].value));
            ui -> B_7_8_1 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_8_1 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][2].point_type == false){
        ui -> B_7_8_2 -> setText(QString::number(new_game.sudokuboard[8][2].value));
        ui -> B_7_8_2 -> setFont(boldFont);
        ui -> B_7_8_2 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][2].value != 0){
            ui -> B_7_8_2 -> setText(QString::number(new_game.sudokuboard[8][2].value));
            ui -> B_7_8_2 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_7_8_2 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][3].point_type == false){
        ui -> B_8_8_3 -> setText(QString::number(new_game.sudokuboard[8][3].value));
        ui -> B_8_8_3 -> setFont(boldFont);
        ui -> B_8_8_3 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][3].value != 0){
            ui -> B_8_8_3 -> setText(QString::number(new_game.sudokuboard[8][3].value));
            ui -> B_8_8_3 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_8_3 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][4].point_type == false){
        ui -> B_8_8_4 -> setText(QString::number(new_game.sudokuboard[8][4].value));
        ui -> B_8_8_4 -> setFont(boldFont);
        ui -> B_8_8_4 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][4].value != 0){
            ui -> B_8_8_4 -> setText(QString::number(new_game.sudokuboard[8][4].value));
            ui -> B_8_8_4 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_8_4 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][5].point_type == false){
        ui -> B_8_8_5 -> setText(QString::number(new_game.sudokuboard[8][5].value));
        ui -> B_8_8_5 -> setFont(boldFont);
        ui -> B_8_8_5 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][5].value != 0){
            ui -> B_8_8_5 -> setText(QString::number(new_game.sudokuboard[8][5].value));
            ui -> B_8_8_5 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_8_8_5 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][6].point_type == false){
        ui -> B_9_8_6 -> setText(QString::number(new_game.sudokuboard[8][6].value));
        ui -> B_9_8_6 -> setFont(boldFont);
        ui -> B_9_8_6 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][6].value != 0){
            ui -> B_9_8_6 -> setText(QString::number(new_game.sudokuboard[8][6].value));
            ui -> B_9_8_6 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_8_6 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][7].point_type == false){
        ui -> B_9_8_7 -> setText(QString::number(new_game.sudokuboard[8][7].value));
        ui -> B_9_8_7 -> setFont(boldFont);
        ui -> B_9_8_7 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][7].value != 0){
            ui -> B_9_8_7 -> setText(QString::number(new_game.sudokuboard[8][7].value));
            ui -> B_9_8_7 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_8_7 -> setText(" ");
        }
    }
    if(new_game.sudokuboard[8][8].point_type == false){
        ui -> B_9_8_8 -> setText(QString::number(new_game.sudokuboard[8][8].value));
        ui -> B_9_8_8 -> setFont(boldFont);
        ui -> B_9_8_8 -> setFont((QFont("Aharoni", 18)));
    }
    else {
        if(new_game.sudokuboard[8][8].value != 0){
            ui -> B_9_8_8 -> setText(QString::number(new_game.sudokuboard[8][8].value));
            ui -> B_9_8_8 -> setFont((QFont("Aharoni", 16)));
        }
        else{
            ui -> B_9_8_8 -> setText(" ");
        }
    }
}
