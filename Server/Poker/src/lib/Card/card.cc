#include "card.h"

const std::array<std::string, 13> Card::rankNames = {
    "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
};

const std::array<std::string, 4> Card::suitNames = {
    "Hearts", "Diamonds", "Clubs", "Spades"
};

Card::Card(const Rank& rank, const Suit& suit)
    : rank(rank), suit(suit) {}

std::string Card::toString() const {
    return rankNames[rank - 2] + " of " + suitNames[suit];
}

bool Card:: operator < (const Card& other_card) const{
    if(rank < other_card.rank) return true;
    else if(rank == other_card.rank) {
        if(suit < other_card.suit) return true;
        else return false;
    }
    else return false;
}

bool Card:: operator != (const Card& other_card) {
    if(rank != other_card.rank || suit != other_card.suit) return true;
    else return false;
}

bool Card:: operator > (const Card& other_card) {
    if(rank > other_card.rank) return true;
    else if(rank == other_card.rank) {
        if(suit > other_card.suit) return true;
        else return false;
    }
    else return false;
}

bool Card :: operator == (const Card& other_card){
    if(rank == other_card.rank && suit == other_card.suit) return true;
    else return false;
}
