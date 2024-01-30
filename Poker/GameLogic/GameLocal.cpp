#include "GameLocal.hpp"
#include <QApplication>
#include <random>


/*
    GameLocal(int seats): initializes a game with that many seats
*/

GameLocal::GameLocal(int seats): tableInfo(seats){
}

/*
    getFreeSeat(): checks if there's a free seat at the table, if there is,
    returns i, the index of the seat. otherwise it returns -1
*/

int GameLocal::getFreeSeat() {
    Table &t = tableInfo;
    for (int i = 0; i<t.seats; i++) {
        if (t.playerInfo.find(i) == t.playerInfo.end()) {
            return i;
        }
    }
    return -1;
}


/*
    JoinGame(PokerPlayer* player): adds the player to the game if there's space and connects
    him to all the signals, with an inital amount of money and initializes his playerInfo
*/
void GameLocal::JoinGame(PokerPlayer* player) {

    //error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        //qDebug() << "too many players";
        return;
    } else {

        //player joins game so we add him to the table with an initial amount of money

        players.push_back(player);


        setPlayerInfos(player);

        //connect slots to signals
        QObject::connect(player, &PokerPlayer::Call, this, &GameLocal::onCall);
        QObject::connect(player, &PokerPlayer::Fold, this, &GameLocal::onFold);
        QObject::connect(player, &PokerPlayer::Raise, this,&GameLocal::onRaise);
        QObject::connect(this, &GameLocal::updatePTable, player, &PokerPlayer::updateTable);

        if (!player->isBot) {
            QObject::connect(player, &PokerPlayer::nextGame, this, &GameLocal::nextHand);
        }

        //player joins game so we add him to the table with an initial amount of money
        updatePlayersTable("/joinGame " + player->name + " " + std::to_string(1000));
        tableInfo.playerInfo[tableInfo.player_num-1].isFold = true;

    }

}


/*
    addBot(int botNumber): calls JoinGame(bot). its use is to simplify the calls.
*/

void GameLocal::addBot(int botNumber) {
    std::string name;
    if (botNumber==1) {
        name = nameBot(1);
    } else if (botNumber==2){
        name = nameBot(2);
    } else {
        name=nameBot();
    }

    switch (botNumber) {
    case 0: {
        // Drunk bot, he always calls
        // Don't bluff against him cause he'll know it
        BotDrunk* bot = new BotDrunk(name);
        JoinGame(bot);
        break;
    }
    case 1: {
        // A random bot
        // It's a monkey, did you really expect him to know how to play?
        MonkeyBot* bot = new MonkeyBot(name);
        JoinGame(bot);
        break;
    }
    case 2: {
        // Darius's bot
        //Insert comment
        BotDarius* bot = new BotDarius(name);
        JoinGame(bot);
        break;
    }
    case 3: {
        // Pu's bot
        BotPu* bot = new BotPu(name);
        JoinGame(bot);
        break;
    }
    }


}


void GameLocal::RemovePlayer(std::string name) {
    if (tableInfo.hand_finished) {
        //remove player from the player vector
        for (int elt=0;elt<players.size(); elt ++) {
            if (players[elt]->name == name) {
                players.erase(players.begin() + elt);
                break;
            }
        }

        //remove from table
        updatePlayersTable("/remove " + name);
    }
};


/*
    pay(PlayerInfo& PlayerPay, int sum): makes PlayerPay pay sum to the stack, and modifies the subpots of allinners if needed.
*/
void GameLocal::pay(PlayerInfo& PlayerPay, int sum) {
    //adding to the subpots for allinners if they allinned this round
    for (int i = 0; i < tableInfo.player_num; i++) {
        if (tableInfo.playerInfo[i].isAllin) { //players who are all in are not folded (you cant have both)
            if (0<tableInfo.playerInfo[i].bet){ //checking if the all in was this round to check if subpot can still increase
                if (PlayerPay.bet < tableInfo.playerInfo[i].bet) { //checks if has already been counted previously in allin
                    tableInfo.subpots[i]+= std::min(tableInfo.playerInfo[i].bet-PlayerPay.bet,sum ); //adds what hadn't been added
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

/*
    win(PlayerInfo& PlayerWin, int sum): gives sum back to PlayerWin.
*/
void GameLocal::win(PlayerInfo& PlayerWin, int sum) {
    //qDebug() << sum;
    updatePlayersTable("/win " + PlayerWin.name + " " + std::to_string(sum));
};

/*
    distribute(): distributes all the money in the pot to the players, takes into account ties and allins by splitting the pot or
    distributing the subpots first. Uses a little bit of recursion to make sure all the money is redistributed.
*/
void GameLocal::distribute() {
    //qDebug()<<"distributing";

    std::vector<PlayerInfo> winnerlist = winners();
    /*
    qDebug()<<"winners are";
    for (int i=0; i<winnerlist.size(); i++) {
        qDebug()<<winnerlist.at(i).name;
    }
    qDebug()<<"end of winners";
    */
    if (winnerlist.size() ==1){
        //qDebug()<<"CASE 1 ERROR";
        PlayerInfo PlayerWin = winnerlist.at(0);
        if (PlayerWin.isAllin) {
            //finds the index of the winning player in playerInfo
            int index=tableInfo.playerIndex(PlayerWin.name);
            //qDebug()<<"CASE A ERROR";
            //just to be safe we check that they can still receive money (i.e if their subpot is bigger than 0)
            if (tableInfo.subpots[index]>0) {
                //transfers the money from the subpot to the players stack
                win(PlayerWin,tableInfo.subpots[index]);


                //decreases the money available in the pot and subpots
                //qDebug()<< "pot went from"<<tableInfo.pot;

                tableInfo.pot -= tableInfo.subpots[index];
                for (int i =0; i<tableInfo.player_num; i++){
                    tableInfo.subpots[i] -= tableInfo.subpots[index];
                }
                //qDebug()<< "to"<<tableInfo.pot;
            }


            //get rid of any all inners who might have been equal to the minimum (at least one)
            for (PokerPlayer* player : players) {
                PlayerInfo candidate= tableInfo.playerInfo[tableInfo.playerIndex(player->name)];
                if (candidate.isAllin) {
                    int index=tableInfo.playerIndex(candidate.name);
                    if (tableInfo.subpots[index]<=0) {
                        //qDebug()<<"folding"<<candidate.name;
                        fold(candidate);
                        //qDebug()<<"it worked?:"<<candidate.isFold;
                    }

                }
            }


            //if theres still money to give...
            if (tableInfo.pot>0){
                //if theres at most one active player, let that active player win the rest (serves as a base case for the recursion)
                if (players_standing<=1) {
                    for (int i =0; i<=tableInfo.player_num; i++){ //there might need an = here
                        if (tableInfo.playerInfo[i].isFold==false) {
                            win(tableInfo.playerInfo[i],tableInfo.pot);
                            break;
                        }
                    }
                } else { //else distribute the rest with the other players

                    //we continue distributing until there is no more pot
                    distribute();

                }
            }
        } else { //if the only player is not allin then he gets all the money and the round is over
            //qDebug()<<"CASE B ERROR";
            win(PlayerWin, tableInfo.pot);
        }
    } else {
        //qDebug()<<"CASE 2 ERROR";
        //check if there's a player who went all in
        int allin_counter=0;
        for (PlayerInfo candidate : winnerlist) {
            if (candidate.isAllin) {
                allin_counter+=1;
            }
        }

        //if no players went all in, share the pot equally
        if (allin_counter==0) {
            //qDebug()<<"CASE A ERROR";
            int splitpot = (tableInfo.pot/winnerlist.size());
            int extra =(tableInfo.pot%winnerlist.size());
            if (extra>0){
                win(winnerlist.at(0),extra);
            }
            for (PlayerInfo candidate : winnerlist) {
                win(candidate,splitpot);
            }


        } else { // if at least one player went all in, we split the smallest subpot with all the winners and redistribute what remains

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
            //qDebug()<<"number of ways to split is"<<winnerlist.size();
            //qDebug()<<"minsubpot is"<<tableInfo.playerInfo[minindex].name<<"'s"<< "and has "<<tableInfo.subpots[minindex];
            //qDebug()<<"split sum is"<<splitpot<<"+"<<extra;
            if (extra>0){
                win(winnerlist.at(0),extra);
            }
            for (PlayerInfo candidate : winnerlist) {
                win(candidate,splitpot);
            }

            //reduce the available money
            int minpot=tableInfo.subpots[minindex];
            //qDebug()<< "pot went from"<<tableInfo.pot;
            tableInfo.pot -= minpot;
            //qDebug()<< "to"<<tableInfo.pot;
            for (int i =0; i<tableInfo.player_num; i++){
                tableInfo.subpots[i] -= minpot;
            }

            //get rid of any all inners who might have been equal to the minimum (at least one)
            for (PokerPlayer* player : players) {
                PlayerInfo& candidate= tableInfo.playerInfo[tableInfo.playerIndex(player->name)];
                if (candidate.isAllin) {
                    int index=tableInfo.playerIndex(candidate.name);
                    if (tableInfo.subpots[index]<=0) {
                        //qDebug()<<"folding"<<candidate.name;
                        fold(candidate);
                        //qDebug()<<"it worked?:"<<candidate.isFold;
                    }

                }
            }

            //qDebug()<<"There are this many players"<<players_standing;
            if (tableInfo.pot>0){ //if theres still money to give...
                if (players_standing<=1) { //if theres at most one active player, let that active player win the rest
                    //qDebug()<<"less than 1 player bug?";
                    for (int i =0; i<=tableInfo.player_num; i++){
                        if (tableInfo.playerInfo[i].isFold==false) {
                            win(tableInfo.playerInfo[i],tableInfo.pot);
                            break;
                        }
                    }
                } else { //else distribute the rest with the other players

                    //we continue distributing until there is no more pot
                    distribute();

                }
            }
        }
    }
}


/*
    endHand(): ends the hand by showing the cards and distributing the money
*/
void GameLocal::endHand() {
    //qDebug() << "hend end";
    //show player hands
    for (int i = 0; i< tableInfo.player_num;i++ ) {
        PlayerInfo* current = &tableInfo.playerInfo[i];
        if (!current->isFold) {
            updatePlayersTable("/setCard " + current->name + " " + suitToString(current->cards[0].getSuit()) + " " + std::to_string(current->cards[0].getValue()) + " " + suitToString(current->cards[1].getSuit()) + " " + std::to_string(current->cards[1].getValue()));
        }
    }


    //distributes the money to the winners
    distribute();

    updatePlayersTable("/finishHand 1");

}

/*
    winners() : returns the vector of winners (can be multiple in case of ties).
*/
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

    //qDebug()<<winners.size();
    return winners;
}

/*
    fold(PlayerInfo& foldPlayer): folds the player and decreases the number of active players.
*/
void GameLocal::fold(PlayerInfo& foldPlayer) {
    foldPlayer.isFold = true;
    players_standing -= 1;
}

/*
    updatePlayersTable(std::string updatePlayersTable): updates the table for the player.
*/
void GameLocal::updatePlayersTable(std::string updatePlayersTable) {
    emit updatePTable(updatePlayersTable);
    tableInfo.updateTable(updatePlayersTable);
    tableInfo.Print();

}

/*
    allin(PlayerInfo& allinPlayerInfo): sets the player to allin, creates their subpot, and pays their whole stack to the pot.
*/
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
                subpot-= (tableInfo.playerInfo[i].bet-allinPlayerInfo.stack_size-allinPlayerInfo.bet); //removes the surplus that players might have put in
            }
        }
    }

    //find the index of the allinPlayer so we can create a subpot for it
    int index=tableInfo.playerIndex(allinPlayerInfo.name);

    //adds the subpot into the subpot vector
    tableInfo.subpots[index]=subpot;
    players_all_in += 1;


    //pay all the money the player has to the pot
    pay(  allinPlayerInfo, allinPlayerInfo.stack_size  );
}


/*
    setPlayerInfos(PokerPlayer* player): .
*/
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

/*
    nextHand(): .
*/
void GameLocal::nextHand(){
    //resets the hands
    for (PokerPlayer* player : players) {
        player->removeCards();
    }

    //reset bets
    for (int i = tableInfo.player_num - 1; i >= 0; i--) {
        tableInfo.playerInfo[i].bet = 0;
        tableInfo.playerInfo[i].isAllin = false;
        tableInfo.playerInfo[i].isFold = false;
        tableInfo.subpots[i]=0;
        if (tableInfo.playerInfo[i].stack_size == 0) {
            RemovePlayer(tableInfo.playerInfo[i].name);
        }
    }
    if (tableInfo.player_num < 3) {
        return;
    }

    players_standing = tableInfo.player_num;
    players_all_in = 0;

    updatePlayersTable("/finishHand 0");

    updatePlayersTable("/resetGame");


    //only start a new round if there are at least 3 players
    if (tableInfo.player_num >= 3){
        nextBettingRound();
    }
}

/*
    askBet(PokerPlayer* p): connects the player functions to the functions in GameLocal.
*/
void GameLocal::askBet(PokerPlayer* p) {
    //connect to  a player, tell him its his turn then disconnect
    //qDebug()<<p->name<<"is asked to make a choice";
    QObject::connect(this, &GameLocal::askAction, p, &PokerPlayer::Action, Qt::QueuedConnection);
    emit askAction();
    QObject::disconnect(this, &GameLocal::askAction, p, &PokerPlayer::Action);
}


/*
    onAction(): sets current player to the next player and goes to the next betting round if the lastRaiser is reach or in
    specific situations.
*/
void GameLocal::onAction() {
    //qDebug()<<"action entered";
    //check if end hand
    if (players_standing == 1) {
        nextBettingRound();
    } else if (players_standing - players_all_in == 0) {
        nextBettingRound();
    }
    else {
        //get next current_player

        setNextCurrentPlayer();

        //if the last raiser just folded
        //this happens if the first person to acts folds
        if (tableInfo.playerInfo[tableInfo.lastRaiser].isFold || tableInfo.playerInfo[tableInfo.lastRaiser].isAllin) {
            updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
        }
        // if we got back to the biggest better
        else if (tableInfo.current_player == tableInfo.lastRaiser) {
            //qDebug()<<"is this the problem?";
            nextBettingRound();
        } else {
            askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
        }

    }
}

/*
    onCall(): calls if they have the money and allins if they dont, then calls onAction() to decide what to do next.
*/
void GameLocal::onCall() {
    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];
    //qDebug()<<"current highest bet is:"<< tableInfo.current_biggest_bet;
    //if doesn't have the money to match: all-in
    if (currentPlayerInfo.stack_size + currentPlayerInfo.bet <= tableInfo.current_biggest_bet){
        allin(currentPlayerInfo);
    } else {
        //pay that money to the pot
        pay(currentPlayerInfo, tableInfo.current_biggest_bet - currentPlayerInfo.bet); //accounts for previous bet
    }
    onAction();
}

/*
    onFold(): folds the player, then calls onAction() to decide what to do next.
*/
void GameLocal::onFold() {
    PlayerInfo &currentPlayerInfo = tableInfo.playerInfo[tableInfo.current_player];

    fold(currentPlayerInfo);

    onAction();
}

/*
    onRaise(): lets the player raise if they have the money and allins if they don't
    updates the current_biggest_bet if necessary, then calls onAction() to decide what to do next.
*/
void GameLocal::onRaise(int bet) {
    //qDebug()<<"IN RAISE";
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
        //qDebug()<<"bet went from:"<<currentPlayerInfo.bet;
        pay(currentPlayerInfo, tableInfo.current_biggest_bet +bet - currentPlayerInfo.bet);
        //qDebug()<<"to:"<<currentPlayerInfo.bet;
        updatePlayersTable("/setBiggestBet " + std::to_string(currentPlayerInfo.bet));
        //qDebug()<<"setting biggest bet to:"<<currentPlayerInfo.bet;
        updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

    }
    onAction();
}

/*
    nextBettingRound():
*/
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
                //qDebug() << QString::fromStdString(player->name);
                player->receiveCards(cards);
                tableInfo.getPlayerInfo(player->name)->cards = cards;
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


            // if there is only one player left or everyone is all in we directly go to the next round
            if (players_standing - players_all_in == 0 || players_standing == 1) {
                nextBettingRound();
            }else if (players_standing >1) {
                updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));
                setNextCurrentPlayer();
                updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));
                askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            }
            break;
    }
    case 2: {
            //third betting round
            Card card1 = deck.dealCard();
            updatePlayersTable("/addCardMid " + suitToString(card1.getSuit()) + " " + std::to_string(card1.getValue()));

            if (players_standing - players_all_in == 0 || players_standing == 1) {
                nextBettingRound();
            }else if (players_standing >1) {
                updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));
                setNextCurrentPlayer();
                updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

                askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            }
            break;
    }
    case 3: {
            //last betting round
            Card card1 = deck.dealCard();
            updatePlayersTable("/addCardMid " + suitToString(card1.getSuit()) + " " + std::to_string(card1.getValue()));


            if (players_standing - players_all_in == 0 || players_standing == 1) {
                nextBettingRound();
            }else if (players_standing >1) {
                updatePlayersTable("/setActivePlayer " + std::to_string(tableInfo.ButtonPlayer));
                setNextCurrentPlayer();
                updatePlayersTable("/setLastRaiser " + std::to_string(tableInfo.current_player));

                askBet(findPlayer(tableInfo.playerInfo[tableInfo.current_player].name));
            }
            break;
    }
    case 4:{
            endHand();
            break;
    }
    }
}

/*
    findPlayer(std::string name): finds the pointer towards the player with the name "name".
*/
PokerPlayer* GameLocal::findPlayer(std::string name) {
    for (PokerPlayer* player : players) {
        if (player->name == name) {
            return player;
        }
    }
};

/*
    setNextCurrentPlayer(): sets currentplayer to the next player who can make a decision (i.e if they're not allin or folded).
*/
void GameLocal::setNextCurrentPlayer() {
    //get next current_player
    for (int elt = 1; elt < tableInfo.player_num; elt++) {
        int next = (tableInfo.current_player + elt) % tableInfo.player_num;
        if ( !tableInfo.playerInfo[next].isFold  && !tableInfo.playerInfo[next].isAllin) {
            updatePlayersTable("/setActivePlayer " + std::to_string(next));
            break;
        }
    }
}

std::string GameLocal::nameBot(int number) {
    //get the vector of existing names
    std::vector<std::string> names;
    for (int i = 0; i < tableInfo.player_num; i++) {
        names.push_back(tableInfo.playerInfo[i].name);
    }

    //bot names
    std::vector<std::string> botNames = {
        "Chimpanzee", "Gorilla", "Baboon", "Capuchin", "Marmocet", "Mandrill", "Orangutan", "Gibbon", "Macaque", "Tamarin",
        "You_better_fold", "Prepared_to_lose?", "Take_a_mortgage", "Better_than_french_wine", "Orient_Express", "All_I_want_for_Christmas",
        "Moses", "Watch_and_Learn", "Sanpellegrino", "Dostoïevsky",
        "Droidle", "Bloop", "MechaMuffin", "Sprocket", "Blipper", "Automato", "Circuita", "Gearlo", "BeepBoop",
        "RoboRoo", "Gadget", "Blinko", "Wirey", "Flexo", "Nano", "ZipZap", "Mechano", "Bitzy", "Electra",
        "Pulsar", "Clank", "Chipper", "Bolt", "Tinker", "Click", "Ratchet", "Fizz", "Alloy", "Ion", "Lazer",
        "Rivet", "Dynamo", "Echo", "Astro", "Logic", "Mobi", "Nova", "Orbit", "Pixel", "Quantum", "Radar",
        "Sonic", "Turbo", "Vector", "Zappy", "Buzz", "Dash", "Flex", "Glimmer", "Jolt", "Kinetic", "Lumen",
        "Max", "Nexus", "Optix", "Prism", "Quark", "Reactor", "Spark", "Tronix", "Vortex", "Watt", "Xenon",
        "Yotta", "Zetta", "Aero", "Blaze", "Cosmo", "Drift", "Eon", "Faze", "Glide", "Holo", "Inertia", "Jet",
        "Kinetic", "Link", "Motion", "Neon", "Ozone"
    };

    int top=99;
    int bottom=20;
    if (number==1) {
        top=9;
        bottom=0;
    } else if (number==2) {
        top=19;
        bottom=10;
    }

    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define the distribution (0 to 99 inclusive)
    std::uniform_int_distribution<> dis(bottom,top);
    //qDebug()<<"returning an integer"<<dis(gen);
    std::string randomName= botNames.at(dis(gen));

    int counter=0;

    while (std::find(names.begin(), names.end(), randomName) != names.end()) {
        randomName=botNames.at(dis(gen));
        counter+=1;
        if (counter>=5) {
            std::uniform_int_distribution<> last(20,99);
            while (std::find(names.begin(), names.end(), randomName) != names.end()) {
                randomName=botNames.at(last(gen));
            }
        }
    }

    //qDebug()<<"here?"<<QString::fromStdString(randomName);
    return randomName;

}


