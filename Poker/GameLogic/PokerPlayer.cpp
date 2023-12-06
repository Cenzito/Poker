#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name, int chips) : name(name), chips(chips), active(true) {}

bool PokerPlayer::isActive() const {
    return active;
}

bool PokerPlayer::canBet(int amount) const {
    return amount <= chips;
}

void PokerPlayer::bet(int amount) {
    chips -= amount;
    // Additional logic for betting (e.g., adding to the pot)
}

int PokerPlayer::decideBet(int currentHighestBet, int minimumRaise) {
    // Implement player decision logic here
    // For now, returning a basic decision
    return currentHighestBet + minimumRaise;
}

void PokerPlayer::receiveCards(const std::vector<Card>& newHand) {
    hand = newHand;
}

void PokerPlayer::updateTable(const Table& tableInfo) {
    currentTable = tableInfo;
}

const std::string& PokerPlayer::getName() const {
    return name;
}

//
void PokerPlayer::placeBet(int amount) {
    return;
}

void PokerPlayer::receiveCards(const std::vector<Card>& cards) {
    hand = cards;
}


void PokerPlayer::showHand() const {
    std::cout << name << "'s hand: ";
    for (const auto& card : hand) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
}

void PokerPlayer::updateTable(Table table) {
    //update info about the table
    //will need to change ui after that
    tableInfo = table;
}

/*
void PokerPlayer::action(std::vector<int> table, int minAmount, int type) {
    std::cout << "Pot: " << table[0] << std::endl;
    for (int i = 1; i < table.size();i++) {
        std::cout << "Bet" << table[i] << std::endl;
    }
};*/


