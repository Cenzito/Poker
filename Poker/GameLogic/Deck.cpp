#include "Deck.hpp"
#include <algorithm>
#include <random>
#include <chrono>


Deck::Deck() : currentCardIndex(0) {
    std::string suits[4] = {"H", "D", "C", "S"};
    for (const std::string& suit : suits) {
        for (int value = 1; value <= 13; ++value) {
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
