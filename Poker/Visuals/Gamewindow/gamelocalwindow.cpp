#include "gamelocalwindow.hpp"

GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(5)
{
    //make player join the game
    game.JoinGame(&game_player);
}
