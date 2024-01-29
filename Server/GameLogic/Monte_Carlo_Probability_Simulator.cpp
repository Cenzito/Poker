#include "Monte_Carlo_Probability_Simulator.hpp"
// function that for any given hand, number of current players, state of the table, computes the probability of winning, making draws or losing
#include <qdebug.h>


std::vector<float> Winning_Probability (Table &table, std::vector<Card> &hand, int num_players, int num_simulations) { //num_players is the number of other players

    //std::cout<<"Entered the function!"<<std::endl;
    //if (num_players==0){
        //num_players= table.active_players();
    //}
    int wins = 0; //number of times player wins
    int losses = 0; //number of times player loses

    int ties = 0; //number of times player ties
    std::vector<Card> community_cards; //vector of community cards

    Deck deck; //create a deck
    //qDebug() <<"Initialisation worked!";
    //std::cout<<"Number of players: "<<num_players<<std::endl;
    //std::cout<<"Number of simulations: "<<num_simulations<<std::endl;
    //std::cout<<"Our cards: "<<hand[0]<<" "<<hand[1]<<std::endl;
    for (int i = 0; i < num_simulations; i++) { // we iterate through the number of simulations

        std::vector<Card> our_hand=hand; //we reconstruct the hand of the first player at each simulation
        //std::cout<<"Entered the for loop!"<<std::endl;

        std::vector<std::vector<Card>> hands; //vector of hands of other players
        for (int l=0; l<num_players; l++) {hands.emplace_back(std::vector<Card>());} //initialise the vector of hands of other players
        std::vector<PokerHand> final_hands; //vector of PokerHand objects of other players
        for (int l=0; l<num_players; l++) {final_hands.emplace_back(PokerHand(std::vector<Card>()));} //initialise the vector of PokerHand objects of other players
        //std::cout<<"Number of players: "<<num_players<<std::endl;
        //std::cout<<"Number of simulations: "<<num_simulations<<std::endl;
        deck.shuffleDeck(); //for each simulation, we shuffle the deck
        //std::cout<<"Shuffled the deck!"<<std::endl;
        //qDebug() <<"trial "<<i<<" out of "<<num_simulations;
        for (int j=0; j<num_players; j++) { //for each simulation, we construct the hand of the other players
            //std::cout<<"Player "<<j<<std::endl;
            for (int k=0; k<2; k++) { //for each player, we iterate through the 2 cards in his hand and construct both
                //std::cout<<"Card "<<k<<std::endl;

                if(deck.getCurrentCard() != our_hand[0] && deck.getCurrentCard()!= our_hand[1]) { // we ignore the cards that the first player already has when dealing cards
                   // std::cout<<"added card "<<deck.getCurrentCard()<<" to player "<<j<<" for card "<<k<<std::endl;
                    hands[j].push_back(deck.dealCard()); 

                    //std::cout<<"Dealt a card!"<<std::endl;
                }
                else {deck.dealCard();  k--;} //if the card is already in the hand of the first player, we ignore it and deal the next one

            }
        } //now we finished constructing the hand
        //qDebug()<< "Constructed the hands!";

    community_cards=table.communityCards;
    while (community_cards.size()<5) { //we deal the community cards up until we have 5
        if(deck.getCurrentCard()!= our_hand[0] && deck.getCurrentCard()!= our_hand[1]) { // we ignore the cards that the first player already has when dealing cards
            community_cards.push_back(deck.dealCard());
           // std::cout<<"Dealt a card!"<<std::endl;
        }
        else {deck.dealCard(); } //if the card is already in the hand of the first player, we ignore it and deal the next one
    }//so, we constructed at random a final stage of the game and possible combinations of hands for the other players. We now check the winner
    //std::cout<<"Constructed the community cards!"<<" of size "<<community_cards.size()<<std::endl;
    our_hand.emplace_back(community_cards[0]);
    our_hand.emplace_back(community_cards[1]);
    our_hand.emplace_back(community_cards[2]);
    our_hand.emplace_back(community_cards[3]);
    our_hand.emplace_back(community_cards[4]); // create a hand with all cards corresponding to the player
    //std::cout<<"Constructed our hand!"<<std::endl;
    PokerHand ourhand(our_hand); //we make it a PokerHand object so that we can use the functions
    //std::cout<<"Our hand is "<<combinationToString(ourhand.get_combination())<<std::endl;
   // std::cout<<"Constructed our Pokerhand object!"<<std::endl;
    int ok=1; // we use it as an indicator to check if we win or lose or draw
    for (int j=0; j<num_players; j++) { //we construct the final hand of the other players
       // std::cout<<"Player "<<j<<std::endl;
        hands[j].emplace_back(community_cards[0]);
        hands[j].emplace_back(community_cards[1]);
        hands[j].emplace_back(community_cards[2]);
        hands[j].emplace_back(community_cards[3]);
        hands[j].emplace_back(community_cards[4]); // create a hand with all cards corresponding to the player
        //std::cout<<"Constructed the hand of player "<<j<<std::endl;
        final_hands[j]=PokerHand(hands[j]); //we make it a PokerHand object so that we can use the functions
        //std::cout<<"Player "<<j<<" has " <<combinationToString(final_hands[j].get_combination())<<std::endl;
        if(compare_hands(ourhand,final_hands[j])==2) {ok=2; break;} //if we lose against a player, we set ok to 2, and we know for sure we lost so we break
        if(compare_hands(ourhand,final_hands[j])==0) {ok=0;} //if we draw against a player, we set ok to 0, so we know for sure we cannot win and continue checking for possible losses
        //std::cout<<"At stage "<<j<<" ok is "<<ok<<std::endl;
    }
    if(ok==0) {ties++; } //if we end with 0 then there were draws but no losses against other players so we draw
    if(ok==2) {losses++;} //if we end with 2 then we lost against at least one player so we lose
    if(ok==1) {wins++;} //if we end with 1 then we won against all players so we win

    }
    std::vector<float> probabilities={float(wins)/float(num_simulations), float(ties)/float(num_simulations), float(losses)/float(num_simulations)}; //we return the probabilities
    return probabilities;
}
