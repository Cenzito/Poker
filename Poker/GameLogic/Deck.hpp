#ifndef DECK_HPP
#define DECK_HPP


#include "Card.hpp"
#include "vector"

class Deck {
public:
    Deck();
    void shuffleDeck();
    Card dealCard();

private:
    std::vector<Card> cards;
    int currentCardIndex;
};

#endif // DECK_HPP
