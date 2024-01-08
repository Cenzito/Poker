#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name) : name(name) {}


int PokerPlayer::decideBet(int currentHighestBet, int money, int minimumRaise) {
    // Implement player decision logic here
    // For now, returning a basic decision
    return currentHighestBet + minimumRaise;
}

void PokerPlayer::receiveCards(const std::vector<Card> newHand) {
    hand = newHand;
}

void PokerPlayer::updateTable(const Table table) {
    tableInfo = table;
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

signed int PokerPlayer::Action() {
    //need to connect to buttons in order to chose the bet size

    return -1;
}




void PokerPlayer::updateChips() {
    //call server to update how many chips we have
}
