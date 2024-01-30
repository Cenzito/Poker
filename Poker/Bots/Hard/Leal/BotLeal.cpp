#include "BotLeal.hpp"

double randnumb_generator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}


void BotLeal::Action(){
    float max = 0;
    for (int i = 0; i < tableInfo.playerInfo.size(); i++) {
        max += tableInfo.playerInfo[i].stack_size;
    }
    max += tableInfo.pot;
    max = max / tableInfo.pot;

    //calculate hand proba of win using  Monte Carlo Proba Simulator
    float win;
    //check previous call
    int last_bet = tableInfo.current_biggest_bet;
    float x = 0; //the % of winning
    float y = last_bet / tableInfo.pot;
    qDebug() << "last bet:" << tableInfo.current_biggest_bet;
    qDebug() << "x:" <<x <<" y:" << 50/75;

    float col;
    float row;

    //check what square we are in
    if (y <= 2) {
        col = (int)x / 0.05;
        row = (int)y / 0.1;
    }
    else {
        col = (int)x / 0.05;
        row = (int)(10 + ((y - 2)) / ((max - 2) * 0.1));
    }
    qDebug() << "col:" <<col <<" row:" << row;

    //refer to matrix for probability of fold


    if (randnumb_generator() < foldfunction[row][col] ) {
        fold_bet();

    }

    //else refer to matrix for probability of raise

    else if (randnumb_generator() < raisefunction[row][col]) {
        raise_bet(tableInfo.current_biggest_bet); //think about how much to raise
    }

    else {
        call_bet();
    }
}

