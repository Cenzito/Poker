#include "Table.hpp"
#include <QApplication>
#include <iostream>
#include <sstream>

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
    qDebug() << "\n\n\n\n\n\n";
    qDebug() << "seats " << seats;
    qDebug() << "number players " << player_num;
    qDebug() << "current player " << current_player;
    qDebug() << "Button player " << ButtonPlayer;
    qDebug() << "Active player " << QString::fromStdString(playerInfo[current_player].name);
    qDebug() << "SB, BB" << SBValue << " " << BBValue << "\n";

    qDebug() << "POT " << pot;

    for (int i = 0; i < player_num; i++ ) {
        playerInfo[i].Print();
        qDebug() << "\n";
    }
}


int Table::active_players() {
    int counter=0;
    for (int i=0; i < player_num; i++) {
        if (playerInfo[i].isFold==false) {
            counter+=1;
        }
    }
    return counter;
}



void Table::updateTable(std::string command) {
    // Use std::istringstream to split the string
    if (command[0] != '/') {
        qDebug() << "invalid command";
        return;
    }

    std::istringstream iss(command);
    std::vector<std::string> wordsArray(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    std::string identifier = wordsArray[0];

    if (identifier == "/bet") {
        // "/bet PlayerName Amount"
        std::string PlayerName = wordsArray[1];
        int Amount = std::stoi(wordsArray[2]);
        qDebug() << QString::fromStdString(PlayerName) << Amount;
        PlayerInfo* current = getPlayerInfo(PlayerName);
        current->stack_size -= Amount;
        current->bet += Amount;
    } else if (identifier == "/setBiggestBet") {
        // "/setBiggest_bet amount"
        int Amount = std::stoi(wordsArray[1]);
        current_biggest_bet = Amount;
    } else if (identifier == "/win") {
        // "/pay PlayerName Amount"
        std::string PlayerName = wordsArray[1];
        int Amount = std::stoi(wordsArray[2]);
        qDebug() << QString::fromStdString(PlayerName) << Amount;
        getPlayerInfo(PlayerName)->stack_size += Amount;

    } else if (identifier == "/allin") {
        // "/pay PlayerName"
        std::string PlayerName = wordsArray[1];
        getPlayerInfo(PlayerName)->bet += getPlayerInfo(PlayerName)->stack_size;
        getPlayerInfo(PlayerName)->stack_size = 0;
        getPlayerInfo(PlayerName)->isAllin = true;
    } else if (identifier == "/fold") {
        std::string PlayerName = wordsArray[1];
        getPlayerInfo(PlayerName)->isFold = true;
    }

    else if (identifier == "/setActivePlayer") {
        // "/setActivePlayer PlayerNumber"
        int PlayerNum = std::stoi(wordsArray[1]);
        current_player = PlayerNum;
    } else if (identifier == "/addCardMid") {
        // "/addCardMid Suit Num"
        std::string Suit = wordsArray[1];
        int Num = std::stoi(wordsArray[2]);
        enum Suit s;

        s = stringToSuit(Suit);

        Card cardToAdd = Card(s, Num);
        communityCards.push_back(cardToAdd);
    } else if (identifier == "/nextRound") {
        betting_round += 1;
        for (int i = 0; i <= player_num; i++) {
            playerInfo[i].bet = 0;
        }
        current_biggest_bet = 0;
        current_player = ButtonPlayer;

        lastRaiser = current_player;

    } else if (identifier == "/resetGame") {
        //reset bets
        for (int i = 0; i <= player_num; i++) {
            playerInfo[i].bet = 0;
            playerInfo[i].isAllin = false;
            playerInfo[i].isFold = false;
        }
        pot=0;
        ButtonPlayer = (ButtonPlayer + 1)% player_num;
        communityCards=std::vector<Card>();
        current_biggest_bet = 0;
        betting_round = -1;

        current_player = ButtonPlayer;

        communityCards.clear();
    } else if (identifier == "/joinGame") {
        // "/joinGame Name chips"
        std::string PlayerName = wordsArray[1];
        int Chips = std::stoi(wordsArray[2]);

        PlayerInfo playerinfo(PlayerName, Chips, 0);
        playerInfo[player_num] = playerinfo;
        player_num += 1;
    } else if (identifier == "/setPInf") {
        // "/setPInf Player1 Stack1 Player2 Stack2 ..."
        for (int i = 1; i < wordsArray.size(); i+=2) {
            //set playerInfo
            PlayerInfo playerinfo(wordsArray[i], std::stoi(wordsArray[i+1]), 0);
            playerInfo[i/2] = playerinfo;
        }
        player_num = wordsArray.size() / 2;
    }


};



PlayerInfo* Table::getPlayerInfo(std::string name) {
    for (int i = 0; i<player_num;i++) {
        if (playerInfo[i].name == name) {
            return &playerInfo[i];
        }
    }
};




