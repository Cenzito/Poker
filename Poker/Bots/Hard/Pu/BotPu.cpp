#include "BotPu.hpp"

const double eps = 0.001;
const double time_limit = 3;

bool BotPu::initialized = false;
int**** BotPu::cfr5 = new int***[7];
int** BotPu::id_to_card5 = new int*[6175];
int***** BotPu::card_to_id5 = new int****[13];


BotPu::BotPu(const std::string& name) : Bot(name, 12) {
    if(initialized == false) {
        for(int i = 0; i < 7; i++){
            cfr5[i] = new int**[91];
            for(int j = 0; j < 91; j++) {
                cfr5[i][j] = new int*[6175];
                for(int k = 0; k < 6175; k++) {
                    cfr5[i][j][k] = new int[3];
                    for(int h = 0; h < 3; h++)
                        cfr5[i][j][k][h] = 0;
                }
            }
        }
        int cnt5 = 0;
        for(int i = 0; i < 6175; i++)
            id_to_card5[i] = new int[5];
        for(int i = 0; i < 13; i++) {
            card_to_id5[i] = new int***[13];
            for(int j = 0; j < 13; j++) {
                card_to_id5[i][j] = new int**[13];
                for(int k = 0; k < 13; k++) {
                    card_to_id5[i][j][k] = new int*[13];
                    for(int l = 0; l < 13; l++)
                        card_to_id5[i][j][k][l] = new int[13];
                }
            }
        }
        for(int i = 0; i < 13; i++)
            for(int j = i; j < 13; j++)
                for(int k = j; k < 13; k++)
                    for(int l = k; l < 13; l++)
                        for(int h = std::max(i + 1, l); h < 13; h++) {
                            card_to_id5[i][j][k][l][h] = cnt5;
                            id_to_card5[cnt5][0] = i;
                            id_to_card5[cnt5][1] = j;
                            id_to_card5[cnt5][2] = k;
                            id_to_card5[cnt5][3] = l;
                            id_to_card5[cnt5][4] = h;
                            cnt5++;
                        }
        initialized = true;
    }
}

float rand_float() {
    std::random_device r;
    std::mt19937 gen(r());
    std::uniform_real_distribution<> uniform_dist(0.0, 1.0);
    return uniform_dist(gen);
}

void BotPu::Action(){
    int round = tableInfo.communityCards.size();
    if(round == 0) {
        std::vector<float> probability = Winning_Probability(tableInfo, hand, tableInfo.current_player, 10000);
        float prob_not_lose = probability[0] + probability[1];
        float factor = rand_float() / 2.5 + 0.8;
        float lim = (1.0 / tableInfo.current_player) * factor;
        if(prob_not_lose >= lim)
            call_bet();
        else
            fold_bet();
    }
    else if(round == 3) {
        call_bet();
    }
    else if(round == 4) {
        call_bet();
    }
    else {
        call_bet();
    }
}
