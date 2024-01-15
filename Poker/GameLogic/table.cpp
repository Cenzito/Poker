#include "table.hpp"


Table::Table(){
    this-> seats = 5;
    ButtonPlayer=0;
    SBValue = 25;
    BBValue=50;
    pot=0;
    current_player=0;
    player_num=0;
}

Table::Table(int seats){
    this-> seats = seats;
    ButtonPlayer=0;
    SBValue = 25;
    BBValue=50;
    pot=0;
    player_num=0;
    current_player=3;
}




void Table::Print() {
    std::cout << "\n\n\n\n\n\n";
    std::cout << "seats " << seats << "\n";
    std::cout << "number players " << player_num << "\n";
    std::cout << "current player " << current_player << "\n";
    std::cout << "Button player " << ButtonPlayer << "\n";
    std::cout << "SB, BB" << SBValue << " " << BBValue << "\n" << "\n";

    std::cout << "POT " << pot << "\n";

    for (int i = 0; i < player_num; i++ ) {
        playerInfo[i].Print();
        std::cout << "\n";
    }
}


int Table::active_players() {
    int counter=0;
    for (int i=0; i < player_num; i++) {
        if (playerInfo[i].isFold==true) {
            counter+=1;
        }
    }
    return counter;
}






