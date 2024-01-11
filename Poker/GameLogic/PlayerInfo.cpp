#include "PlayerInfo.hpp"
#include <QApplication>



PlayerInfo::PlayerInfo(std::string name, int stack_size, int bet) {this->name=name;this->stack_size=stack_size; this->bet=bet;};


PlayerInfo::PlayerInfo(){
    name = "John";
    stack_size = 1000;
    bet = 0;
};



void PlayerInfo::Print() {
    qDebug() << "name " << QString::fromStdString(name);
    qDebug() << "stack_size " << stack_size;
    qDebug() << "Bet " << bet;
    qDebug() << "IsFold IsAllin " << isFold << isAllin;
};
