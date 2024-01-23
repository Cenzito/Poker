#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <qdebug.h>


PokerPlayer::PokerPlayer(const std::string& name) : name(name) {}


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


