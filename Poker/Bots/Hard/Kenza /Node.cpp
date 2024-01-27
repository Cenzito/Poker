#include "Node.h"
#include <algorithm>
#include <sstream>

// Calculate and return the current strategy based on regret sums.
std::vector<double> Node::getStrategy(double realizationWeight) {
    std::vector<double> strategy(2, 0.0);
    double normalizingSum = 0.0;

    // Calculate the normalizing sum based on positive regrets
    for (int i = 0; i < 2; ++i) {
        strategy[i] = std::max(regretSum[i], 0.0);
        normalizingSum += strategy[i];
    }
    // Normalize the strategy or assign equal probability if no positive regret
    if (normalizingSum > 0) {
        for (int i = 0; i < 2; ++i) {
            strategy[i] /= normalizingSum;
        }
    } else {
        strategy.assign(2, 0.5); // Assign equal probability if no positive regrets
    }

    // Normalize the strategy or assign equal probability if no positive regret
    for (int i = 0; i < 2; ++i) {
        strategySum[i] += realizationWeight * strategy[i]; // Update cumulative strategy sum
    }
    return strategy; // Return the normalized strategy
}

// Calculate and return the average strategy over all iterations.
std::vector<double> Node::getAverageStrategy() const {
    double normalizingSum = strategySum[0] + strategySum[1] ;  // Sum from both actions
    std::vector<double> avgStrategy = {0.5, 0.5}; // Default to equal probabilities


    if (normalizingSum > 0) {
        for (int i = 0; i < 2; ++i) avgStrategy[i] = strategySum[i] / normalizingSum;
    }

    return avgStrategy; // Return the normalized average strategy
}

