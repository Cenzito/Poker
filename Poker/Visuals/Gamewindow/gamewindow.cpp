#include "gamewindow.hpp"
#include "Visuals/RulesWindow/ruleswindow.h"
#include "ui_gamewindow.h"
#include <QPixmap>
#include "GameLogic/table.hpp"
#include"GameLogic/PlayerInfo.hpp"
#include "GameLogic/PokerPlayer.hpp"
#include "GameLogic/Game.hpp"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &GameWindow::onPlayButtonClicked);

    // Loading and setting the image to the QLabel
    QPixmap image("../Poker/Visuals/images/pokertable.jpg");
    ui->label_tablepic->setPixmap(image);
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
void GameWindow::on_dealButton_clicked() {;}


    // see with logic to run from here the function that deals the cards and then return which ones we need to display

    //QImage card_1(GameWindow::Get_image_path("H", "1")); // simply change the arguments to get the card you want
    //QImage card_2(GameWindow::Get_image_path("D", "1")); // simply change the arguments to get the card you want


    //QSize size = ui->label_card1->size();

    //ui->label_card1->setPixmap(QPixmap::fromImage(card_1).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    //ui->label_card2->setPixmap(QPixmap::fromImage(card_2).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this



void GameWindow::onPlayButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}

void GameWindow::on_BetButton_clicked()
{
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
}

void GameWindow::update_to_display(PokerPlayer* player, PlayerInfo* info){
    //bug
    //ui->name_line->setText(QString::fromStdString(player->getName()));
    // need to add the card displays,


    // Update community cards (middle cards)
    update_community_cards();

}


void GameWindow::update_community_cards() {
    Table table;
    const std::vector<Card>& communityCards = table.communityCards;

    // Display the first three community cards initially
    for (int i = 0; i < 3; ++i) {
        update_middle_card_display(i + 1, communityCards[i]);
    }
}

void GameWindow::update_middle_card_display(int cardIndex, const Card& card) {
    QLabel* middleCardLabel = findChild<QLabel*>(QString("label_middlecard%1").arg(cardIndex));
    if (middleCardLabel) {
        // Get the image path for the card
        //QString imagePath = Get_image_path(card.suit, std::to_string(card.getValue()), false);
//many bugs but i will solve them
        // Loading and setting the image to the QLabel
        //QPixmap image(imagePath);
        //ui->middleCardLabel->setPixmap(image);
    }
}


void GameWindow::update_from_display(PokerPlayer* player, PlayerInfo* info){

}



