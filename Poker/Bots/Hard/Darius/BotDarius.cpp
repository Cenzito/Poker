#include "BotDarius.hpp"

float BotDarius::optimalBet()
{
    double optimalBet;
    std::vector<Card> our_hand, table_cards;
    our_hand = getHand();
    table_cards = tableInfo.communityCards; 
    int active_players = tableInfo.player_num;
    std::vector<float> win_probabilities; //to be computed using the win probability function
    

    //compute optimalBet using Kelly's criterion, to be implemented
    return optimalBet;
}
void BotDarius::Action(){
    float bet0;
    bet0 = optimalBet();
    int bet=bet0; // computes the optimal bet, uses it to see what action to take
    int bet_on_table; // the current bet on the table, to be computed using the table informations
    if (bet > bet_on_table)
    {
        bet-bet_on_table; // raises by the difference between the optimal bet and the current bet if the optimal bet is higher than the current bet
    }
    else if (bet == bet_on_table) // if the optimal bet is equal to the current bet, the bot calls
    {
        bet;
    }
    else
    {
        -1;
    }
}
