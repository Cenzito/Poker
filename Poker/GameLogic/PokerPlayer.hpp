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
    const std::string& getName() const;



    void showHand() const;

    //void receiveCards(const std::vector<Card>& hand);


    void receiveCards(const std::vector<Card> cards);
    void removeCards();
    std::vector<Card> getHand() const;

    Table tableInfo;

    //this is not implemented in cpp file
    //virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind

    std::string name;
    std::vector<Card> hand;
    //isActive tells if it's the players turn to bet
    bool isBot, isActive;

    //Action function, will be called when table changes
    int get_percentage(int card1, int card2, bool IsSuited);


public slots:
    virtual void Action();

    void updateTable(std::string command);
    void updatePInf(std::string commandPInf);

signals:
    void Raise(int amount);
    void Fold();
    void Call();

    void callUpdateDisplay();
};







#endif // POKER_PLAYER_HPP
