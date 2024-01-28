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
    subpots={};
    hand_finished=true;
}

Table::Table(int seats){
    this-> seats = seats;
    ButtonPlayer=0;
    SBValue = 25;
    BBValue=50;
    pot=0;
    player_num=0;
    current_player=3;
    subpots={};
    hand_finished=true;
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
    //qDebug() << QString::fromStdString(command);

    std::istringstream iss(command);
    std::vector<std::string> wordsArray(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    CommandType cmdType = parseCommand(wordsArray[0]);
    //qDebug() << QString::fromStdString(command);

    switch (cmdType) {
    case CommandType::Bet: {
        // "/bet PlayerName Amount"
        std::string PlayerName = wordsArray[1];
        int Amount = std::stoi(wordsArray[2]);
        PlayerInfo* current = getPlayerInfo(PlayerName);
        current->stack_size -= Amount;
        current->bet += Amount;
        pot += Amount;
        break;
    } case CommandType::Win: {
        // "/pay PlayerName Amount"
        std::string PlayerName = wordsArray[1];
        int Amount = std::stoi(wordsArray[2]);
        getPlayerInfo(PlayerName)->stack_size += Amount;
        break;
    } case CommandType::SetBiggestBet:  {
        // "/setBiggest_bet amount"
        current_biggest_bet = std::stoi(wordsArray[1]);
        break;
    } case CommandType::SetLastRaiser:{
        // "/setLastRaiser number"
        lastRaiser = std::stoi(wordsArray[1]);
        break;
    } case CommandType::AllIn: {
        // "/pay PlayerName"
        std::string PlayerName = wordsArray[1];
        getPlayerInfo(PlayerName)->bet += getPlayerInfo(PlayerName)->stack_size;
        getPlayerInfo(PlayerName)->stack_size = 0;
        getPlayerInfo(PlayerName)->isAllin = true;
        break;
    } case CommandType::Fold: {
        // "/fold PlayerName"
        std::string PlayerName = wordsArray[1];
        getPlayerInfo(PlayerName)->isFold = true;
        break;
    } case CommandType::SetActivePlayer: {
        // "/setActivePlayer PlayerNumber"
        int PlayerNum = std::stoi(wordsArray[1]);
        current_player = PlayerNum;
        break;
    } case CommandType::AddCardMid: {
        // "/addCardMid Suit Num"
        std::string Suit = wordsArray[1];
        int Num = std::stoi(wordsArray[2]);
        enum Suit s;

        s = stringToSuit(Suit);

        Card cardToAdd = Card(s, Num);
        communityCards.push_back(cardToAdd);
        break;
    } case CommandType::NextRound: {
        betting_round += 1;
        for (int i = 0; i <= player_num; i++) {
            playerInfo[i].bet = 0;
            playerInfo[i].cards.clear();
        }
        qDebug()<<"IT WAS RESET";
        current_biggest_bet = 0;
        current_player = ButtonPlayer;


        lastRaiser = current_player;
        break;
    } case CommandType::ResetGame: {
        //reset bets
        qDebug()<<"IT WAS RESET";
        for (int i = 0; i <= player_num; i++) {
            playerInfo[i].bet = 0;
            playerInfo[i].isAllin = false;
            playerInfo[i].isFold = false;
            playerInfo[i].cards.clear();
        }
        pot=0;
        ButtonPlayer = (ButtonPlayer + 1)% player_num;
        communityCards=std::vector<Card>();
        current_biggest_bet = 0;
        betting_round = -1;

        current_player = ButtonPlayer;

        communityCards.clear();
        break;
    } case CommandType::JoinGame: {
        // "/joinGame Name chips"
        std::string PlayerName = wordsArray[1];
        int Chips = std::stoi(wordsArray[2]);

        PlayerInfo playerinfo(PlayerName, Chips, 0);
        playerInfo[player_num] = playerinfo;
        player_num += 1;
        break;
    } case CommandType::SetPlayerInfo: {
        // "/setPInf Player1 Stack1 Player2 Stack2 ..."
        for (int i = 1; i < wordsArray.size(); i+=2) {
            //set playerInfo
            PlayerInfo playerinfo(wordsArray[i], std::stoi(wordsArray[i+1]), 0);
            playerInfo[i/2] = playerinfo;
        }
        player_num = wordsArray.size() / 2;
        break;
    } case CommandType::SetCards: {
        // "/setCard PlayerName Suit1 Num1 Suit2 Num2"
        std::string playerName = wordsArray[1];
        std::string Suit1 = wordsArray[2];
        int Num1 = std::stoi(wordsArray[3]);

        std::string Suit2 = wordsArray[4];
        int Num2 = std::stoi(wordsArray[5]);

        enum Suit s1;
        enum Suit s2;

        s1 = stringToSuit(Suit1);
        s2 = stringToSuit(Suit2);

        Card cardToAdd1 = Card(s1, Num1);
        Card cardToAdd2 = Card(s2, Num2);
        PlayerInfo* p = getPlayerInfo(playerName);
        p->cards.push_back(cardToAdd1);
        p->cards.push_back(cardToAdd2);
        break;
    } case CommandType::FinishHand: {
        std::string opt = wordsArray[1];
        if (opt == "1") {
            hand_finished = true;
        } else {
            hand_finished = false;
        }
        break;
    }
    case CommandType::Invalid: {
        qDebug() << "not valid";
        break;
    }
    }
};

CommandType Table::parseCommand(const std::string& command) {
    if (command == "/bet") return CommandType::Bet;
    else if (command == "/setBiggestBet") return CommandType::SetBiggestBet;
    else if (command == "/setLastRaiser") return CommandType::SetLastRaiser;
    else if (command == "/win") return CommandType::Win;
    else if (command == "/allin") return CommandType::AllIn;
    else if (command == "/fold") return CommandType::Fold;
    else if (command == "/setActivePlayer") return CommandType::SetActivePlayer;
    else if (command == "/addCardMid") return CommandType::AddCardMid;
    else if (command == "/nextRound") return CommandType::NextRound;
    else if (command == "/resetGame") return CommandType::ResetGame;
    else if (command == "/joinGame") return CommandType::JoinGame;
    else if (command == "/setPInf") return CommandType::SetPlayerInfo;
    else if (command == "/setCard") return CommandType::SetCards;
    else if (command == "/finishHand") return CommandType::FinishHand;
    else return CommandType::Invalid;
}

PlayerInfo* Table::getPlayerInfo(std::string name) {
    for (int i = 0; i<player_num;i++) {
        if (playerInfo[i].name == name) {
            return &playerInfo[i];
        }
    }
};


int Table::playerIndex(std::string& name){
    int index=-1;
    for (int i = 0; i < player_num; i++) {
        if (playerInfo[i].name == name) {
            index=i;
        }
    }
    return index;
}

