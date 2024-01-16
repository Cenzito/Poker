#include "BotCenzo.hpp"
#include "../../../GameLogic/table.hpp"
#include <cmath>
#include <random>



void BotCenzo::Action(){
    float max;
    for (int i = 0; i < tableInfo.playerInfo.size(); i++) {
        max += tableInfo.playerInfo[i].stack_size;
    }
    max += tableInfo.pot;
    max = max / tableInfo.pot;

    //calculate hand proba of win using  Monte Carlo Proba Simulator
    float win;
    //check previous call
    int last_bet = tableInfo.playerInfo[tableInfo.current_player - 1].bet;
    float x; //the % of winning
    float y = last_bet / tableInfo.pot;

    float col;
    float row;

    //check what square we are in
    if (y <= 2) {
        col = floor(x/0.05);
        row = floor(y/0.1);
    }
    else {
        col = floor(x/0.05);
        row = floor((0.1 + (y - 2)) / ((max - 2) / 0.1));
    }

    //refer to matrix for probability of fold

    if (foldfunction[row][col] == 1) {
        //fold
    }

    else {
        if (static_cast<float>(rand()) / RAND_MAX < foldfunction[row][col] ) {
            //fold
        }
    }

    //else refer to matrix for probability of raise
}
