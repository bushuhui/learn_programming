#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

void MainWindow::updateTime()
{
    *TimeRecord = TimeRecord->addSecs(1);
    ui->timer_show->display(TimeRecord->toString("hh:mm:ss"));
    QString temp = TimeRecord->toString("hhmmss");
    new_game.game_time = temp.toInt();
}

void MainWindow::on_B_time_clicked()
{
    if(isStart == false){
        timer->start(1000);
        ui -> B_time->setText("stop");
    }
    else{
        timer->stop();
        ui -> B_time->setText("continue");
        }
    isStart = !isStart;
}
