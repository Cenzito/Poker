
#pragma once
#include "../GameLogic/PokerPlayer.hpp"

class Bot : public PokerPlayer {
public :
    Bot(const std::string& name, int level) : PokerPlayer(name) {

        this -> level = level;
    };

   virtual void Action();

protected:
    int level;
};
