#include "GameLocal.hpp"


GameLocal::GameLocal(int seats): Game(seats) {;}


void GameLocal::JoinGame(PokerPlayerLocal player) {

    //would need to do a try in case of error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        return;
    } else {
        //player joins game so we add him to the table with an initial amount of money
        PlayerInfo playerinfo = PlayerInfo(player.getName(), 1000, 0);
        tableInfo.playerInfo.insert({getFreeSeat(), playerinfo});
        players.push_back(player);
    }
    updatePlayersTable();
}

void GameLocal::addBot(PokerPlayerLocal bot) {
    GameLocal::JoinGame(bot);
    updatePlayersTable();
}


void GameLocal::pay(PlayerInfo& PlayerPay, int sum) {
    PlayerPay.stack_size -= sum;
    updatePlayersTable();
};

void GameLocal::win(PlayerInfo& PlayerWin, int sum) {
    PlayerWin.stack_size += sum;
    updatePlayersTable();
};

//only consider one player rn
void GameLocal::endHand(PlayerInfo& winner) {
    win(winner, tableInfo.pot);
    nextHand();
}

void GameLocal::fold(PlayerInfo& foldPlayer) {
    //returns a boolean
    //if we need to end the round ( 1 player remaining), return false
    //otherwise: return true
    foldPlayer.isFold = true;
    players_standing -= 1;
}

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
    tableInfo.ButtonPlayer += 1;
    tableInfo.communityCards=std::vector<Card>();
    hand_finished = false;
    updatePlayersTable();
}

signed int GameLocal::askAction(PokerPlayerLocal player) {
    return player.Action();
}

void GameLocal::bettingRound(int first_player, bool isfirst_round) {
    int first_actor = first_player;
    tableInfo.current_player = first_player;
    int current_biggest_bet = 0;
    if (isfirst_round) {
        current_biggest_bet = tableInfo.BBValue;
    }
    do {
        //go over players asking for a bet
        if (tableInfo.playerInfo.find(tableInfo.current_player) != tableInfo.playerInfo.end()) {
            PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];

            signed int bet = askAction(findPlayer(currentPlayerInfo.name));
            if (bet == -1) {
                fold(currentPlayerInfo);
            } else if (bet == 0) {
                //if doesn't have the money to bet: fold
                if (currentPlayerInfo.stack_size + currentPlayerInfo.bet < current_biggest_bet){
                    fold(currentPlayerInfo);
                } else {
                    currentPlayerInfo.bet = current_biggest_bet;
                }
            }
            else{
                //if bets too little or doesn't have the money to bet: fold
                if (currentPlayerInfo.stack_size < bet || bet + currentPlayerInfo.bet < current_biggest_bet) {
                    fold(currentPlayerInfo);
                } else {
                    currentPlayerInfo.bet += bet;
                    current_biggest_bet = currentPlayerInfo.bet;
                    first_actor = tableInfo.current_player;
                }
            }
        }
        tableInfo.current_player = (tableInfo.current_player + 1) % tableInfo.seats;
    } while (first_actor != tableInfo.current_player && players_standing > 1); // continue until same person that put the highest bet needs to bet again or only one person left
}

PokerPlayerLocal GameLocal::findPlayer(std::string name) {
    for (PokerPlayerLocal& player : players) {
        if (player.name == name) {
            return player;
        }
    }
};

void GameLocal::testGameLocal(int num_rounds){
    //add 2 bots
    //initialize the table

}






