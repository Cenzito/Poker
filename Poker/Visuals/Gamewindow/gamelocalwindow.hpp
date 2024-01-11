#ifndef GAMELOCALWINDOW_HPP
#define GAMELOCALWINDOW_HPP

#include "gamewindow.hpp"
#include "GameLogic/GameLocal.hpp"


class GameLocalWindow : public GameWindow
{
public:
    explicit GameLocalWindow(QWidget *parent = nullptr, PokerPlayer p = PokerPlayer("name"));

    GameLocal game;
};

#endif // GAMELOCALWINDOW_HPP
