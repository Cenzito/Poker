#include "GameLocal.hpp"

GameLocal::GameLocal() : Game(5)
{

}


void GameLocal::JoinGame(PokerPlayer player) {

    //player joins game so we add him to the table with an initial amount of money
    PlayerInfo playerinfo = PlayerInfo(player.getName(), 1000, 0);

    getFreeSeat();
    //would need to do a try in case of error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        return;
    } else {
        tableInfo.playerInfo.insert({getFreeSeat(), playerinfo});
        players.push_back(player);
    }
}

void GameLocal::addBot(PokerPlayer bot) {
    GameLocal::JoinGame(bot);
}


void GameLocal::pay(int position, int sum) {
    tableInfo.playerInfo[position].stack_size -= sum;
};
void GameLocal::win(int position, int sum) {
    tableInfo.playerInfo[position].stack_size += sum;
};


void GameLocal::updatePlayersTable() {
    for (PokerPlayer& player : players) {
        player.updateTable(tableInfo);
    }
}


void GameLocal::nextHand(){
    for (PokerPlayer& player : players) {
        player.removeCards();
    }

    tableInfo.pot=0;
    tableInfo.smallBlindPlayer += 1;
    tableInfo.communityCards=std::vector<Card>();
}








