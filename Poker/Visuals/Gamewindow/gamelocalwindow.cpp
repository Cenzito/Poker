#include "gamelocalwindow.hpp"
#include "ui_gamewindow.h"
#include <qdebug.h>
#include <QApplication>

GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(8)
{
    //make player join the game
    //qDebug() << QString::fromStdString(game_player.getName());


    QObject::connect(this, &GameLocalWindow::addBot, &game, &GameLocal::addBot);
    QObject::connect(this, &GameLocalWindow::removePlayer, &game, &GameLocal::RemovePlayer);

    game.JoinGame(&game_player);

}



void GameLocalWindow::onAddBotClicked(){
    int level =  ui->AddBot->currentIndex();
    qDebug() << level;
    emit addBot(level);
};

void GameLocalWindow::onKickButtonClicked(int num) {
    return;
}
