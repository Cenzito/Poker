#include "Card.hpp"



std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.toString();
    return os;
}


Card::Card(const std::string& suit, int value) : suit(suit), value(value) {}

std::string Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}

std::string Card::toString() const {
    return std::to_string(value) + suit;
}
