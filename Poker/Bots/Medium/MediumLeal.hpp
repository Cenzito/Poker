#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "Bots/Bot.hpp"

class MediumLeal : public Bot {
public:
    MediumLeal(const std::string& name, int level) : Bot(name, 3) {}; //constrcutor

    void Action();

    bool SameRank(std::vector<Card> hand);
    bool SameSuit (std::vector<Card> hand);
    bool CloseRank (std::vector<Card> hand);


private:
    int NumericalCardValue;
    float lambda = 4.8; //arbitrary
    int threshold = 5; //basically arbitrary
};

#endif // MEDIUMLEAL_HPP

