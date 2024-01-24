#include "BotCenzo.hpp"
#include "../../../GameLogic/table.hpp"
#include <cmath>
#include <random>




void BotCenzo::Action(){
    float max = 0;
    for (int i = 0; i < tableInfo.playerInfo.size(); i++) {
        max += tableInfo.playerInfo[i].stack_size;
    }
    max += tableInfo.pot;
    max = max / tableInfo.pot;

    //calculate hand proba of win using  Monte Carlo Proba Simulator
    float win;
    //check previous call
    int last_bet = tableInfo.playerInfo[tableInfo.current_player - 1].bet;
    float x = 0; //the % of winning
    float y = last_bet / tableInfo.pot;

    float col;
    float row;

    //check what square we are in
    if (y <= 2) {
        col = (int)x / 0.05;
        row = (int)y / 0.1;
    }
    else {
        col = (int)x / 0.05;
        row = (int)(0.1 + (y - 2)) / ((max - 2) / 0.1);
    }

    //refer to matrix for probability of fold

    if (foldfunction[row][col] == 1) {
        fold_bet();
    }

    else {
        if (static_cast<float>(rand()) / RAND_MAX < foldfunction[row][col] ) {
            fold_bet();
        }
    }

    //else refer to matrix for probability of raise


    if (static_cast<float>(rand()) / RAND_MAX < raisefunction[row][col]) {
        raise_bet(10); //think about how much to raise
    }

    else {
        call_bet();
    }
}

