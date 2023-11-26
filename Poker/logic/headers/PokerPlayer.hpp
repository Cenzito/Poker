#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>

//TO IMPLEMENT:
//Combinations class that gives which defines what combinations are possible and which are better than others
//add to game class a function that: given player cards and cards in the middle give their combination (and probablity of success later)
//implement betting in the game class


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


class PokerPlayer {
public:
    PokerPlayer(const std::string& name, int initialChips);
    const std::string& getName() const { return name; }
    int getChips() const;
    void placeBet(int amount);
    void receiveCards(const std::vector<Card>& cards);
    void showHand() const;
    void winChips(int amount);
    

private:
    std::string name;
    int chips;
    std::vector<Card> hand; 
    
};

class Deck {
public:
    Deck();
    void shuffleDeck();
    Card dealCard();

private:
    std::vector<Card> cards;
    int currentCardIndex;
};


class Game {
public:

    Game(int numOfPlayers);
    void startGame();

private:
    Deck deck;
    std::vector<PokerPlayer> players;
    std::vector<Card> communityCards;
};



#endif // POKER_PLAYER_HPP
