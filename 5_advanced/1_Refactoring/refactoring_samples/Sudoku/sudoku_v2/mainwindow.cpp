#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Sudoku new_game;

    // draw the suduko board
    int side = 55;
    int space = 10;
    for (int i = 0; i < 9; i++){
        for(int j = 0;j < 9; j++){
            QPushButton *bt = new QPushButton(QString::asprintf(" "), ui->groupBox_sudoku);
            bt -> setGeometry(space*(j/3+1)+(space+side)*j,10+space*(i/3+1)+(space+side)*i,side,side);
            bt -> setObjectName(QString::asprintf("%d%d", i,j));
            connect(bt,SIGNAL(clicked(bool)),this,SLOT(on_board_clicked()));
        }
    }


    // draw the number keypad
    int a = 60;
    int b = 32;
    int space_ = 10;
    for (int i = 0; i < 3; i++){
        for(int j = 0;j < 3; j++){
            QPushButton *bt = new QPushButton(QString::asprintf(" "), ui -> groupBox_Keypad);
            bt -> setGeometry(5+space_*(j/3+1)+(space_+a)*j,20+space_*(i/3+1)+(space_+b)*i,a,b);
            bt -> setObjectName(QString::asprintf("number%d", 3*i+j+1));
            bt -> setText(QString::asprintf("%d", 3*i+j+1));
            connect(bt,SIGNAL(clicked(bool)),this,SLOT(on_keypad_clicked()));
        }
    }


    isStart = false;     //初始为还未计时
    timer = new QTimer(this);  //初始化定时器
    TimeRecord = new QTime(0, 0, 0); //初始化
    ui -> timer_show -> setDigitCount(8);
    ui -> timer_show -> setSegmentStyle(QLCDNumber::Flat);
    ui -> timer_show -> display(TimeRecord->toString("hh:mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


