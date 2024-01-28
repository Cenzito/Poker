#include "PlayerInfo.hpp"
#include <QApplication>



PlayerInfo::PlayerInfo(std::string name, int stack_size, int bet) {
    this->name=name;
    this->stack_size=stack_size;
    this->bet=bet;
    this->isAllin = false;
    this->isFold = false;
};

PlayerInfo::PlayerInfo(){}


void PlayerInfo::Print() {
    /*
    qDebug() << "name " << QString::fromStdString(name);
    qDebug() << "stack_size " << stack_size;
    qDebug() << "Bet " << bet;
    qDebug() << "IsFold IsAllin " << isFold << isAllin;
    if (cards.size() == 2) {
        qDebug() << "Cards " << QString::fromStdString(cards[0].toString()) << " " << QString::fromStdString(cards[1].toString());
    }
*/
};

