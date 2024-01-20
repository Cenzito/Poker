#include "dealer.h"


Dealer::Dealer() : currentCardIndex(0) {
    initializeDeck();
    shuffleDeck();
}

void Dealer::initializeDeck() {
    deck.clear();
    for (int suit = Card::Hearts; suit <= Card::Spades; suit++) {
        for (int rank = Card::Two; rank <= Card::Ace; rank++) {
            deck.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }
}

void Dealer::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    currentCardIndex = 0;
}

Card Dealer::dealCard() {
    if (currentCardIndex >= deck.size()) {
        throw std::runtime_error("No more cards to deal");
    }
    return deck[currentCardIndex++];
}

std::vector<Card> Dealer::dealCommunityCards(int count) {
    std::vector<Card> communityCards;
    for (int i = 0; i < count; ++i) {
        communityCards.push_back(dealCard());
    }
    return communityCards;
}

void Dealer::burnCard() {
    if (currentCardIndex >= deck.size()) {
        throw std::runtime_error("No more cards to burn");
    }
    currentCardIndex++; 
}

void Dealer::resetDeck() {
    currentCardIndex = 0;
    initializeDeck();
    shuffleDeck();
}
