#ifndef CARD_HPP
#define CARD_HPP
#include "iostream"
enum class PokerCombinations {
    HighCard = 1,
    Pair = 2,
    TwoPairs = 3,
    ThreeOfAKind = 4,
    Straight = 5,
    Flush = 6,
    FullHouse = 7,
    FourOfAKind = 8,
    StraightFlush = 9,
    RoyalFlush = 10
};  // assigns a score to all possible combinations
std::string combinationToString(PokerCombinations combination); //converts the poker combination to a string

enum class Suit {
    Spades = 3,
    Hearts = 2,
    Diamonds = 1,
    Clubs = 0
}; //represent the suit of the card, making them easily comparable

std::string suitToString(Suit suit); //converts the suit to a string
Suit stringToSuit(std::string suit); //converts the string to a suit

class Card {
public:
    Card (Suit suit, int value); //constructor
    friend std::ostream& operator<<(std::ostream& os, const Card& card); //overload the << operator, makes for printing the card easier
    Suit getSuit() const; 
    int getValue() const;
    std::string toString() const;
    bool operator <(const Card& other_card) const; //overload the < operator, makes for comparing the cards easier
    bool operator == (const Card& other_card); //overload the == operator, makes for comparing the cards easier
    bool operator >(const Card& other_card); //overload the > operator, makes for comparing the cards easier
    bool operator !=(const Card& other_card); //overload the != operator
private:
    Suit suit;          // suit represented as an object of the suit class
    int value;        // cards 2 - 14, 13 is king, 14 is ace
};

#endif // CARD_HPP
