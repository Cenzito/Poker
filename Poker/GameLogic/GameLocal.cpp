#include "GameLocal.hpp"
#include <QApplication>

GameLocal::GameLocal(int seats): tableInfo(seats){
}

int GameLocal::getFreeSeat() {
    Table &t = tableInfo;
    for (int i = 0; i<t.seats; i++) {
        if (t.playerInfo.find(i) == t.playerInfo.end()) {
            return i;
        }
    }
    return -1;
}

void GameLocal::JoinGame(PokerPlayer* player) {

    //would need to do a try in case of error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        return;
    } else {
        //player joins game so we add him to the table with an initial amount of money
        PlayerInfo playerinfo(player->getName(), 1000, 0);
        tableInfo.playerInfo.insert({getFreeSeat(), playerinfo});
        players.push_back(player);
        tableInfo.player_num += 1;


        //connect slots to signals
        QObject::connect(player, &PokerPlayer::Call, this, &GameLocal::onCall);
        QObject::connect(player, &PokerPlayer::Fold, this, &GameLocal::onFold);
        QObject::connect(player, &PokerPlayer::Raise, this,&GameLocal::onRaise);
        QObject::connect(this, &GameLocal::updatePTable, player, &PokerPlayer::updateTable);

    }
    updatePlayersTable();
}

void GameLocal::addBot(Bot* bot) {
    GameLocal::JoinGame(bot);
}


void GameLocal::pay(PlayerInfo& PlayerPay, int sum) {
    PlayerPay.stack_size -= sum;
    PlayerPay.bet += sum;
    tableInfo.pot += sum;

};

void GameLocal::win(PlayerInfo& PlayerWin, int sum) {

    //add thimgy here

    qDebug() << sum;
    for (int i = 0; i <= tableInfo.player_num; i++) {
        if (tableInfo.playerInfo[i].name == PlayerWin.name) {
            tableInfo.playerInfo[i].stack_size += sum;
        }
    }
};

//only consider one player winning rn
void GameLocal::endHand(PlayerInfo& winner) {
    win(winner, tableInfo.pot);

    updatePlayersTable();
    nextHand();
}

void GameLocal::fold(PlayerInfo& foldPlayer) {
    foldPlayer.isFold = true;
    players_standing -= 1;
}

void GameLocal::updatePlayersTable() {
    emit updatePTable(tableInfo);
    tableInfo.Print();
}



void GameLocal::nextHand(){
    for (PokerPlayer* player : players) {
        player->removeCards();
    }
    //reset bets
    for (int i = 0; i <= tableInfo.player_num; i++) {
        tableInfo.playerInfo[i].bet = 0;
        tableInfo.playerInfo[i].isAllin = false;
        tableInfo.playerInfo[i].isFold = false;
    }
    //reset bets
    /*for (int i = 0; i <= tableInfo.player_num; i++) {
        tableInfo.playerInfo[i].bet = 0;
        tableInfo.playerInfo[i].isAllin = false;
        tableInfo.playerInfo[i].isFold = false;
    }*/

    tableInfo.pot=0;
    tableInfo.ButtonPlayer = (tableInfo.ButtonPlayer + 1)% tableInfo.player_num;
    tableInfo.communityCards=std::vector<Card>();
    tableInfo.current_biggest_bet = 0;
    tableInfo.betting_round = -1;
    players_standing = tableInfo.player_num;

    tableInfo.current_player = tableInfo.ButtonPlayer;

    tableInfo.communityCards.clear();

    hand_finished = false;
    updatePlayersTable();


    //only start a new round if there are at least 3 players
    if (tableInfo.player_num >= 3){
        nextBettingRound();
    }
}

void GameLocal::askBet(PokerPlayer* p) {
    //connect to  a player, tell him its his turn then disconnect
    QObject::connect(this, &GameLocal::askAction, p, &PokerPlayer::Action, Qt::QueuedConnection);
    emit askAction();
    QObject::disconnect(this, &GameLocal::askAction, p, &PokerPlayer::Action);

}

void GameLocal::onAction() {

    //check if end hand
    if (players_standing == 1) {
        PlayerInfo winner;
        for (int i = 0; i < tableInfo.player_num; i++) {
            if (!tableInfo.playerInfo[i].isFold) {
                winner = tableInfo.playerInfo[i];
            }
        }
        endHand(winner);
    }
    else {
        //get next current_player
        setNextCurrentPlayer();


        // we end round of betting
        if (tableInfo.current_player == tableInfo.lastRaiser) {
            nextBettingRound();
        } else {
            updatePlayersTable();
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
        }
    }
}
void GameLocal::onCall() {

    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];

    //if doesn't have the money to bet: fold
    if (currentPlayerInfo.stack_size + currentPlayerInfo.bet < tableInfo.current_biggest_bet){
        fold(currentPlayerInfo);
    } else {
        //pay that money to the pot
        pay(currentPlayerInfo, tableInfo.current_biggest_bet - currentPlayerInfo.bet);
    }
    onAction();
}
void GameLocal::onFold() {
    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];

    fold(currentPlayerInfo);

    onAction();
}

void GameLocal::onRaise(int bet) {
    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];
    //if bets too little or doesn't have the money to bet: fold
    if (currentPlayerInfo.stack_size < tableInfo.current_biggest_bet + bet) {
        fold(currentPlayerInfo);
    } else {
        pay(currentPlayerInfo, bet);
        tableInfo.current_biggest_bet = currentPlayerInfo.bet;
        tableInfo.lastRaiser = tableInfo.current_player;

    }
    onAction();
}


void GameLocal::nextBettingRound() {
    tableInfo.betting_round += 1;
    for (int i = 0; i <= tableInfo.player_num; i++) {
        tableInfo.playerInfo[i].bet = 0;
    }
    tableInfo.current_biggest_bet = 0;
    tableInfo.current_player = tableInfo.ButtonPlayer;
    setNextCurrentPlayer();
    tableInfo.lastRaiser = tableInfo.current_player;



    switch (tableInfo.betting_round) {
        case 0:

            //preflop
            players_standing = tableInfo.player_num;

            tableInfo.current_biggest_bet = tableInfo.BBValue;
            //setting small and big blind
            pay(tableInfo.playerInfo[(tableInfo.ButtonPlayer + 1) % tableInfo.player_num], tableInfo.SBValue);

            pay(tableInfo.playerInfo[(tableInfo.ButtonPlayer + 2) % tableInfo.player_num], tableInfo.BBValue);



            deck.shuffleDeck();
            //give cards to players
            for (PokerPlayer* player : players) {
                std::vector<Card> cards;
                cards.push_back(deck.dealCard());
                cards.push_back(deck.dealCard());
                player->receiveCards(cards);
            }

            updatePlayersTable();
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;

        case 1:
            // second betting round
            tableInfo.communityCards.push_back(deck.dealCard());
            tableInfo.communityCards.push_back(deck.dealCard());
            tableInfo.communityCards.push_back(deck.dealCard());


            updatePlayersTable();
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;

        case 2:
            //third betting round
            tableInfo.communityCards.push_back(deck.dealCard());
            updatePlayersTable();
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;

        case 3:
            //last betting round
            tableInfo.communityCards.push_back(deck.dealCard());
            updatePlayersTable();
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;

        case 4:
            // show hands and declare winner

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
            std::vector<Card> winnerHandVect = findPlayer(winner.name)->getHand();

            winnerHandVect.insert(winnerHandVect.end(), community.begin(), community.end());

            PokerHand winnerHand(winnerHandVect);
            //iterate over players and compute their hand score
            //if their score is better than the current best, they become best
            //haven't taken into account ties yet, in that case, first player considered wins
            for (PlayerInfo current : playersNotFold) {
                std::vector<Card> currentHandVect = findPlayer(current.name)->getHand();;
                //getting hands throught the "getHand" function in the PokerPlayer class which is bad
                //need to store the hands of the players in the Game in order to retrieve and compare them

                currentHandVect.insert(currentHandVect.end(), community.begin(), community.end());
                PokerHand currentHand(currentHandVect);
                if (compare_hands(winnerHand, currentHand) == 2) {
                    winner = current;
                    winnerHand = currentHand;
                }
            }
            endHand(winner);
            break;
    }
}

PokerPlayer* GameLocal::findPlayer(std::string name) {
    for (PokerPlayer* player : players) {
        if (player->name == name) {
            return player;
        }
    }
};

void GameLocal::setNextCurrentPlayer() {
    //get next current_player
    for (int elt = 1; elt <= tableInfo.player_num; elt++) {
        tableInfo.current_player = (tableInfo.current_player + 1) % tableInfo.player_num;
        if ( !tableInfo.playerInfo[tableInfo.current_player].isFold ) {
            break;
        }
    }
}




