#ifndef GAMELOCALWINDOW_HPP
#define GAMELOCALWINDOW_HPP

#include "gamewindow.hpp"
#include "GameLogic/GameLocal.hpp"


class GameLocalWindow : public GameWindow
{
    Q_OBJECT
public:
    explicit GameLocalWindow(QWidget *parent = nullptr, std::string p = "name");

    GameLocal game;

    void onAddBotClicked();

    void onKickButtonClicked(int);
    signals:
        void addBot(int level);
        void removePlayer(std::string name);
};

#endif // GAMELOCALWINDOW_HPP
