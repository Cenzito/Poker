// In Monte_Carlo_Probability_Simulator.h
#ifndef MONTE_CARLO_PROBABILITY_SIMULATOR_H
#define MONTE_CARLO_PROBABILITY_SIMULATOR_H

#include "PokerHand.hpp"
#include "Deck.hpp"
#include <iostream>
#include "Table.hpp"

std::vector<float> Winning_Probability(Table &table, std::vector<Card> &hand, int num_players, int num_simulations);

#endif // MONTE_CARLO_PROBABILITY_SIMULATOR_H
