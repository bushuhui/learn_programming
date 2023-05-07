#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"
#include "tool_function.h"

using namespace std;

void MainWindow::on_Newgame_clicked()
{
    new_game.RandomSudoku();
    update_(new_game);
    TimeRecord = new QTime(0, 0, 0);
    isStart = false;
    on_B_time_clicked();
}

void MainWindow::on_Computerplay_clicked()
{
    on_input_define_clicked();
    new_game.SolveSudoku(0);
    update_(new_game);
}

void MainWindow::on_Quit_clicked()
{
    this -> close();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if( arg1 == "    Game mode : easy") new_game.game_mode = 6;
    if (arg1 == "    Game mode : normal") new_game.game_mode = 4;
    if (arg1 == "    Game mode : hard") new_game.game_mode = 2;
}


void MainWindow::on_Save_clicked()
{
    isStart = true;
    on_B_time_clicked();

    QString path = QFileDialog::getSaveFileName(this, tr("Save Game"),"F:/",tr("game(*.dat)"));
    std::string str = path.toStdString();
    const char* ch = str.c_str();
    ofstream File;
    File.open(ch, ios::out | ios::binary);
    File.write((char*)&new_game, sizeof(new_game));
    File.close();

}

void MainWindow::on_Load_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"load","F:/","*.dat");
    std::string str = file_name.toStdString();
    const char* ch = str.c_str();
    ifstream File;
    File.open(ch,ios::in|ios::binary);
    File.read((char *)&new_game, sizeof(new_game));
    File.close();

    update_(new_game);
    if(new_game.game_mode == 2) ui ->comboBox->setCurrentIndex(2);
    if(new_game.game_mode == 4) ui ->comboBox->setCurrentIndex(1);
    if(new_game.game_mode == 6) ui ->comboBox->setCurrentIndex(0);

    int time[3];
    get_time(time , new_game.game_time);
    TimeRecord = new QTime(time[0], time[1], time[2]);
    updateTime();
    isStart = true;
    on_B_time_clicked();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if( event->key() == Qt::Key_R )  on_Newgame_clicked();
    if( event->key() == Qt::Key_G )  on_Computerplay_clicked();
    if( event->key() == Qt::Key_C ) on_input_define_clicked();
    if( event->key() == Qt::Key_Backspace ) on_input_delete_clicked();
    if( event->key() == Qt::Key_Q) on_Quit_clicked();
    if( event->key() == Qt::Key_E ) on_Save_clicked();
    if( event->key() == Qt::Key_T) on_Load_clicked();


    if( event->key() == Qt::Key_W ) {
        if(new_game.location[0]>0){
            new_game.location[0] --;
            update_(new_game);
        }
    }

    if( event->key() == Qt::Key_S ) {
        if(new_game.location[0]<8){
            new_game.location[0] ++;
            update_(new_game);
        }
    }

    if( event->key() == Qt::Key_A ) {
        if(new_game.location[1]>0){
            new_game.location[1] --;
            update_(new_game);
        }
    }

    if( event->key() == Qt::Key_D ) {
        if(new_game.location[1]<8){
            new_game.location[1] ++;
            update_(new_game);
        }
    }

    if( event->key() == Qt::Key_1 )  {Input_number(1); update_(new_game);}
    if( event->key() == Qt::Key_2 )  {Input_number(2); update_(new_game);}
    if( event->key() == Qt::Key_3 )  {Input_number(3); update_(new_game);}
    if( event->key() == Qt::Key_4 )  {Input_number(4); update_(new_game);}
    if( event->key() == Qt::Key_5 )  {Input_number(5); update_(new_game);}
    if( event->key() == Qt::Key_6 )  {Input_number(6); update_(new_game);}
    if( event->key() == Qt::Key_7 )  {Input_number(7); update_(new_game);}
    if( event->key() == Qt::Key_8 )  {Input_number(8); update_(new_game);}
    if( event->key() == Qt::Key_9 )  {Input_number(9); update_(new_game);}
}


void MainWindow::on_board_clicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    qDebug() << btn;

    QList <QPushButton *> Button_list;
    Button_list = ui -> groupBox_sudoku -> findChildren <QPushButton *>();

    for(int i = 0;i < 81;i ++){
        if( Button_list[i]->objectName() == btn->objectName()){
            new_game.location[0] = i / 9;
            new_game.location[1] = i % 9;
            update_(new_game);
            break;
        }
    }
}
