#include "PlayerInfo.hpp"




PlayerInfo::PlayerInfo(std::string name, int stack_size, int bet) {this->name=name;this->stack_size=stack_size; this->bet=bet;};


PlayerInfo::PlayerInfo(){
    name = "John";
    stack_size = 1000;
    bet = 0;
};



void PlayerInfo::Print() {
    std::cout << "name " << name << "\n";
    std::cout << "stack_size " << stack_size << "\n";
    std::cout << "Bet " << bet << "\n";
    std::cout << "IsFold IsAllin " << isFold << isAllin << "\n";
};
