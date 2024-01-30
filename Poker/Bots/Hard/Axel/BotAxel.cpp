#include "BotAxel.hpp"

#include <cmath>


/*This bot works like the Darius hardbot, but 20% of the games of poker,
 * instead of playing its hand, it bluffs and plays exactly how Darius hardbot would if
 * it had a random strong hand, making all its decisions as if it had,
 * for example, A king of hearts and a queen of spades
 * rather than the actual 2 of spades and 7 of diamond it was dealt.
*/


double randnumb_generator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

BotAxel::BotAxel(const std::string& name) : Bot(name, 10) {

}

float BotAxel::Kelly_Criterion(int &wealth, int &pot, float &win_proba, float &lose_proba, float multiplier){

    float kelly_criterion;
    float delta;
    delta=(pot/wealth-win_proba*multiplier+lose_proba)*(pot/wealth-win_proba*multiplier+lose_proba)+4*multiplier*win_proba*pot/wealth;
    kelly_criterion=(-(pot/wealth-win_proba*multiplier+lose_proba)+sqrt(delta))/(2*multiplier/wealth);
    return kelly_criterion;
}
int BotAxel::optimalBet()
{
    std::vector<Card> our_hand_cardsvector, table_cards_cardsvector;
    int round=tableInfo.communityCards.size();

    if  (round ==0){
        double x = randnumb_generator();
        if (x<= 0.8){
            our_hand_cardsvector = getHand();
            HandThisGame = our_hand_cardsvector;
        }
        else {
            double randvalcard1 = randnumb_generator();
            double randsuitcard1 = randnumb_generator();
            int suitnumcard1 = int(randsuitcard1 * 4);
            int valnumcard1 = int(randvalcard1 *5) + 10;
            double randvalcard2 = randnumb_generator();
            double randsuitcard2 = randnumb_generator();
            int suitnumcard2 = int(randsuitcard2 * 4);
            int valnumcard2 = int(randvalcard2 *5) + 10;
            while (suitnumcard1 == suitnumcard2 and valnumcard1 == valnumcard2 ){
                randvalcard2 = randnumb_generator();
                randsuitcard2 = randnumb_generator();
                suitnumcard2 = int(randsuitcard2 * 4);
                valnumcard2 = int(randvalcard2 *5) + 10;
            }
            Card Card1 = Card(suitnumcard1,valnumcard1);
            Card Card2 = Card(suitnumcard2,valnumcard2);
            HandThisGame = std::vector<Card>{Card1, Card2};
            our_hand_cardsvector = HandThisGame;
        }
    }
    else {
        our_hand_cardsvector = HandThisGame;
    }
    table_cards_cardsvector = tableInfo.communityCards;
    PokerHand our_hand(our_hand_cardsvector);
    PokerHand table_cards(table_cards_cardsvector);

    int active_players = tableInfo.active_players();
    std::vector<float> win_probabilities;
    win_probabilities = Winning_Probability(tableInfo, this->hand, active_players-1, 3000);
    float win_probability = win_probabilities[0];
    float lose_probability = win_probabilities[2];
    int pot;
    int wealth;
    wealth=find_stack_size();
    pot=tableInfo.pot;
    float optimal_bet;
    if( round==0){ /
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,float(0.66*active_players));

    }
    if(round==3){
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability, float(0.33*active_players));
    }
    if(round==4){
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,1.0);;
    }
    if(round==5){
        optimal_bet=Kelly_Criterion(wealth,pot, win_probability,lose_probability,0.75);;

    }
    return int(optimal_bet);
}
void BotAxel::Action(){

    float bet0;
    bet0 = optimalBet();

    int bet=bet0;
    int bet_on_table;
    bet_on_table=tableInfo.current_biggest_bet;



    if (bet > bet_on_table)
    {
        raise_bet(bet);
        return;
    }
    else if (bet == bet_on_table)
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


