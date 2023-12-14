#include "PokerHand.hpp"
#include "PokerPlayer.hpp"
#include "Deck.hpp"
#include <iostream>
#include "Table.hpp"
// function that for any given hand, number of current players, state of the table, computes the probability of winning, making draws or losing
std::vector<float> Winning_Probability (Table table, PokerPlayer player, int num_players, int num_simulations) {
    int wins = 0; //number of times player wins
    int losses = 0; //number of times player loses
    int ties = 0; //number of times player ties
    int k=0; //auxiliary variable
    std::vector<Card> our_hand, community_cards; //vector of community cards
    our_hand=player.hand;
    std::vector<std::vector<Card>> hands; //vector of hands of other players
    std::vector<PokerHand> final_hands; //vector of PokerHand objects of other players
    Deck deck;
    for (int i = 0; i < num_simulations; i++) { // we iterate through the number of simulations
        deck.shuffleDeck(); //for each simulation, we shuffle the deck
        for (int j=0; j<num_players; j++) { //for each simulation, we construct the hand of the other players
            for (k=0; k<2; k++) { //for each player, we iterate through the 2 cards in his hand and construct both
                if(deck.getCurrentCard()!= player.hand[0] && deck.getCurrentCard()!= player.hand[1]) { // we ignore the cards that the first player already has when dealing cards
                    hands[j].push_back(deck.dealCard());
                }
                
            }
        } //now we finished constructing the hand
    community_cards=table.communityCards;
    while (community_cards.size()<5) { //we deal the community cards up until we have 5
        if(deck.getCurrentCard()!= player.hand[0] && deck.getCurrentCard()!= player.hand[1]) { // we ignore the cards that the first player already has when dealing cards
            community_cards.push_back(deck.dealCard());
        }
    }//so, we constructed at random a final stage of the game and possible combinations of hands for the other players. We now check the winner
    our_hand.emplace_back(community_cards[0]);
    our_hand.emplace_back(community_cards[1]);
    our_hand.emplace_back(community_cards[2]);
    our_hand.emplace_back(community_cards[3]);
    our_hand.emplace_back(community_cards[4]); // create a hand with all cards corresponding to the player
    PokerHand ourhand(our_hand); //we make it a PokerHand object so that we can use the functions
    int ok=0; // we use it as an indicator to check if we win or lose or draw
    for (int j=0; j<num_players; j++) { //we construct the final hand of the other players
        
        hands[j].emplace_back(community_cards[0]);
        hands[j].emplace_back(community_cards[1]);
        hands[j].emplace_back(community_cards[2]);
        hands[j].emplace_back(community_cards[3]);
        hands[j].emplace_back(community_cards[4]); // create a hand with all cards corresponding to the player
        final_hands[j]=PokerHand(hands[j]); //we make it a PokerHand object so that we can use the functions
        if(compare_hands(ourhand,final_hands[j])==2) {ok=2; break;} //if we lose against a player, we set ok to 2, and we know for sure we lost so we break
        if(compare_hands(ourhand,final_hands[j])==0) {ok=0;} //if we draw against a player, we set ok to 0, so we know for sure we cannot win and continue checking for possible losses
    }
    if(ok==0) {ties++;} //if we end with 0 then there were draws but no losses against other players so we draw
    if(ok==2) {losses++;} //if we end with 2 then we lost against at least one player so we lose
    if(ok==1) {wins++;} //if we end with 1 then we won against all players so we win
    }
    std::vector<float> probabilities={float(wins)/float(num_simulations), float(ties)/float(num_simulations), float(losses)/float(num_simulations)}; //we return the probabilities
    return probabilities;
}