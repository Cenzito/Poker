#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name, int initialChips) : name(name), chips(initialChips) {}

int PokerPlayer::getChips() const {
    return chips;
}

void PokerPlayer::placeBet(int amount) {
    if (amount <= chips) {
        chips -= amount;
        std::cout << name << " bets " << amount << " chips." << std::endl;
    } else {
        std::cout << name << " cannot bet that amount." << std::endl;
    }
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

void PokerPlayer::winChips(int amount) {
    chips += amount;
    std::cout << name << " wins " << amount << " chips." << std::endl;
}

/*
void PokerPlayer::action(std::vector<int> table, int minAmount, int type) {
    std::cout << "Pot: " << table[0] << std::endl;
    for (int i = 1; i < table.size();i++) {
        std::cout << "Bet" << table[i] << std::endl;
    }
};*/


