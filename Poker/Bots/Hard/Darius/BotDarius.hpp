#ifndef BOTDARIUS_H
#define BOTDARIUS_H

#include "../Bot.hpp" 
#include "../../GameLogic/PokerHand.hpp"
#include "../../GameLogic/Card.hpp"
#include "../../GameLogic/Table.hpp"
#include "../../GameLogic/Game.hpp"

class BotDarius : public Bot
{
public:
    BotDarius() : Bot (name, level){
        this -> level = level;
        this->name = name;
    };
    void action();
    float optimalBet();

    private:



};

#endif // BOTDARIUS_H
