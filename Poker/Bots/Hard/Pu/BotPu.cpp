#include "BotPu.hpp"

const double eps = 0.001;
const int iter_lim = 1000;

bool BotPu::initialized = false;
int BotPu::cnt5 = 0, BotPu::cnt_hand = 0;
int** BotPu::id_to_hand = new int*[91];
int** BotPu::hand_to_id = new int*[13];
int**** BotPu::cfr5 = new int***[7];
int** BotPu::id_to_card5 = new int*[6175];
int***** BotPu::card_to_id5 = new int****[13];
int cnt_card[13];
bool card_suit[13][4];

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
        for(int i = 0; i < 91; i++)
            id_to_hand[i] = new int[2];
        for(int i = 0; i < 13; i++) {
            hand_to_id[i] = new int[13];
            for(int j = i; j < 13; j++) {
                id_to_hand[cnt_hand][0] = i;
                id_to_hand[cnt_hand][1] = j;
                hand_to_id[i][j] = cnt_hand;
                cnt_hand++;
            }
        }
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

int rand_int(int a, int b) {
    std::random_device r;
    std::mt19937 gen(r());
    std::uniform_int_distribution<int> distribute(a, b);
    return distribute(gen);
}

int BotPu::get_cfr5(int player_num, int handid, int riverid) {
    int cfr5_norm[3];
    for(int i = 0; i < 3; i++)
        cfr5_norm[i] = std::max(0, cfr5[player_num][handid][riverid][i]);
    if(cfr5_norm[0] == 0 && cfr5_norm[1] == 0 && cfr5_norm[2] == 0)
        return 0;
    float choice_dist[3];
    for(int i = 0; i < 3; i++)
        choice_dist[i] = 1.0 * cfr5_norm[i] / (1.0 * cfr5_norm[0] + cfr5_norm[1] + cfr5_norm[2]);
    float percentage = rand_float();
    if(percentage - eps <= choice_dist[0])
        return 0;
    else if(percentage - eps <= choice_dist[0] + choice_dist[1])
        return 1;
    else
        return 2;
}

void BotPu::Action(){
    int round = tableInfo.communityCards.size();
    if(round == 0) {
        std::vector<float> probability = Winning_Probability(tableInfo, hand, tableInfo.player_num, 10000);
        float prob_not_lose = probability[0] + probability[1];
        float factor = 1.0 - rand_float() / 2.0;
        float lim = (1.0 / tableInfo.player_num) * factor;
        if(prob_not_lose >= lim)
            call_bet();
        else
            fold_bet();
    }
    int player_suit[8][2], player_hand[8][2], player_handid[8];
    bool folded[8];
    std::vector<Card> hand_self = getHand();
    player_hand[0][0]= hand_self[0].getValue() - 2;
    player_hand[0][1] = hand_self[1].getValue() - 2;
    player_suit[0][0] = (int) hand_self[0].getSuit();
    player_suit[0][1] = (int) hand_self[1].getSuit();
    if(player_hand[0][0] > player_hand[0][1]) {
        std::swap(player_hand[0][0], player_hand[0][1]);
        std::swap(player_suit[0][0], player_suit[0][1]);
    }
    player_handid[0] = hand_to_id[player_hand[0][0]][player_hand[0][1]];
    if(round == 3) {
        call_bet();
    }
    if(round == 4) {
        call_bet();
    }
    if(round== 5) {
        int card_num[5];
        for(int i = 0; i < 5; i++)
            card_num[i] = tableInfo.communityCards[i].getValue() - 2;
        std::sort(card_num, card_num + 5);
        int cardid = card_to_id5[card_num[0]][card_num[1]][card_num[2]][card_num[3]][card_num[4]];
        for(int _ = 0; _ < iter_lim; _++) {
            if(abs(cfr5[tableInfo.player_num - 2][player_handid[0]][cardid][0]) > 500000000 ||
                abs(cfr5[tableInfo.player_num - 2][player_handid[0]][cardid][1]) > 500000000 ||
                abs(cfr5[tableInfo.player_num - 2][player_handid[0]][cardid][2]) > 500000000)
                break;
            for(int i = 0; i < tableInfo.player_num; i++)
                folded[i] = false;
            for(int i = 0; i < 13; i++) {
                cnt_card[i] = 0;
                for(int j = 0; j < 4; j++)
                    card_suit[i][j] = false;
            }
            cnt_card[player_hand[0][0]]++;
            cnt_card[player_hand[0][1]]++;
            card_suit[getHand()[0].getValue() - 2][int(getHand()[0].getSuit())] = true;
            card_suit[getHand()[1].getValue() - 2][int(getHand()[1].getSuit())] = true;
            for(Card card : tableInfo.communityCards) {
                cnt_card[card.getValue() - 2]++;
                card_suit[card.getValue() - 2][int(card.getSuit())] = true;
            }
            for(int i = 1; i < tableInfo.player_num; i++) {
                while(true) {
                    int handid = rand_int(0, 90);
                    int cardV1 = id_to_hand[handid][0];
                    int cardV2 = id_to_hand[handid][1];
                    if(cnt_card[cardV1] == 4 || cnt_card[cardV2] == 4)
                        continue;
                    if(cardV1 == cardV2 && cnt_card[cardV1] == 3)
                        continue;
                    player_handid[i] = handid;
                    player_hand[i][0] = cardV1, player_hand[i][1] = cardV2;
                    cnt_card[cardV1]++;
                    cnt_card[cardV2]++;
                    break;
                }
            }
            for(int i = 1; i < tableInfo.player_num; i++) {
                while(true) {
                    int suit = rand_int(0, 3);
                    if(card_suit[player_hand[i][0]][suit])
                        continue;
                    card_suit[player_hand[i][0]][suit] = true;
                    player_suit[i][0] = suit;
                    break;
                }
                while(true) {
                    int suit = rand_int(0, 3);
                    if(card_suit[player_hand[i][1]][suit])
                        continue;
                    card_suit[player_hand[i][1]][suit] = true;
                    player_suit[i][1] = suit;
                    break;
                }
            }
            std::vector<Card> playerHand[8];
            for(int i = 0; i < tableInfo.player_num; i++) {
                playerHand[i].clear();
                playerHand[i].push_back(Card(Suit (player_suit[i][0]), player_hand[i][0] + 2));
                playerHand[i].push_back(Card(Suit (player_suit[i][1]), player_hand[i][1] + 2));
            }
            int player_action[8];
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(tableInfo.playerInfo[i].isFold)
                    continue;
                player_action[i] = get_cfr5(tableInfo.player_num - 2, player_handid[i], cardid);
            }
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(tableInfo.playerInfo[i].isFold)
                    folded[i] = true;
                if(player_action[i] == 2)
                    folded[i] = true;
            }
            std::vector<int> notFolded;
            notFolded.clear();
            notFolded.push_back(0);
            bool win0;
            int cnt_winner = 0;
            for(int i = 1; i < tableInfo.player_num; i++)
                notFolded.push_back(i);
            for(int i : notFolded) {
                std::vector<Card> firstvect = playerHand[i];
                firstvect.insert(firstvect.end(), tableInfo.communityCards.begin(), tableInfo.communityCards.end());
                PokerHand firstHand(firstvect);
                bool win = true;
                for(int j : notFolded) {
                    if(j == i)
                        continue;
                    std::vector<Card> secondvect = playerHand[j];
                    secondvect.insert(secondvect.end(), tableInfo.communityCards.begin(), tableInfo.communityCards.end());
                    PokerHand secondHand(secondvect);
                    if(compare_hands(firstHand, secondHand) == 2) {
                        win = false;
                        break;
                    }
                }
                if(win == true)
                    cnt_winner++;
                if(i == 0)
                    win0 = win;
            }
            int gain[3];
            gain[2] = - int ((tableInfo.playerInfo[tableInfo.current_player].bet) / tableInfo.BBValue);
            int cnt_folded = 0, cnt_raised = 0;
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(folded[i]) {
                    cnt_folded++;
                    continue;
                }
                if(player_action[i] == 1)
                    cnt_raised++;
            }
            int cnt_notfolded = tableInfo.player_num - cnt_folded;
            if(win0) {
                gain[0] = (cnt_raised * (cnt_notfolded - 1) + (tableInfo.pot - tableInfo.playerInfo[tableInfo.current_player].bet) / (tableInfo.BBValue)) / cnt_winner;
                gain[1] = ((cnt_raised + 1) * (cnt_notfolded - 1) + (tableInfo.pot - tableInfo.playerInfo[tableInfo.current_player].bet) / (tableInfo.BBValue)) / cnt_winner;
            }
            else {
                gain[0] = - (cnt_raised + tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue);
                gain[1] = - (cnt_raised + 1 + tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue);
            }
            int choice = get_cfr5(tableInfo.player_num - 2, player_handid[0], cardid);
            for(int i = 0; i < 3; i++) {
                if(i == choice)
                    continue;
                cfr5[tableInfo.player_num - 2][player_handid[0]][cardid][i] += (gain[i] - gain[choice]);
            }
        }
        int choice = get_cfr5(tableInfo.player_num - 2, player_handid[0], cardid);
        if(choice == 0)
            call_bet();
        else if(choice == 1)
            raise_bet(tableInfo.BBValue);
        else
            fold_bet();
    }
}
