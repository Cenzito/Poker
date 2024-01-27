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

Suit stringToSuit(std::string suit) {
    if (suit == "Spades") {
        return Suit::Spades;
    } else if (suit == "Hearts") {
        return Suit::Hearts;
    } else if (suit == "Diamonds") {
        return Suit::Diamonds;
    } else if (suit == "Clubs") {
        return Suit::Clubs;
    }
}


std::string combinationToString(PokerCombinations combination){
    if(combination==PokerCombinations::HighCard) return "High Card";
    else if(combination==PokerCombinations::Pair) return "Pair";
    else if(combination==PokerCombinations::TwoPairs) return "Two Pairs";
    else if(combination==PokerCombinations::ThreeOfAKind) return "Three of a Kind";
    else if(combination==PokerCombinations::Straight) return "Straight";
    else if(combination==PokerCombinations::Flush) return "Flush";
    else if(combination==PokerCombinations::FullHouse) return "Full House";
    else if(combination==PokerCombinations::FourOfAKind) return "Four of a Kind";
    else if(combination==PokerCombinations::StraightFlush) return "Straight Flush";
    else if(combination==PokerCombinations::RoyalFlush) return "Royal Flush";
    else return "Unknown Combination";
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.toString();
    return os;
}


Card::Card (Suit suit, int value) {
    this->suit = suit;
    this->value = value;
}
bool Card:: operator<(const Card& other_card) const{
    if(value<other_card.value) return true;
    else if(value==other_card.value) {
        if(suit<other_card.suit) return true;
        else return false;
    }
    else return false;
}
bool Card:: operator!=(const Card& other_card) {
    if(value!=other_card.value || suit!=other_card.suit) return true;
    else return false;
}
bool Card:: operator>(const Card& other_card) {
    if(value>other_card.value) return true;
    else if(value==other_card.value) {
        if(suit>other_card.suit) return true;
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
