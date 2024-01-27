#ifndef TRAINER_H
#define TRAINER_H

#include <map>
#include <random>
#include <vector>
#include "Node.h"

class Trainer {
private:
    std::mt19937 gen;  // Mersenne Twister random number generator
    static constexpr int PASS = 0, BET = 1 ;


public:
    std::map<std::string, Node> nodeMap;

    Trainer() : gen(time(0)) {} ;

    void train(int iterations);
    double cfr(const std::vector<int>& cards, const std::string& history, double p0, double p1);

};

#endif // TRAINER_H


