#ifndef CARD_HPP
#define CARD_HPP
#include "iostream"

class Card {
public:
    Card(const std::string& suit, int value);
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    std::string getSuit() const;
    int getValue() const;
    std::string toString() const;

private:
    std::string suit; // 'H' is heart 'D' is diamond etc.
    int value;        // cards 1 - 13, 13 is king
};

#endif // CARD_HPP
