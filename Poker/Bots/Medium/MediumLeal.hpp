#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "Bots/Bot.hpp"
#include "../../GameLogic/PokerHand.hpp"
#include "../../GameLogic/Card.hpp"
#include "../../GameLogic/Table.hpp"

class MediumLeal : public Bot {
public:

    // Bot(const std::string& name, int level) : PokerPlayer(name) {

    //constrcutor
    MediumLeal(const std::string& name, int level) : Bot(name, 3) {};

    void Action();

private:
    int CalcCardValue();;
    PokerCombinations CardValue;
    int NumericalCardValue;
    float lambda = 4.8;
    int threshold = 5;

};

#endif // MEDIUMLEAL_HPP

