#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "QPixmap"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/anato/OneDrive/Desktop/Bachelor Year 2/CSE201/Poker/poker_table.jpeg");
    int w = ui->label_table->width();
    int l = ui->label_table->height();
    ui->label_table->setPixmap(pix.scaled(w,l, Qt::KeepAspectRatio));
}

GameWindow::~GameWindow()
{
    delete ui;
}
