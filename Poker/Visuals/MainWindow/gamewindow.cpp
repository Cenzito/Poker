#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "QPixmap"
#include "iostream"
#include <QVBoxLayout>
#include <QDir>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    qDebug() << QDir::currentPath();
    QPixmap pix("../Poker/Visuals/Gamewindow/poker_table.jpeg");


    int w = ui->label_table->width();
    int l = ui->label_table->height();

    ui->label_table->setPixmap(pix.scaled(w,l, Qt::KeepAspectRatio));

    layout->addWidget(ui->label_table);

}

GameWindow::~GameWindow()
{
    delete ui;
}
