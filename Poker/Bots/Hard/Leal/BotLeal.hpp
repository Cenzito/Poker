#ifndef BOTLEAL_H
#define BOTLEAL_H
#include "./../../Bot.hpp"

//#include <mlpack/core.hpp>
//#include <mlpack/methods/logistic_regression/logistic_regression.hpp>


class BotLeal : public Bot {

public:
    BotLeal(const std::string& name) : Bot(name,7) {};

    void Action();
    //matrix adjustraise; what?

};

#endif // BOTLEAL_H
