#include "BotCenzo.hpp"
#include "../../../GameLogic/Table.hpp"
#include "../../../GameLogic/GameLocal.hpp"
#include "../../../GameLogic/PokerPlayer.hpp"
#include <cmath>
#include <random>
#include <QDebug>
#include <QFile>
#include <QTextStream>



double randnumb_generator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}



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
    int last_bet = tableInfo.current_biggest_bet;
    float x = 1 - Winning_Probability(tableInfo, hand, tableInfo.player_num, 1000)[2];
    float y = static_cast<float>(last_bet) / tableInfo.pot;
    //qDebug() << "y" << y;

    float col;
    float row;

    //check what square we are in
    if (y <= 2) {
        col = std::floor(x / 0.05);
        row = std::floor(y / 0.1); //division by right number??
    }
    else {
        col = std::floor(x / 0.05);
        row = std::floor((10 + ((y - 2)) / ((max - 2) * 0.1)));
    }
    //qDebug() << "col:" <<col <<" row:" << row;

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

