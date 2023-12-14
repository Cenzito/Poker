#pragma once

#include "../GameLogic/PokerPlayer.hpp"

class Bot : public PokerPlayer {
public :

    Bot(const std::string& name, int level) : PokerPlayer(name) {
        this -> level = level;
    };

   virtual void action(int minAmount, int type) = 0;

protected:
    int level;
};
