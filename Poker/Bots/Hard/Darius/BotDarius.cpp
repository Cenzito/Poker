#include "BotDarius.hpp"

float BotDarius::optimalBet()
{
    double optimalBet;
    //compute optimalBet using Kelly's criterion, to be implemented
    return optimalBet;
}
void BotDarius::action(){
    float bet0;
    bet0 = optimalBet();
    int bet=bet0; // computes the optimal bet, uses it to see what action to take
    if (bet > tableInfo.bet_on_table)
    {
        raise(bet-tableInfo.bet_on_table); // raises by the difference between the optimal bet and the current bet if the optimal bet is higher than the current bet
    }
    else if (bet == tableInfo.bet_on_table) // if the optimal bet is equal to the current bet, the bot calls
    {
        call(bet);
    }
    else
    {
        fold();
    }
}
