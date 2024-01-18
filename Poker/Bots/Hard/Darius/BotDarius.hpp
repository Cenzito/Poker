#ifndef BOTDARIUS_H
#define BOTDARIUS_H

#include "Bots/Bot.hpp"
#include "GameLogic/PokerHand.hpp"
#include "GameLogic/Card.hpp"
#include "GameLogic/Table.hpp"
#include "GameLogic\Monte_Carlo_Probability_Simulator.cpp"

class BotDarius : public Bot
{
public:
    BotDarius() : Bot (name, level){
        this -> level = level;
        this->name = name;
    };
    void Action(); //returns the optimal action of the bot
    int optimalBet();
    
    private:



};

#endif // BOTDARIUS_H
