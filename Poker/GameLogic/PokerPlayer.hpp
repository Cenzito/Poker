#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>
#include <set>
#include "Table.hpp"
#include "Card.hpp"
#include <unordered_map>
#include <QObject>




class PokerPlayer : public QObject {
    Q_OBJECT
public:
    PokerPlayer(const std::string& name);
    const std::string& getName() const; //returns the name of the player



    void showHand() const; //prints the hand of the player

    //void receiveCards(const std::vector<Card>& hand);


    void receiveCards(const std::vector<Card> cards); //initializes the hand of a player with the cards it receives as argument
    void removeCards(); //removes the cards from the player's hand
    std::vector<Card> getHand() const; //returns the hand of the player

    Table tableInfo;  // each player has a state of the table available 
    //this is not implemented in cpp file
    //virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind

    std::string name; //keeps the name of the player
    std::vector<Card> hand; //keeps the cards of a player
    //isActive tells if it's the players turn to bet
    bool isBot; //boolean to identify for the players that are bots 
    bool isActive; // boolean to identify for the active players at a given stage of the game


    int get_percentage(int card1, int card2, bool IsSuited);


public slots:
    virtual void Action();

    void updateTable(std::string command); //send a specific command to the table to update it
    void updatePInf(std::string commandPInf); // initializes the table information for new joiners in the game.

signals:
    void Raise(int amount);
    void Fold();
    void Call();
    void nextGame();

    void callUpdateDisplay(); //signal making the connection between the logic and the visual part of the project
};







#endif // POKER_PLAYER_HPP
