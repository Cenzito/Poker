#ifndef POKER_HAND_HPP
#define POKER_HAND_HPP

#include "Card.hpp"
#include "algorithm"
#include "vector"
#include "string"

class PokerHand{
    public:
    PokerHand( const std::vector <Card> &cards); // constructor
    std::vector<int> get_score(); // computes the score of a given hand, so that we can rank them
    std::vector <Card> get_cards(); // returns the cards
    PokerCombinations get_combination(); // returns the best combination of the hand
    void order_cards(); // orders the cards in the hand in descending order
    bool is_member(Card card); // returns true if the card is in the hand
    bool has_high_card(); // returns true if the hand has a high card
    bool has_pair(); // returns true if the hand has a pair
    bool has_three_of_a_kind(); // returns true if the hand has three of a kind
    bool has_two_pairs(); // returns true if the hand has two pairs
    bool has_straight(); // returns true if the hand has a straight
    int max_straight(); // returns the maximum straight that the hand has (the kicker)
    bool has_flush(); // returns true if the hand has a flush
    bool has_full_house(); // returns true if the hand has a full house
    bool has_four_of_a_kind(); // returns true if the hand has four of a kind
    bool has_straight_flush(); // returns true if the hand has a straight flush
    bool has_royal_flush(); // returns true if the hand has a royal flush

    private:
    std::vector<Card> cards; //the cards that will be used to make the hand
    

};
int compare_hands(PokerHand hand1, PokerHand hand2); // compares two hands and returns 1 if the first hand is better, 2 if the second hand is better and 0 if they are equal
#endif // POKER_HAND_HPP