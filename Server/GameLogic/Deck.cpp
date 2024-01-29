#include "Deck.hpp"
#include <algorithm>
#include <random>
#include <chrono>


Deck::Deck() : currentCardIndex(0) {
    Suit suits[4] = {Suit:: Spades, Suit:: Hearts, Suit:: Diamonds, Suit:: Clubs};
    for (const Suit& suit : suits) {
        for (int value = 2; value <= 14; ++value) {
            cards.emplace_back(suit, value);
        }
    }
    shuffleDeck();
}



void Deck::shuffleDeck() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


    std::mt19937 engine(seed);
    std::shuffle(cards.begin(), cards.end(), engine);
    currentCardIndex = 0;
}


Card Deck::dealCard() {
    if (currentCardIndex < cards.size()) {
        return cards[currentCardIndex++];
    } else {
        throw std::out_of_range("No more cards in the deck");
    }
}
Card Deck::getCurrentCard() const {
    return cards[currentCardIndex];
}