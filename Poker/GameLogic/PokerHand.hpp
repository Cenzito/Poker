#ifndef POKER_HAND_HPP
#define POKER_HAND_HPP

#include "Card.hpp"
#include "algorithm"
#include "vector"
#include "string"

class PokerHand{
    public:
    PokerHand( std::vector <Card> cards); // constructor
    int get_score(); // computes the score of a given hand, so that we can rank them
    std::vector <Card> get_cards(); // returns the cards
    PokerCombinations get_combination(); // returns the best combination of the hand
    void order_cards(); // orders the cards in the hand, so that we can easily check for combinations
    bool is_high_card(); // returns true if the hand has a high card
    bool is_pair(); // returns true if the hand has a pair
    bool is_three_of_a_kind(); // returns true if the hand has three of a kind
    bool is_two_pairs(); // returns true if the hand has two pairs
    bool is_straight(); // returns true if the hand has a straight
    bool is_flush(); // returns true if the hand has a flush
    bool is_full_house(); // returns true if the hand has a full house
    bool is_four_of_a_kind(); // returns true if the hand has four of a kind
    bool is_straight_flush(); // returns true if the hand has a straight flush
    bool is_royal_flush(); // returns true if the hand has a royal flush

    private:
    std::vector<Card> cards; //the cards that will be used to make the hand


};

#endif // POKER_HAND_HPP