#include "gamewindow.hpp"
#include "ui_gamewindow.h"
#include <QPixmap>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_dealButton_clicked()
{

    // see with logic to run from here the function that deals the cards and then return which ones we need to display

    QImage card_1(":/images/back_card.png"); // simply change the path to replace by whichever card you want/need
    QImage card_2(":/images/back_card.png");
    QImage card_3(":/images/back_card.png");
    QImage card_4(":/images/back_card.png");
    QImage card_5(":/images/back_card.png");

    QSize size = ui->label_card1->size();

    ui->label_card1->setPixmap(QPixmap::fromImage(card_1).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_card2->setPixmap(QPixmap::fromImage(card_2).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_card3->setPixmap(QPixmap::fromImage(card_3).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_card4->setPixmap(QPixmap::fromImage(card_4).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_card5->setPixmap(QPixmap::fromImage(card_5).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}



