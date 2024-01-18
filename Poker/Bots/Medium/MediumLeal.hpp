#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "../Bot.hpp"
#include "../../GameLogic/PokerHand.hpp"
#include "../../GameLogic/Card.hpp"
#include "../../GameLogic/Table.hpp"

class MediumLeal : public Bot {
public:

    // Bot(const std::string& name, int level) : PokerPlayer(name) {

    //constrcutor
    MediumLeal() : Bot(name, level){
        this -> level = level;
        this->name = name;
    };

private:
    int CalcCardValue();
    bool ShouldFold();
    bool ShouldRaise(int threshhold);
    PokerCombinations CardValue;
    int NumericalCardValue;
    float lambda = 4.8;
    int threshold;

};

#endif // MEDIUMLEAL_HPP

