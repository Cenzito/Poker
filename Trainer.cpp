#include "Trainer.h"
#include <fstream>
#include <algorithm>
#include <iostream>


void Trainer::train(int iterations) {
    // initialize the deck
    std::vector<int> cards = {1, 2, 3};  // Representing Jack, Queen, King

    // open a file to save the stategies
    // This will be useful for time complexity (it takes around 50 seconds to get the values with such a big number of iterations)
    // but having them saved and accessing them through a file takes much less time (linear complexity)

    std::ofstream file("Bots/Hard/Kenza/KuhnPokerStrategy.txt");

    for (int i = 0; i < iterations; ++i) {
        // Shuffle the cards
        std::shuffle(cards.begin(), cards.end(), gen);
        // Training
        cfr(cards, "", 1, 1);

    }

    // Write the strategy in the file
    for (const auto& entry : nodeMap) {
        std::vector<double> avgStrat = entry.second.getAverageStrategy();
        std::string infoStr = entry.first + ":\nPass: " + std::to_string(avgStrat[0]) + ", Bet: " + std::to_string(avgStrat[1]) + "\n";
        file << infoStr;
    }

    // Close the file.
    file.close();
}

double Trainer::cfr(const std::vector<int>& cards, const std::string& history, double p0, double p1) {
    // Determine whose turn it is based on the length of the play history
    int plays = history.length(); // Number of actions taken so far
    int player = plays % 2; // Current player (0 or 1)
    int opponent = 1 - player; // Opponent player
    int outcome = 0 ;

    // Check if the game reached its end (this is the last play)
    if (plays > 1) {
        // If the last action was a pass
        if (history.back() == 'p') {
            if (history == "pp") {
                // Both players passed: Showdown, the player with the higher card wins
                outcome = cards[player] > cards[opponent] ? 1 : -1;
            } else {
                // One player passed: the player who didn't pass wins
                outcome = 1;
            }
            // If the last two actions were bets
        } else if (plays >= 2 && history.substr(plays - 2) == "bb") {
            // Both players bet: showdown, highest card wins
            outcome = cards[player] > cards[opponent] ? 2 : -2;
        }
    }

    // If the game has reached its end, return the payoff
    if (outcome != 0) return outcome;

    // Construct the information set for the current state
    std::string infoSet = std::to_string(cards[player]) + history;

    // Access or create a node for the current information set
    auto& node = nodeMap[infoSet];
    node.infoSet = infoSet;

    // Get the current strategy
    std::vector<double> strategy = node.getStrategy(player == 0 ? p0 : p1);
    std::vector<double> utility(2, 0.0); // Utility of each action
    double nodeUtility = 0; // Total utility for the node

    // Iterate over possible actions (e.g., pass or bet)
    for (int action = 0; action < 2; action++) {
        std::string nextHistory = history + ( action == PASS ? "p" : "b"); // Update history with the new action
        // Recursively call cfr with the new history
        utility[action] = -cfr(cards, nextHistory, player == 0 ? p0 * strategy[action] : p0, player == 1 ? p1 * strategy[action] : p1);
        // Accumulate utility weighted by the strategy's probability for the action
        nodeUtility += strategy[action] * utility[action];
    }

    // Update regrets for each action
    for (int action = 0; action < 2 ; action++) {
        double regret = utility[action] - nodeUtility; // Regret is the difference between the utility of the action and the total utility
        // Update the regret sum, factoring in the probability of reaching this information set
        node.regretSum[action] += (player == 0 ? p1 : p0) * regret;
    }

    return nodeUtility; // Return the total utility for this node
}
