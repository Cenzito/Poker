#include "gamewindow.hpp"
#include "Visuals/RulesWindow/ruleswindow.h"
#include "ui_gamewindow.h"
#include <QPixmap>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &GameWindow::onPlayButtonClicked);

}

GameWindow::~GameWindow()
{
    delete ui;
}

const QString GameWindow::Get_image_path(const std::string &suit, const std::string &value, bool back){

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


    QSize size = ui->label_card1->size();

    ui->label_card1->setPixmap(QPixmap::fromImage(card_1).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    ui->label_card2->setPixmap(QPixmap::fromImage(card_2).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this

}

void GameWindow::onPlayButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}


