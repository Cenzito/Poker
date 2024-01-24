#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <qdebug.h>


PokerPlayer::PokerPlayer(const std::string& name) : name(name) {
    this->isBot=false;
}


void PokerPlayer::receiveCards(const std::vector<Card> newHand) {
    hand = newHand;
}

void PokerPlayer::updateTable(std::string command) {
    tableInfo.updateTable(command);
    emit callUpdateDisplay();
}

void PokerPlayer::updatePInf(std::string commandPInf) {
    updateTable(commandPInf);
}

const std::string& PokerPlayer::getName() const {
    return name;
}


std::vector<Card> PokerPlayer::getHand() const {
    return hand;
}


void PokerPlayer::removeCards() {
    hand = std::vector<Card>();
}

void PokerPlayer::Action() {
    //to be changed only to display betting buttons
    emit callUpdateDisplay();
}


int PokerPlayer::get_percentage(int card1, int card2, bool IsSuited){
    int values[13 * 13] = {
        51, 35, 36, 37, 37, 37, 40, 42, 44, 47, 49, 53, 57,
        39, 55, 38, 39, 39, 39, 40, 43, 45, 48, 50, 54, 58,
        40, 42, 58, 41, 41, 41, 42, 43, 46, 48, 51, 54, 59,
        41, 43, 44, 61, 43, 43, 44, 45, 47, 49, 52, 55, 60,
        40, 42, 44, 46, 64, 45, 46, 47, 48, 50, 53, 56, 59,
        41, 43, 45, 46, 58, 67, 47, 48, 50, 52, 54, 57, 60,
        43, 43, 45, 47, 49, 50, 69, 50, 52, 53, 55, 58, 61,
        45, 46, 46, 48, 50, 51, 53, 72, 53, 55, 57, 59, 62,
        47, 48, 49, 49, 51, 53, 54, 56, 75, 57, 59, 61, 64,
        50, 50, 51, 52, 53, 54, 56, 57, 59, 78, 59, 62, 65,
        52, 53, 54, 55, 55, 56, 58, 59, 61, 61, 80, 62, 65,
        55, 56, 57, 58, 58, 59, 60, 61, 63, 64, 64, 83, 66,
        59, 60, 61, 62, 62, 63, 63, 64, 66, 66, 67, 68, 85
    };

    int matrix[13][13];
    int index = 0; // Index for accessing values array

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 13; ++j) {
            matrix[i][j] = values[index++];
        }
    }
    int percentage;
    int m1, m2;
    if (card1 > card2){m1 = card1; m2 = card2;}
    else {m1 = card2; m2 = card1;}

    if (IsSuited){
        percentage = matrix[m1-2][m2-2];
    }
    else {
        percentage = matrix[m2-2][m1-2];
    }
    return percentage;
}



