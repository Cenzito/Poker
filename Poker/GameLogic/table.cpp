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
    std::istringstream iss(command);

    // Count the number of words
    int wordCount = 0;
    while (iss) {
        std::string word;
        iss >> word;
        wordCount++;
    }

    // Allocate memory for the array
    std::string *wordsArray = new std::string[wordCount];

    // Reset the stringstream and fill the array
    iss.clear();
    iss.seekg(0, std::ios::beg);
    int i = 0;
    while (iss >> wordsArray[i]) {
        i++;
    }


    std::string identifier = wordsArray[0];

    if (identifier == "/bet") {
        // "/bet PlayerName Amount"
        std::string PlayerName = wordsArray[1];
        std::string Amount = wordsArray[2];

    } else if (identifier == "/pay") {
        // "/pay PlayerName Amount"
        std::string PlayerName = wordsArray[1];
        std::string Amount = wordsArray[2];
    } else if (identifier == "/setActivePlayer") {
        // "/setActivePlayer PlayerName"
        std::string PlayerName = wordsArray[1];
    } else if (identifier == "/addCardMid") {
        // "/addCardMid Suit Num"
        std::string Suit = wordsArray[1];
        std::string Num = wordsArray[2];
    } else if (identifier == "/addCardHand") {
        // "/addCardHand Suit Num"
        std::string Suit = wordsArray[1];
        std::string Num = wordsArray[2];


    } else if (identifier == "/nextRound") {

    } else if (identifier == "/resetGame") {

    }


};





