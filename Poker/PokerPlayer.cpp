#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <string>


PokerPlayer::PokerPlayer(const std::string& name, int initialChips) : name(name), initialChips(initialChips), current_bet(0) {}

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

void PokerPlayer::call(int bet_on_table) {//TO BE DONE: manage the case where Not enough chips DO THIS IN OTHER Function
    //decreases Chips available by bet_on_table - current_bet
    initialChips -= (bet_on_table - current_bet);
    //changes current_bet = bet_on_table
    current_bet = bet_on_table;
}

int PokerPlayer::raise(int bet_on_table) { //TO BE DONE: check if input follows guidelines (integer)
    //TO BE DONE: Ask raise amount !!!there are minimums (check poker rules)
    std::string userInput;
    std::cout << "By how much woud you like to raise: "; 
    //TO BE DONE: minimum based on small_blind and bet_on_table
    std::cin >> userInput;
    int amount_to_raise = std::stoi(userInput);

    initialChips -= amount_to_raise; //decreases Chips available by amount_to_raise
    current_bet += amount_to_raise; //changes current_bet = amount_to_raise + current_bet
    //returns current_bet + amount_to_raise = updated current bet
    return current_bet; //this returns allows us to redefine the general bet on the table
}

int PokerPlayer::fold() {
    //change value of player_stopped_playing to true
    isFold = true;
    //returns current bet to add to total pot
    int current_bet_2 = current_bet; //allows us to make current bet 0 while returning current_bet_2
    current_bet = 0;
    return current_bet_2;
}
