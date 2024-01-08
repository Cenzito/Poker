#include "gamelocalwindow.hpp"

GameLocalWindow::GameLocalWindow(QWidget *parent, PokerPlayer p) : GameWindow(parent, p), game(5)
{
    //make player join the game
    game.JoinGame(p);
    std::cout << p.name;
}
