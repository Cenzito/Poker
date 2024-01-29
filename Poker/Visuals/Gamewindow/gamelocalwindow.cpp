#include "gamelocalwindow.hpp"
#include "ruleswindow.h"
#include "gamewindow.cpp"
#include <qdebug.h>
#include "client.h"
#include "Creationaccount.hpp"
#include "PokerPlayer.hpp"


GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(7)
{
    //make player join the game
    //qDebug() << QString::fromStdString(game_player.getName());

    game.JoinGame(&game_player);

}

void GameLocalWindow::onRaiseButtonClicked() {
    std::string message = "/raise";
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
    qDebug() << add_bet;
    int sum = add_bet + current;
    pokerclient.sendMessage(message + "" + std::to_string(sum));
    pokerclient.send_message = message;
}

void GameLocalWindow::onCallButtonClicked(){ //Reminder: this is check/call button, need to work on changing the name in accordance with the situation, but functionallity should work fine for now
    int current = (ui->cumulative_bet_line->text()).toInt();
    std::string message = "/bet";
    pokerclient.sendMessage(message + ":"+ pokerclient.player.name + ":"+ std::to_string(current));
    pokerclient.send_message = "/bet";
}



void GameLocalWindow::onFoldButtonClicked(){
    std::string message = "/fold";
    pokerclient.sendMessage(message);
    pokerclient.send_message = message;
}

/*
 * switch_bet_button_on() : display the bet button when it is our turn to bet
 *
*/
void GameLocalWindow::switch_bet_button_on(){
    ui->RaiseButton->show();
    ui->FoldButton->show() ;
    ui->CallButton->show();
}

/*
 * switch_bet_button_off() : remove display of the bet button when it is clicked
 *
*/

void GameLocalWindow::switch_bet_button_off(){
    ui->RaiseButton->hide();
    ui->FoldButton->hide() ;
    ui->CallButton->hide();
}

void GameLocalWindow::onNextRoundButtonClicked(){
    std::string message = "/nextRound";
    pokerclient.sendMessage(message);
    pokerclient.send_message = message;
}
