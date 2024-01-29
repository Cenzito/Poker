#ifndef BOTDARIUS_H
#define BOTDARIUS_H

#include "Bots/Bot.hpp"

class BotDarius : public Bot
{
public:
    BotDarius(const std::string& name);

    virtual void Action(); //returns the optimal action of the bot
    int optimalBet();
    float Kelly_Criterion (int &wealth, int &pot, float &win_proba, float &lose_proba, float multiplier);
    //we apply Kelly's criterion, instead of considering the pot as the expected win (in case of win) we also consider a multiplier
    //that is computed considering the stage of the game. For example, expecting that 3 other people will call my bet
    //the odds will increase by 3. Thus, the Kelly's criterion optimal bet should verify:
    //bet/wealth=win_proba -lose_proba/(pot/bet+multiplier), which is a quadratic equation

    private:



};

#endif // BOTDARIUS_H
