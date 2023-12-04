#include "PlayerInfo.hpp"




PlayerInfo::PlayerInfo(std::string name, int stack_size, int bet) {this->name=name;this->stack_size=stack_size; this->bet=bet;};


std::string PlayerInfo::get_name() {return name;}
int PlayerInfo::get_stack(){return stack_size;};
int PlayerInfo::get_bet(){return bet;};



