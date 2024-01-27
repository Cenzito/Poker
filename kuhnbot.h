#ifndef KUHNBOT_H
#define KUHNBOT_H

#include <iostream>
#include <string>
#include <random>
#include <map>
#include <sstream>
#include <ctime>

class Kuhnbot{
private:
    std::map<std::string, double> strategy;
    std::string card;                              // The card the bot has
    std::string history;                          // The history of actions, history can contain : "b" (opponent bet), "p" ( opponent passed), or "pb" (The Bot bet and the opponent passed)
    std::mt19937 gen;

public:
    Kuhnbot() : gen(time(0)) {}
    void loadStrategy() ;
    std::string decideAction();
};

#endif //KUHNBOT_H

