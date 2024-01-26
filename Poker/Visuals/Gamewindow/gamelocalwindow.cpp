#include "gamelocalwindow.hpp"
#include <qdebug.h>

GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(7)
{
    //make player join the game
    //qDebug() << QString::fromStdString(game_player.getName());


    game.JoinGame(&game_player);

}
