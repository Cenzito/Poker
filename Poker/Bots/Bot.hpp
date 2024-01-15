
#pragma once
#include "../GameLogic/PokerPlayer.hpp"

class Bot : public PokerPlayer {
    Q_OBJECT
public :
    Bot(const std::string& name, int level) : PokerPlayer(name) {

        this -> level = level; //BotCenzo is level 7 (might change)
    };

    virtual void Action();

public slots:
    void call_bet();
    void fold_bet();
    void raise_bet(int amount);

    protected:
        int level;
};
