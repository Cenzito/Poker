#include "GameLocal.hpp"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QString>


QFile file("C:/Users/Leal Köksal/Documents/a University/Semester 3/CSE201/C++ Project/Poker/Poker/logistic_regression");

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
        qDebug() << "too many players";
        return;
    } else {

        //player joins game so we add him to the table with an initial amount of money
        PlayerInfo playerinfo(player->getName(), 1000, 0);
        tableInfo.playerInfo[tableInfo.player_num] = playerinfo;

        players.push_back(player);


        setPlayerInfos(player);

        //connect slots to signals
        QObject::connect(player, &PokerPlayer::Call, this, &GameLocal::onCall);
        QObject::connect(player, &PokerPlayer::Fold, this, &GameLocal::onFold);
        QObject::connect(player, &PokerPlayer::Raise, this,&GameLocal::onRaise);
        QObject::connect(this, &GameLocal::updatePTable, player, &PokerPlayer::updateTable);

        //player joins game so we add him to the table with an initial amount of money
        updatePlayersTable("/joinGame " + player->name + " " + std::to_string(1000));

    }

}

void GameLocal::addBot(Bot* bot) {
    GameLocal::JoinGame(bot);
}


void GameLocal::pay(PlayerInfo& PlayerPay, int sum) {
    //adding to the subpots for allinners if they allinned this round
    for (int i = 0; i < tableInfo.player_num; i++) {
        if (tableInfo.playerInfo[i].isAllin) { //players who are all in are not folded (you cant have both)
            if (0<tableInfo.playerInfo[i].bet){ //checking if the all in was this round to check if subpot can still increase
                if (PlayerPay.bet < tableInfo.playerInfo[i].bet) { //checks if has already been counted previously in allin
                    tableInfo.subpots[i]+= (tableInfo.playerInfo[i].bet-PlayerPay.bet ); //adds what hadn't been added
                }
            }
        }
    }
    if (PlayerPay.isAllin){
        if (sum>0){
            int index2=tableInfo.playerIndex(PlayerPay.name);
            tableInfo.subpots[index2]+=sum;
        }
    }

    updatePlayersTable("/bet " + PlayerPay.name + " " + std::to_string(sum));
};

void GameLocal::win(PlayerInfo& PlayerWin, int sum) {
    //qDebug() << sum;
    updatePlayersTable("/win " + PlayerWin.name + " " + std::to_string(sum));
    //FILE1 win amount

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Failed to open the file for writing:" << file.errorString();
        return;
    }
    QTextStream stream(&file);
    if (PlayerWin.name == "bot4") {
        stream << sum << "\n";
    }

    else {
        stream << 0 << "\n";
    }

    if (stream.status() != QTextStream::Ok) {
        qDebug() << "Error writing to the file:" << file.errorString();
    }

    file.close();
};


void GameLocal::distribute() {

    std::vector<PlayerInfo> winnerlist = winners();

    if (winnerlist.size() ==1){
        PlayerInfo PlayerWin = winnerlist.at(0);
        if (PlayerWin.isAllin) {
            //finds the index of the winning player in playerInfo
            int index=tableInfo.playerIndex(PlayerWin.name);
            qDebug()<<"SINGLE ALLIN WINNER";
            if (tableInfo.subpots[index]>0) {

                //transfers the money from the subpot to the players stack
                win(PlayerWin,tableInfo.subpots[index]);

                //decreases the value in the pot and subpots
                tableInfo.pot -= tableInfo.subpots[index];
                for (int i =0; i<tableInfo.player_num; i++){
                    tableInfo.subpots[i] -= tableInfo.subpots[index];
                }
            }


            //get rid of any all inners who might have been equal to the minimum (at least one)
            for (PlayerInfo candidate : winnerlist) {
                if (candidate.isAllin) {
                    int index=tableInfo.playerIndex(candidate.name);
                    if (tableInfo.subpots[index]<=0) {
                        fold(candidate);
                    }

                }
            }

            qDebug()<<"There are this many players"<<players_standing;
            if (tableInfo.pot>0){ //if theres still money to give...
                if (players_standing<=1) { //if theres at most one active player, let that active player win the rest
                    for (int i =0; i<=tableInfo.player_num; i++){
                        if (tableInfo.playerInfo[i].isFold==false) {
                            win(tableInfo.playerInfo[i],tableInfo.pot);
                        }
                    }
                } else { //else distribute the rest with the other players

                    //we continue distributing until there is no more pot
                    distribute();

                }
            }
        } else { //if the only player is not allin then he gets all the money and the round is over
            qDebug()<<"One player got the money:" << PlayerWin.name;
            qDebug()<< "They won" << tableInfo.pot;


            win(PlayerWin, tableInfo.pot);

        }
    } else {
        //check if there's a player who went all in
        int allin_counter=0;
        for (PlayerInfo candidate : winnerlist) {
            if (candidate.isAllin) {
                allin_counter+=1;
            }
        }

        //if no players went all in, share the pot equally
        if (allin_counter==0) {
            int splitpot = (tableInfo.pot/winnerlist.size());
            int extra =(tableInfo.pot%winnerlist.size());
            win(winnerlist.at(0),extra);
            for (PlayerInfo candidate : winnerlist) {
                win(candidate,splitpot);
            }

        } else { // if at least one player went all in, we split the smallest subpot with all the winners and check with the rest

            //find the smallest subpot
            int minindex =-1;
            for (PlayerInfo candidate : winnerlist) {
                if (candidate.isAllin) {
                    int index=tableInfo.playerIndex(candidate.name);
                    if (minindex==-1) {
                        minindex= index;
                    } else {
                        if (tableInfo.subpots[minindex]>tableInfo.subpots[index]){
                            minindex=index;
                        }
                    }

                }
            }

            //split the subpot
            int splitpot = (tableInfo.subpots[minindex]/winnerlist.size());
            int extra =(tableInfo.subpots[minindex]%winnerlist.size());
            win(winnerlist.at(0),extra);
            for (PlayerInfo candidate : winnerlist) {
                win(candidate,splitpot);
            }

            //reduce the available money
            tableInfo.pot -= tableInfo.subpots[minindex];
            for (int i =0; i<=tableInfo.player_num; i++){
                tableInfo.subpots[i] -= tableInfo.subpots[minindex];
            }

            //get rid of any all inners who might have been equal to the minimum (at least one)
            for (PlayerInfo candidate : winnerlist) {
                if (candidate.isAllin) {
                    int index=tableInfo.playerIndex(candidate.name);
                    if (tableInfo.subpots[index]<=0) {
                        fold(candidate);
                    }

                }
            }
            //keep distributing the money if there's any left
            if (tableInfo.pot>0){
                if (players_standing>=1) {
                    distribute();
                }

            }
        }
    }
}


//distributes the money to the winner and start anew
void GameLocal::endHand() {

    //show player hands
    for (int i = 0; i< tableInfo.player_num;i++ ) {
        PlayerInfo* current = &tableInfo.playerInfo[i];
        if (current->cards.size() == 2) {
            updatePlayersTable("/setCard " + current->name + " " + suitToString(current->cards[0].getSuit()) + " " + std::to_string(current->cards[0].getValue()) + " " + suitToString(current->cards[1].getSuit()) + " " + std::to_string(current->cards[1].getValue()));
        }
    }
    distribute();


    nextHand();
}

std::vector<PlayerInfo> GameLocal::winners() {
    //get all the people who haven't folded
    std::vector<PlayerInfo> playersNotFold;
    for (int i = 0; i < tableInfo.player_num; i++) {
        if (!tableInfo.playerInfo[i].isFold) {
            playersNotFold.push_back(tableInfo.playerInfo[i]);
        }
    }

    //create the winners vector
    std::vector<PlayerInfo> winners;

    //bring the community cards in to build the hands
    std::vector<Card> community = tableInfo.communityCards;

    for (PlayerInfo first : playersNotFold) {

        //get the first hand
        std::vector<Card> firstvect = findPlayer(first.name)->getHand();
        firstvect.insert(firstvect.end(), community.begin(), community.end());
        PokerHand firstHand(firstvect);

        //creates a counter just to make it easier to know when we're at the end of the vector
        int counter=0;

        for (PlayerInfo second : playersNotFold) {

            //get the second hand
            std::vector<Card> secondvect = findPlayer(second.name)->getHand();
            secondvect.insert(secondvect.end(), community.begin(), community.end());
            PokerHand secondHand(secondvect);

            //if they lose to any hand, they can't win so we skip them
            if (compare_hands(firstHand, secondHand) == 2) {
                break;
            } else {
                //increments the counter since they didn't lose
                counter+=1;
            }

            //if we're at the end of the vector and they still haven't lost then they're a winner
            if (counter == players_standing) {
                winners.push_back(first);
            }
        }
    }
    qDebug()<<winners.size();
    return winners;
}


void GameLocal::fold(PlayerInfo& foldPlayer) {
    foldPlayer.isFold = true;
    players_standing -= 1;
}


void GameLocal::updatePlayersTable(std::string updatePlayersTable) {
    emit updatePTable(updatePlayersTable);
    tableInfo.updateTable(updatePlayersTable);
    //tableInfo.Print();

}


void GameLocal::allin(PlayerInfo& allinPlayerInfo) {
    //set the player to all in
    allinPlayerInfo.isAllin=true;
    //qDebug()<<allinPlayerInfo.name<<"went all in";

    //get players who havent folded since they are the ones who might of bet more than our stack
    //(keep in mind that if a player has folded then he certainly put in less than our stack or else this would
    //have already been triggered earlier, and they couldn't have both called/raised and folded in that one move)
    //creates the subpot for the allinPlayer
    int subpot= tableInfo.pot;
    for (int i = 0; i < tableInfo.player_num; i++) {
        if (!tableInfo.playerInfo[i].isFold) {
            if (tableInfo.playerInfo[i].bet>allinPlayerInfo.stack_size+allinPlayerInfo.bet){
                subpot -= (tableInfo.playerInfo[i].bet-allinPlayerInfo.stack_size-allinPlayerInfo.bet); //removes the surplus that players might have put in
            }
        }
    }

    //find the index of the allinPlayer so we can create a subpot for it
    int index=tableInfo.playerIndex(allinPlayerInfo.name);

    //adds the subpot into the subpot vector
    tableInfo.subpots[index]=subpot;


    //pay all the money the player has to the pot
    pay(  allinPlayerInfo, allinPlayerInfo.stack_size  );
}



void GameLocal::setPlayerInfos(PokerPlayer* player) {
    //used to set the players in the Table when you join the game
    // can also be used to resync the players with what the game has.
    std::string listPInf = "/setPInf";

    for (int i = 0; i< tableInfo.player_num;i++) {
        //add info to command
        //if we also want to pass the bets we can add them
        listPInf += " " + tableInfo.playerInfo[i].name;
        listPInf += " " + std::to_string(tableInfo.playerInfo[i].stack_size);
    }

    //qDebug() << QString::fromStdString(listPInf);

    //emit the change to the player
    QObject::connect(this, &GameLocal::setPInf, player, &PokerPlayer::updatePInf);
    emit setPInf(listPInf);
    QObject::disconnect(this, &GameLocal::setPInf, player, &PokerPlayer::updatePInf);

}


void GameLocal::nextHand(){
    //resets the hands
    for (PokerPlayer* player : players) {
        player->removeCards();
    }

    //reset bets
    for (int i = 0; i <= tableInfo.player_num; i++) {
        tableInfo.playerInfo[i].bet = 0;
        tableInfo.playerInfo[i].isAllin = false;
        tableInfo.playerInfo[i].isFold = false;
    }


    players_standing = tableInfo.player_num;
    //qDebug() << tableInfo.communityCards.size();

    hand_finished = false;

    updatePlayersTable("/resetGame");


    //only start a new round if there are at least 3 players
    if (tableInfo.player_num >= 3){
        nextBettingRound();
    }
}

void GameLocal::askBet(PokerPlayer* p) {
    //connect to  a player, tell him its his turn then disconnect
    //qDebug()<<p->name<<"is asked to make a choice";
    QObject::connect(this, &GameLocal::askAction, p, &PokerPlayer::Action, Qt::QueuedConnection);
    emit askAction();
    QObject::disconnect(this, &GameLocal::askAction, p, &PokerPlayer::Action);
}

void GameLocal::onAction() {
    QTextStream stream(&file);
    if (tableInfo.playerInfo[tableInfo.current_player].name == "bot4") {
        std::vector<Card> bot_hand = tableInfo.playerInfo[tableInfo.current_player].cards;
        for (int i = 0; i < tableInfo.communityCards.size(); i++) {
            bot_hand.emplace_back(tableInfo.communityCards[i]);
        }

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            qDebug() << "Failed to open the file for writing:" << file.errorString();
            return;
        }

        if (tableInfo.playerInfo[tableInfo.current_player].name == "bot4") {
            if (tableInfo.betting_round == 3 || tableInfo.playerInfo[tableInfo.current_player].isFold == true ) {
                stream << tableInfo.betting_round << "\t" << Winning_Probability(tableInfo, bot_hand, tableInfo.player_num, 100)[0] << "\t";

            }
            else {
                stream << tableInfo.betting_round << "\t" << Winning_Probability(tableInfo, bot_hand, tableInfo.player_num, 100)[0] << QString::fromStdString(" ") << "\n";
            }
        }

        if (stream.status() != QTextStream::Ok) {
            qDebug() << "Error writing to the file:" << file.errorString();
        }

        file.close();
    }


    if (players_standing == 1) {
        endHand();
    }
    else {
        //get next current_player
        //qDebug()<<"is this the problem?";
        setNextCurrentPlayer();
        // we end round of betting
        if (tableInfo.current_player == tableInfo.lastRaiser) {
            //qDebug()<<"is this the problem?";
            nextBettingRound();
        } else {
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
        }

    }
}

void GameLocal::onCall() {
    QTextStream stream(&file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Failed to open the file for writing:" << file.errorString();
        return;
    }

    if (tableInfo.playerInfo[tableInfo.current_player].name == "bot4") {
        stream << 0 << "\t";
    }

    if (stream.status() != QTextStream::Ok) {
        qDebug() << "Error writing to the file:" << file.errorString();
    }

    file.close();


    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];
    qDebug()<<"current highest bet is:"<< tableInfo.current_biggest_bet << "by" << tableInfo.current_player;
    //if doesn't have the money to match: all-in
    if (currentPlayerInfo.stack_size + currentPlayerInfo.bet <= tableInfo.current_biggest_bet){
        allin(currentPlayerInfo);
    } else {
        //pay that money to the pot
        pay(currentPlayerInfo, tableInfo.current_biggest_bet - currentPlayerInfo.bet); //accounts for previous bet
    }
    onAction();
}


void GameLocal::onFold() {
    QTextStream stream(&file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Failed to open the file for writing:" << file.errorString();
        return;
    }

    if (tableInfo.playerInfo[tableInfo.current_player].name == "bot4") {
        stream << 1 << "\t";
    }


    if (stream.status() != QTextStream::Ok) {
        qDebug() << "Error writing to the file:" << file.errorString();
    }

    file.close();


    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];

    fold(currentPlayerInfo);

    onAction();
}


void GameLocal::onRaise(int bet) {
    QTextStream stream(&file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Failed to open the file for writing:" << file.errorString();
        return;
    }
    if (tableInfo.playerInfo[tableInfo.current_player].name == "bot4") {
        stream << 0 << "\t";

    }

    if (stream.status() != QTextStream::Ok) {
        qDebug() << "Error writing to the file:" << file.errorString();
    }

    file.close();


    qDebug()<<"IN RAISE";
    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];
    //qDebug()<<currentPlayerInfo.name<<"is trying to raise"<<bet;

    //if bets too little or doesn't have the money to bet: all in
    if (currentPlayerInfo.stack_size <= tableInfo.current_biggest_bet + bet - currentPlayerInfo.bet) { //checks for lack of funds to raise by "bet" amount
        if (currentPlayerInfo.stack_size + currentPlayerInfo.bet > tableInfo.current_biggest_bet) {
            updatePlayersTable("/setBiggestBet " + std::to_string(currentPlayerInfo.stack_size + currentPlayerInfo.bet));
            updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));
        }

        allin(currentPlayerInfo);
    } else { //if they have the funds
        qDebug()<<"bet went from:"<<currentPlayerInfo.bet;
        pay(currentPlayerInfo, tableInfo.current_biggest_bet +bet - currentPlayerInfo.bet);
        qDebug()<<"to:"<<currentPlayerInfo.bet << "player that bet" << tableInfo.playerInfo[tableInfo.current_player].player_name();

        //paste betting amount here
        updatePlayersTable("/setBiggestBet " + std::to_string(currentPlayerInfo.bet));
        qDebug()<<"setting biggest bet to:"<<currentPlayerInfo.bet;
        updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

    }
    onAction();
}


void GameLocal::nextBettingRound() {
    updatePlayersTable("/nextRound");
    //qDebug() << tableInfo.betting_round;

    switch (tableInfo.betting_round) {
    case 0: {

            //preflop
            players_standing = tableInfo.player_num;

            updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));

            updatePlayersTable("/setBiggestBet " + std::to_string(tableInfo.BBValue));
            //setting small and big blind
            setNextCurrentPlayer();
            pay(tableInfo.playerInfo[tableInfo.current_player], tableInfo.SBValue);

            setNextCurrentPlayer();
            pay(tableInfo.playerInfo[tableInfo.current_player], tableInfo.BBValue);


            deck.shuffleDeck();
            //give cards to players
            for (PokerPlayer* player : players) {
                std::vector<Card> cards;
                cards.push_back(deck.dealCard());
                cards.push_back(deck.dealCard());
                player->receiveCards(cards);
                tableInfo.getPlayerInfo(player->name)->cards = cards;
                //FILE1: calculate card combo here and add %win to table
            }
            //three players after button is first to act
            setNextCurrentPlayer();

            //biggest bet is always first to act
            //if all fold and come back to him -> go to next round
            updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;
    }
    case 1: {
            // second betting round
            Card card1 = deck.dealCard();
            Card card2 = deck.dealCard();
            Card card3 = deck.dealCard();

            updatePlayersTable("/addCardMid " + suitToString(card1.getSuit()) + " " + std::to_string(card1.getValue()));
            updatePlayersTable("/addCardMid " + suitToString(card2.getSuit()) + " " + std::to_string(card2.getValue()));
            updatePlayersTable("/addCardMid " + suitToString(card3.getSuit()) + " " + std::to_string(card3.getValue()));


            //player after button is first to act
            updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));
            setNextCurrentPlayer();
            updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;
    }
    case 2: {
            //third betting round
            Card card1 = deck.dealCard();
            updatePlayersTable("/addCardMid " + suitToString(card1.getSuit()) + " " + std::to_string(card1.getValue()));

            updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));
            setNextCurrentPlayer();
            updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;
    }
    case 3: {
            //last betting round
            Card card1 = deck.dealCard();
            updatePlayersTable("/addCardMid " + suitToString(card1.getSuit()) + " " + std::to_string(card1.getValue()));

            updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));
            setNextCurrentPlayer();
            updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            break;
    }
    case 4:{
            endHand();
            break;
    }
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
        int next = (tableInfo.current_player + elt) % tableInfo.player_num;
        if ( !tableInfo.playerInfo[next].isFold ) {
            updatePlayersTable("/setActivePlayer " + std::to_string(next));
            break;
        }
    }
}




