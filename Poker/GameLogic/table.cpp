#include "table.hpp"


Table::Table(){this-> seats = 5;}
Table::Table(int seats){this->seats = seats;};



//to implement
void Table::resetHand(){return;}
//to implement
void Table::addBet(){return;}
//to implement
void Table::winMoney(std::string name, int amount){return;}

int Table::getFreeSeat() {
    for (int i = 0; i<seats; i++) {
        if (!(playerInfo.find(i) == playerInfo.end())) {
            return i;
        }
    }
    return -1;
}


void Table::addCard(Card card) {communityCards.push_back(card);}


//new person joins table
void Table::JoinTable(PlayerInfo player) {
    if (player_num >= seats)  {
        return;
    } else {
        playerInfo.insert({getFreeSeat(), player});
    }
}

//to implement
void Table::leaveTable(PlayerInfo player) {return;}






