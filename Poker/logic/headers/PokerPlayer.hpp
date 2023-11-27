#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>
#include <set>

//TO IMPLEMENT:
//Combinations class that gives which defines what combinations are possible and which are better than others
//add to game class a function that: given player cards and cards in the middle give their combination (and probablity of success later)
//implement betting in the game class


class Card {
public:
    Card(const std::string& suit, int value);
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    static std::set<std::string> names;
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
    virtual void action(int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind

protected:
    std::string name;
    int chips;
    std::vector<Card> hand; 
    bool isBot, isAllin, isFold;
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
