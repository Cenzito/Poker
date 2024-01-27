#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "../Bot.hpp"
#include "../../GameLogic/PokerHand.hpp"
#include "../../GameLogic/Card.hpp"
#include "../../GameLogic/Table.hpp"

class MediumLeal : public Bot {
public:

    //constrcutor
    MediumLeal(const std::string& name) : Bot(name, 3){
        this -> level = level;
        this->name = name;
    };

private:
    int CalcCardValue();
    PokerCombinations CardValue;
    int NumericalCardValue;
    float lambda = 4.8;
    int card_threshold = 4;

};

#endif // MEDIUMLEAL_HPP

