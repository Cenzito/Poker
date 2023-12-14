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
    //player = PokerPlayer('John', 3) ;
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

void GameWindow::display_player_hand(PokerPlayer* player){ // to test

    std::vector<Card> H = player->getHand() ; //get the player's hand, to access the cards that need to be displayed
    Card C1 = H[0] ;
    Card C2 = H[1] ;
    Suit S1 = C1.getSuit() ;
    Suit S2 = C2.getSuit() ;
    int v1 = C1.getValue() ;
    int v2 = C2.getValue() ;
    // we have the two cards of the player, the suit and value of both those cards
    // following are the path to both corresponding image cards
    QString p1 = Get_image_path(suitToString(S1),std::to_string(v1)) ;
    QString p2 = Get_image_path(suitToString(S2),std::to_string(v2)) ;
    //below the two images
    QPixmap first_card(p1) ;
    QPixmap second_card(p2) ;
    //display of the player's cards
    ui->label->setPixmap(first_card) ;
    ui ->label_2->setPixmap(second_card) ;

}

void GameWindow::update_to_display(PokerPlayer* player, PlayerInfo* info){


    //bug
    //ui->name_line->setText(QString::fromStdString(player->getName()));
    // need to add the card displays,

}

void GameWindow::update_from_display(PokerPlayer* player, PlayerInfo* info){

}



