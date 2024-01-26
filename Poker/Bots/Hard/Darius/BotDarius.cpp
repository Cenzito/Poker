#include "BotDarius.hpp"


BotDarius::BotDarius(const std::string& name) : Bot(name, 10) {

}

float::Kelly_Criterion(int &wealth, int &pot, float &win_proba, float &lose_proba, float &multiplier){
    
    float kelly_criterion;
    float delta;
    delta=(pot/wealth-win_proba*multiplier+lose_proba)^2+4*multiplier*win_proba*pot/wealth;
    kelly_criterion=(-(pot/wealth-win_proba*multiplier+lose_proba)+sqrt(delta))/(2*multiplier/wealth);
    return kelly_criterion;
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
    float lose_probability = win_probabilities[2]; //the probability of losing
    std::cout<<"lose proba= "<<lose_probability<<std::endl;
    int pot;
    int wealth;
    wealth=find_stack_size();
    pot=tableInfo.pot;
    int round=tableInfo.communityCards.size();
    
    if( round==0){ //we are in the preflop
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,3/4*active_players); //we have higher odds in the preflop where a lot of people might join
        std::cout<<"pot: "<<pot<<" wealth: "<<wealth<<" active players: "<<active_players<<" odds: "<<odds;

    }
    if(round==3){ //we are in the flop
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,1/2*active_players); //we have lower odds in the flop where less people might join, we can expect half of the players to remain in game
        std::cout<<"round: "<<round<<" odds: "<<odds<<std::endl;
    }
    if(round==4){ //we are in the turn
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,1);; //we have lower odds in the turn where less people might join
        std::cout<<"round: "<<round<<" odds: "<<odds<<std::endl;
    }
    if(round==5){ //we are in the river
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,3/4);; //we have lower odds in the river where less people might join
        std::cout<<"round: "<<round<<" odds: "<<odds<<std::endl;
    }
    //qDebug() << pot;

    
    float optimal_bet, optimal_percentage;
    optimal_percentage=win_probability-(lose_probability/odds); //we compute the optimal percentage of wealth to bet
    optimal_bet=optimal_percentage*wealth; //we compute the optimal bet
    std::cout<< "WIn_proba= "<<win_probability << "Wealth=  " << wealth << "Optimal bet=  "<< optimal_bet<<" lose proba:"<<lose_probability<<" optimal_percentage "<<optimal_percentage<<" odds "<<odds<<" round: "<<round;
    //qDebug() << optimal_bet;
    //tried to account for different dynamics in different stages of the game
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
