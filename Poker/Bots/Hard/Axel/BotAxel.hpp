#ifndef BOTAXEL_H
#define BOTAXEL_H

#include "Bots/Bot.hpp"
#include "GameLogic/PokerHand.hpp"
#include "GameLogic/Card.hpp"
#include "GameLogic/Table.hpp"
#include "GameLogic/Monte_Carlo_Probability_Simulator.hpp"
#include <qdebug.h>


/*This bot works like the Darius hardbot, but 20% of the games of poker,
 * instead of playing its hand, it bluffs and plays exactly how Darius hardbot would if
 * it had a random strong hand, making all its decisions as if it had,
 * for example, A king of hearts and a queen of spades
 * rather than the actual 2 of spades and 7 of diamond it was dealt.
*/

class BotAxel : public Bot
{
public:
    BotAxel(const std::string& name);

    virtual void Action();
    int optimalBet();
    float Kelly_Criterion (int &wealth, int &pot, float &win_proba, float &lose_proba, float multiplier);

private:
    std::vector <Card> HandThisGame;

};

#endif // BOTAXEL_H
