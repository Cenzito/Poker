#include "logic_scratch.hpp"

#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>

class Logic_ {

};
Player:: Player(int chips, std::vector<Cards> cards, int small_blind, int big_blind, bool is_player_still_playing) {
    this->chips = chips;
    this->cards = cards;
    this->small_blind = small_blind;
    this->big_blind = big_blind;
    this->is_player_still_playing = is_player_still_playing;
}
int Player:: get_chips() {
    return chips;
}


std::vector<Cards> Player:: get_cards() {
    return cards;
}
bool Player::is_still_playing() {
    return is_player_still_playing;
}
std::vector<Cards> Player::find_best_hand(std::vector<Cards> cards_in_middle) {
    std::vector<Cards> best_hand;
    std::vector<Cards> all_cards;
    all_cards.insert(all_cards.end(), cards.begin(), cards.end());
    all_cards.insert(all_cards.end(), cards_in_middle.begin(), cards_in_middle.end());
    
}


#endif // POKER_PLAYER_HPP
