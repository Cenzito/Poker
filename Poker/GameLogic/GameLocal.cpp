#include "GameLocal.hpp"

GameLocal::GameLocal(int seats){;}


int GameLocal::getFreeSeat() {
    Table &t = tableInfo;
    for (int i = 0; i<t.seats; i++) {
        if (t.playerInfo.find(i) == t.playerInfo.end()) {
            return i;
        }
    }
    return -1;
}

void GameLocal::JoinGame(PokerPlayerLocal player) {

    //would need to do a try in case of error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        return;
    } else {
        //player joins game so we add him to the table with an initial amount of money
        PlayerInfo playerinfo(player.getName(), 1000, 0);
        tableInfo.playerInfo.insert({getFreeSeat(), playerinfo});
        players.push_back(player);
        tableInfo.player_num += 1;
    }
    updatePlayersTable();
}

void GameLocal::addBot(Bot bot) {
    GameLocal::JoinGame(bot);
}

void GameLocal::startGame() {
    //need to be more than 3 to play
    for (int i = 0 ; i < 3; i++) {
        newHand();
    }
    /*
    while (tableInfo.player_num >= 3) {
        newHand();
    }*/
    std::cout << "not enough players";
}

void GameLocal::pay(PlayerInfo& PlayerPay, int sum) {
    PlayerPay.stack_size -= sum;
    PlayerPay.bet += sum;
    tableInfo.pot += sum;
    updatePlayersTable();
};

void GameLocal::win(PlayerInfo& PlayerWin, int sum) {
    PlayerWin.stack_size += sum;
    updatePlayersTable();
};

//only consider one player rn
void GameLocal::endHand(PlayerInfo& winner) {
    win(winner, tableInfo.pot);
}

void GameLocal::fold(PlayerInfo& foldPlayer) {
    foldPlayer.isFold = true;
    players_standing -= 1;
}

void GameLocal::updatePlayersTable() {
    for (PokerPlayer& player : players) {
        player.updateTable(tableInfo);
    }
    tableInfo.Print();
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

void GameLocal::newHand() {
    std::cout << "start hand \n\n";

    //setting small and big blind
    pay(tableInfo.playerInfo[(tableInfo.ButtonPlayer + 1) % tableInfo.player_num], tableInfo.SBValue);

    pay(tableInfo.playerInfo[(tableInfo.ButtonPlayer + 2) % tableInfo.player_num], tableInfo.BBValue);

    updatePlayersTable();

    deck.shuffleDeck();
    //give cards to players
    for (PokerPlayer& player : players) {
        std::vector<Card> cards;
        cards.push_back(deck.dealCard());
        cards.push_back(deck.dealCard());
        player.receiveCards(cards);
    }
    //first betting round
    bettingRound((tableInfo.ButtonPlayer + 3)% tableInfo.player_num, true);

    if (players_standing == 1) {
        PlayerInfo winner;
        for (int i = 0; i < tableInfo.player_num; i++) {
            if (!tableInfo.playerInfo[i].isFold) {
                winner = tableInfo.playerInfo[i];
            }
        }
        endHand(winner);
        return;
    }
    //second betting round
    tableInfo.communityCards.push_back(deck.dealCard());
    tableInfo.communityCards.push_back(deck.dealCard());
    tableInfo.communityCards.push_back(deck.dealCard());
    updatePlayersTable();
    bettingRound((tableInfo.ButtonPlayer + 1)%tableInfo.player_num, false);

    if (players_standing == 1) {
        PlayerInfo winner;
        for (int i = 0; i < tableInfo.player_num; i++) {
            if (!tableInfo.playerInfo[i].isFold) {
                winner = tableInfo.playerInfo[i];
            }
        }
        endHand(winner);
        return;
    }
    //third betting round
    tableInfo.communityCards.push_back(deck.dealCard());
    updatePlayersTable();
    bettingRound((tableInfo.ButtonPlayer + 1)% tableInfo.player_num, false);

    if (players_standing == 1) {
        PlayerInfo winner;
        for (int i = 0; i < tableInfo.player_num; i++) {
            if (!tableInfo.playerInfo[i].isFold) {
                winner = tableInfo.playerInfo[i];
            }
        }
        endHand(winner);
        return;
    }
    //fourth and last betting round
    tableInfo.communityCards.push_back(deck.dealCard());
    updatePlayersTable();
    bettingRound((tableInfo.ButtonPlayer + 1)% tableInfo.player_num, false);


    if (players_standing == 1) {
        PlayerInfo winner;
        for (int i = 0; i < tableInfo.player_num; i++) {
            if (!tableInfo.playerInfo[i].isFold) {
                winner = tableInfo.playerInfo[i];
            }
        }
        endHand(winner);
        return;
    } else {
        //get all the people who haven't folded
        std::vector<PlayerInfo> playersNotFold;
        for (int i = 0; i < tableInfo.player_num; i++) {
            if (!tableInfo.playerInfo[i].isFold) {
                playersNotFold.push_back(tableInfo.playerInfo[i]);
            }
        }

        std::vector<Card> community = tableInfo.communityCards;

        //showdown
        PlayerInfo winner = playersNotFold[0];
        std::vector<Card> winnerHandVect;
        merge(community.begin(), community.end(), findPlayer(winner.name).getHand().begin(), findPlayer(winner.name).getHand().end(), winnerHandVect.begin());

        PokerHand winnerHand(winnerHandVect);

        //iterate over players and compute their hand score
        //if their score is better than the current best, they become best
        //haven't taken into account ties yet, in that case, first player considered wins
        for (PlayerInfo current : playersNotFold) {
            std::vector<Card> currentHandVect;
            //getting hands throught the "getHand" function in the PokerPlayer class which is bad
            //need to store the hands of the players in the Game in order to retrieve and compare them
            merge(community.begin(), community.end(), findPlayer(winner.name).getHand().begin(), findPlayer(winner.name).getHand().end(), winnerHandVect.begin());

            PokerHand currentHand(currentHandVect);
            if (compare_hands(winnerHand, currentHand) == 2) {
                winner = current;
                winnerHand = currentHand;
            }
        }
        endHand(winner);
        return;
    }

}




