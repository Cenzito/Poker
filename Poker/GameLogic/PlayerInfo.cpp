#include "PlayerInfo.hpp"




PlayerInfo::PlayerInfo(std::string name, int stack_size, int bet) {this->name=name;this->stack_size=stack_size; this->bet=bet;};


PlayerInfo::PlayerInfo(){
    name = "John";
    stack_size = 1000;
    bet = 0;
};

