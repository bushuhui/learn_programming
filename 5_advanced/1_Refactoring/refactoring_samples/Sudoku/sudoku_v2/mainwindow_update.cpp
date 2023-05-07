#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

void MainWindow::update_(Sudoku new_game)
{
    //QPalette pe1;
    //pe1.setColor(QPalette::ButtonText,Qt::black);
    QFont boldFont ;
    boldFont.setBold(true);
    QList <QPushButton *> Button_list;
    Button_list = ui -> groupBox_sudoku -> findChildren <QPushButton *>();

    new_game.Check_board();
    int check_number = 0;

    for(int i = 0;i < 81;i++){
        int x = i / 9;
        int y = i % 9;

        QString style_1 = "border: 4px outset rgb(0,0,255);background-color: rgb(105,105,105)";

        // update the number
        if(new_game.sudokuboard[x][y].point_type == false){
            Button_list[i] -> setText(QString::number(new_game.sudokuboard[x][y].value));
            Button_list[i] -> setFont(boldFont);
            Button_list[i] -> setFont((QFont("Aharoni", 18)));
        }
        else {
            if(new_game.sudokuboard[x][y].value != 0){
                Button_list[i] -> setText(QString::number(new_game.sudokuboard[x][y].value));
                Button_list[i] -> setFont((QFont("Aharoni", 16)));
            }
            else{
                Button_list[i] -> setText(" ");
            }
        }

        //update the background
        //"border: 4px outset rgb(0,0,255)" is to draw the blue rec means whether the button is choosn
        if(new_game.sudokuboard[x][y].point_type == false){ //(black)

            if(new_game.location[0] == x && new_game.location[1] == y )
            {
                Button_list[i] -> setStyleSheet("border: 8px outset rgb(0,0,255);background-color: rgb(105,105,105)");
            }
            else Button_list[i]->setStyleSheet("background-color: rgb(105,105,105)");
            check_number += 1;

        }
        else {
            if(new_game.sudokuboard[x][y].point_Islegal == true){
                if(new_game.sudokuboard[x][y].value != 0){  // the block isn't empty(green)

                    if(new_game.location[0] == x && new_game.location[1] == y )
                    {
                        Button_list[i] -> setStyleSheet("border: 8px outset rgb(0,0,255);background-color: rgb(0,255,0)");
                    }
                    else Button_list[i]->setStyleSheet("background-color: rgb(0,255,0)");
                    check_number += 1;

                }
                else { // the block is empty

                    if(new_game.location[0] == x && new_game.location[1] == y )
                    {
                        Button_list[i] -> setStyleSheet("border: 8px outset rgb(0,0,255);background-color: rgb(200,200,200)");
                    }
                    else Button_list[i]->setStyleSheet("background-color: rgb(200,200,200)");
                    }

                }
            else {  //point_Islegal == false (red)

                if(new_game.location[0] == x && new_game.location[1] == y )
                {
                    Button_list[i] -> setStyleSheet("border: 8px outset rgb(0,0,255);background-color: rgb(255,0,0)");
                }
                else Button_list[i]->setStyleSheet("background-color: rgb(255,0,0)");

            }
        }
    }

    if(check_number == 81){
        isStart = true;
        on_B_time_clicked();
    }
}
