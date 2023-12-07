#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name, int initialChips) : name(name) {}

//
void PokerPlayer::placeBet(int amount) {
    return;
}

void PokerPlayer::receiveCards(const std::vector<Card>& cards) {
    hand = cards;
}


std::vector<Card> PokerPlayer::getHand() const {
    std::cout << name << "'s hand: ";
    for (const auto& card : hand) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
    return hand;
}

void PokerPlayer::updateTable(Table table) {
    //update info about the table
    //will need to change ui after that
    tableInfo = table;
}

void PokerPlayer::removeCards() {
    hand = std::vector<Card>();
}

/*
void PokerPlayer::action(std::vector<int> table, int minAmount, int type) {
    std::cout << "Pot: " << table[0] << std::endl;
    for (int i = 1; i < table.size();i++) {
        std::cout << "Bet" << table[i] << std::endl;
    }
};*/


