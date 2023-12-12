#ifndef LOCALGAMEWINDOW_H
#define LOCALGAMEWINDOW_H

#include "gamewindow.hpp"
#include "GameLogic/Game.hpp"
//#include "Bots/Bot.hpp"

class LocalGameWindow : public GameWindow
{
public:
    LocalGameWindow(QWidget *parent);

    void addBot(PokerPlayer bot);

private:
    //have own game
    Game game;
};

#endif // LOCALGAMEWINDOW_H
