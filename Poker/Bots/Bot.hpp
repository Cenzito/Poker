
#pragma once
#include "../GameLogic/PokerPlayer.hpp"

class Bot : public PokerPlayer {
public :
    Bot(const std::string& name, int level) : PokerPlayer(name) {

        this -> level = level; //BotCenzo is level 7 (might change)
    };

   virtual signed int Action();

protected:
    int level;
};
