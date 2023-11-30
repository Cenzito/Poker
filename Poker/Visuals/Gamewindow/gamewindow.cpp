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

QString GameWindow::Get_image_path(std::string suit, std::string value, bool back){

    if (back){
        return ":/images/cards/back_card.png";
    }

    std::string temp =  ":/images/cards/"+suit+"/"+value+".png";
    QString final = QString::fromStdString(temp);
    return final;

}
void GameWindow::on_dealButton_clicked()
{

    // see with logic to run from here the function that deals the cards and then return which ones we need to display

    QImage card_1(GameWindow::Get_image_path("H", "1")); // simply change the arguments to get the card you want
    QImage card_2(GameWindow::Get_image_path("D", "1")); // simply change the arguments to get the card you want
    QImage card_3(GameWindow::Get_image_path("S", "1")); // simply change the arguments to get the card you want
    QImage card_4(GameWindow::Get_image_path("C", "1")); // simply change the arguments to get the card you want
    QImage card_5(GameWindow::Get_image_path("H", "12")); // simply change the arguments to get the card you want

    QSize size = ui->label_card1->size();

    ui->label_card1->setPixmap(QPixmap::fromImage(card_1).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    ui->label_card2->setPixmap(QPixmap::fromImage(card_2).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    ui->label_card3->setPixmap(QPixmap::fromImage(card_3).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    ui->label_card4->setPixmap(QPixmap::fromImage(card_4).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    ui->label_card5->setPixmap(QPixmap::fromImage(card_5).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
}



