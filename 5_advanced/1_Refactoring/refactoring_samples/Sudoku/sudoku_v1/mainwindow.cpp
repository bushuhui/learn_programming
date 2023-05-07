#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Newgame,SIGNAL(clicked()),this,SLOT(on_Newgame_clicked()));
    connect(ui->Newgame,SIGNAL(clicked()),this,SLOT(on_B_1_0_0_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_(Sudoku new_game)
{
    new_game.Check_board();
    update_numbers(new_game);
    update_background(new_game);
}

