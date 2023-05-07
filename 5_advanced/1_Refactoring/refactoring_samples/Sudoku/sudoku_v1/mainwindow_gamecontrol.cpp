#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

using namespace std;

Sudoku new_game;
void MainWindow::on_Newgame_clicked()
{
    new_game.RandomSudoku();
    update_(new_game);
}

void MainWindow::on_Computerplay_clicked()
{
    on_input_define_clicked();
    new_game.SolveSudoku(0);
    update_(new_game);
}

void MainWindow::on_Quit_clicked()
{
    this->close();
}


void MainWindow::on_Save_clicked()
{
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
        }
    }

    if( event->key() == Qt::Key_S ) {
        if(new_game.location[0]<8){
            new_game.location[0] ++;
        }
    }

    if( event->key() == Qt::Key_A ) {
        if(new_game.location[1]>0){
            new_game.location[1] --;
        }
    }

    if( event->key() == Qt::Key_D ) {
        if(new_game.location[1]<8){
            new_game.location[1] ++;
        }
    }

    if( event->key() == Qt::Key_1 )  on_input_1_clicked();
    if( event->key() == Qt::Key_2 )  on_input_2_clicked();
    if( event->key() == Qt::Key_3 )  on_input_3_clicked();
    if( event->key() == Qt::Key_4 )  on_input_4_clicked();
    if( event->key() == Qt::Key_5 )  on_input_5_clicked();
    if( event->key() == Qt::Key_6 )  on_input_6_clicked();
    if( event->key() == Qt::Key_7 )  on_input_7_clicked();
    if( event->key() == Qt::Key_8 )  on_input_8_clicked();
    if( event->key() == Qt::Key_9 )  on_input_9_clicked();


}
