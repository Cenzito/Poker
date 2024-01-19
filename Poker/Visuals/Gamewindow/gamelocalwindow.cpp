#include "gamelocalwindow.hpp"
#include <qdebug.h>
#include "client.h"

GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(5)
{
    //make player join the game
    qDebug() << QString::fromStdString(game_player.getName());


    game.JoinGame(&game_player);

}

void GameLocalWindow::onRaiseButtonClicked() override{
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
    qDebug() << add_bet;
    //emit game_player.Raise(add_bet);
    sendMessage("\bet");
}

void GameLocalWindow::onCallButtonClicked() override{ //Reminder: this is check/call button, need to work on changing the name in accordance with the situation, but functionallity should work fine for now
    //emit game_player.Call();
    sendMessage("\call");
}



void GameLocalWindow::onFoldButtonClicked() override{
    emit game_player.Fold();
    sendMessage("\fold");
}
