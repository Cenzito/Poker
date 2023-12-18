#include "table.hpp"


Table::Table(){
    this-> seats = 5;
    smallBlindPlayer=0;
    SBValue = 25;
    BBValue=50;
    pot=0;
    current_player=0;
    player_num=0;
}

Table::Table(int seats){
    this-> seats = seats;
    smallBlindPlayer=0;
    SBValue = 25;
    BBValue=50;
    pot=0;
    current_player=0;
    player_num=0;
}











