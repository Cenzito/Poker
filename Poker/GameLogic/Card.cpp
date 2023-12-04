#include "Card.hpp"

std::string suitToString(Suit suit) {
    if (suit == Suit::Spades) {
        return "Spades";
    } else if (suit == Suit::Hearts) {
        return "Hearts";
    } else if (suit == Suit::Diamonds) {
        return "Diamonds";
    } else if (suit == Suit::Clubs) {
        return "Clubs";
    } else {
        return "Unknown Suit";
    }
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.toString();
    return os;
}


Card::Card (Suit suit, int value) {
    this->suit = suit;
    this->value = value;
}
bool Card:: operator<(const Card& other_card) {
    if(value<other_card.value) return true;
    else if(value==other_card.value) {
        if(suit<other_card.suit) return true;
        else return false;
    }
    else return false;
}
bool Card :: operator == (const Card& other_card){
    if(value==other_card.value && suit==other_card.suit) return true;
    else return false;
}

Suit Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}

std::string Card::toString() const {
    return std::to_string(value) + suitToString(suit);
}
