#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
public:
    std::string infoSet;
    std::vector<double> regretSum;
    std::vector<double> strategySum;

    Node() : regretSum(2, 0.0), strategySum(2, 0.0) {}

    std::vector<double> getStrategy(double realizationWeight);
    std::vector<double> getAverageStrategy() const;
};

#endif // NODE_H
