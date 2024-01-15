#ifndef DEALER_H
#define DEALER_H

#include "card.h"
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>

class Dealer {
public:
    Dealer();
    void shuffleDeck();
    Card dealCard();
    std::vector<Card> dealCommunityCards(int count);
    void burnCard();
    void resetDeck();

private:
    std::vector<Card> deck;
    size_t currentCardIndex;
    void initializeDeck();
};

#endif // DEALER_H
