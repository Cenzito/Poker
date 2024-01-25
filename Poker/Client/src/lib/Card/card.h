#ifndef CARD_H
#define CARD_H

#include <string>
#include <array>

class Card {
public:
    enum Suit { Hearts, Diamonds, Clubs, Spades };
    enum Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace }; 

    Card(const Rank& rank, const Suit& suit);
    std::string toString() const;

    bool operator <(const Card& other_card) const; 
    bool operator == (const Card& other_card); 
    bool operator >(const Card& other_card); 
    bool operator !=(const Card& other_card); 

private:
    Rank rank;
    Suit suit;
    static const std::array<std::string, 13> rankNames;
    static const std::array<std::string, 4> suitNames;
};

#endif // CARD_H
