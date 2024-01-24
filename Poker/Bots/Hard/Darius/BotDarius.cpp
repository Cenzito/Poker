#include "BotDarius.hpp"


BotDarius::BotDarius(const std::string& name) : Bot(name, 10) {

}


int BotDarius::optimalBet()
{
    std::vector<Card> our_hand_cardsvector, table_cards_cardsvector;
    our_hand_cardsvector = getHand();
    table_cards_cardsvector = tableInfo.communityCards; 
    PokerHand our_hand(our_hand_cardsvector); //we create a PokerHand object having a vector of cards 
    PokerHand table_cards(table_cards_cardsvector); //we create a PokerHand object having a vector of cards

    int active_players = tableInfo.active_players();
    std::vector<float> win_probabilities; //to be computed using the win probability function
    win_probabilities = Winning_Probability(tableInfo, this->hand, active_players, 3000); //we compute the win probabilities for the bot given the current situation
    //qDebug() << "wind proba ended";

    float win_probability = win_probabilities[0]; //the probability of winning
    int pot;

    pot=tableInfo.pot;
    //qDebug() << pot;

    int wealth;
    wealth=find_stack_size();
    float optimal_bet;

    optimal_bet=win_probability*wealth/(1+(1-win_probability)/(2*pot)*wealth);
    std::cout<< "WIn_proba= "<<win_probability << "Wealth=  " << wealth << "Optimal bet=  "<< optimal_bet;
    //qDebug() << optimal_bet;
    //this is a very conservative strategy, we assume that making a certain bet we win just the preexisting pot, and we don't take into account the fact that we can win more money from the other players
    //also, this is prone to lots of errors, judging a big pot as "fruitfull variant", when it may be the fact that players hands are very good
    //so, it needs further improvement
   // qDebug() << int(optimal_bet);
    return int(optimal_bet);
}
void BotDarius::Action(){
    //qDebug() << "bot turn";
    float bet0;
    bet0 = optimalBet();
    //qDebug() << "after optimal";
    int bet=bet0; // computes the optimal bet, uses it to see what action to take
    int bet_on_table; // the current bet on the table, to be computed using the table informations
    bet_on_table=tableInfo.current_biggest_bet;

    //qDebug() << "bet" << bet << bet_on_table;

    if (bet > bet_on_table)
    {
        raise_bet(bet); // raises by the difference between the optimal bet and the current bet if the optimal bet is higher than the current bet
        return;
    }
    else if (bet == bet_on_table) // if the optimal bet is equal to the current bet, the bot calls
    {
        call_bet();
        return;
    }
    else
    {
        fold_bet();
        return;

    }
}
