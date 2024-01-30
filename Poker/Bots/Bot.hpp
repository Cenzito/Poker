#pragma once
#include "../GameLogic/PokerPlayer.hpp"
#include <qdebug.h>
#include <cmath>
#include <random>
#include <algorithm>
#include "GameLogic/PokerHand.hpp"
#include "GameLogic/Card.hpp"
#include "GameLogic/Table.hpp"
#include "GameLogic/Monte_Carlo_Probability_Simulator.hpp"

class Bot : public PokerPlayer {
    Q_OBJECT
public :
    Bot(const std::string& name, int level) : PokerPlayer(name) {

        this -> level = level; //BotCenzo is level 7 (might change)
        this-> isBot = true;
    };

    virtual void Action() = 0;

public slots:
    void call_bet();
    void fold_bet();
    void raise_bet(int amount);
    int find_stack_size();
    protected:
        int level;
};
