#include "BotDarius.hpp"

int BotDarius::optimalBet()
{
    double optimalBet;
    std::vector<Card> our_hand_cardsvector, table_cards_cardsvector;
    our_hand_cardsvector = getHand();
    table_cards_cardsvector = tableInfo.communityCards; 
    PokerHand our_hand(our_hand_cardsvector); //we create a PokerHand object having a vector of cards 
    PokerHand table_cards(table_cards_cardsvector); //we create a PokerHand object having a vector of cards

    int active_players = tableInfo.player_num;
    std::vector<float> win_probabilities; //to be computed using the win probability function
    win_probabilities = Winning_Probability(tableInfo, *this, active_players, 3000); //we compute the win probabilities for the bot given the current situation
    float win_probability = win_probabilities[0]; //the probability of winning
    int pot;
    pot=tableInfo.pot;
    int wealth;
    wealth=this->chips;
    float optimal_bet;
    optimal_bet=win_probability*wealth/(1+(1-win_probability)/win_probability*wealth);
    //this is a very conservative strategy, we assume that making a certain bet we win just the preexisting pot, and we don't take into account the fact that we can win more money from the other players
    //also, this is prone to lots of errors, judging a big pot as "fruitfull variant", when it may be the fact that players hands are very good
    //so, it needs further improvement
    
    return int(optimalBet);
}
void BotDarius::Action(){
    float bet0;
    bet0 = optimalBet();
    int bet=bet0; // computes the optimal bet, uses it to see what action to take
    int bet_on_table; // the current bet on the table, to be computed using the table informations
    if (bet > bet_on_table)
    {
        return raise_bet(bet-bet_on_table); // raises by the difference between the optimal bet and the current bet if the optimal bet is higher than the current bet
    }
    else if (bet == bet_on_table) // if the optimal bet is equal to the current bet, the bot calls
    {
        return call_bet();
    }
    else
    {
        return fold_bet();
    }
}
