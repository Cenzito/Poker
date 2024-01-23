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

void PokerPlayer::updateTable(const Table table) {
    tableInfo = table;
    emit callUpdateDisplay();
}

const std::string& PokerPlayer::getName() const {
    return name;
}


std::vector<Card> PokerPlayer::getHand() const {
    std::cout << name << "'s hand: ";
    for (const auto& card : hand) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
    return hand;
}


void PokerPlayer::removeCards() {
    hand = std::vector<Card>();
}

void PokerPlayer::Action() {
    //to be changed only to display betting buttons
    emit callUpdateDisplay();
}


