#include "gamelocalwindow.hpp"
#include "ui_gamewindow.h"
#include <qdebug.h>
#include <QApplication>

GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(8)
{
    //make player join the game
    //qDebug() << QString::fromStdString(game_player.getName());


    QObject::connect(this, &GameLocalWindow::addBot, &game, &GameLocal::addBot);

    game.JoinGame(&game_player);

}



void GameLocalWindow::onAddBotClicked(){
    int level = 2;
    emit addBot(level);
};
