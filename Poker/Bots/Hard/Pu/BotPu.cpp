#include "BotPu.hpp"

const double eps = 0.001;
const int iter_lim = 1000;

bool BotPu::initialized = false;
int BotPu::cnt5 = 0, BotPu::cnt4 = 0, BotPu::cnt3 = 0, BotPu::cnt_hand = 0;
int** BotPu::id_to_hand = new int*[91];
int** BotPu::hand_to_id = new int*[13];
int**** BotPu::cfr5 = new int***[7];
int**** BotPu::cfr4 = new int***[7];
int**** BotPu::cfr3 = new int***[7];
int** BotPu::id_to_card5 = new int*[6175];
int***** BotPu::card_to_id5 = new int****[13];
int** BotPu::id_to_card4 = new int*[1820];
int**** BotPu::card_to_id4 = new int***[13];
int** BotPu::id_to_card3 = new int*[455];
int*** BotPu::card_to_id3 = new int**[13];
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
        for(int i = 0; i < 7; i++){
            cfr4[i] = new int**[91];
            for(int j = 0; j < 91; j++) {
                cfr4[i][j] = new int*[1820];
                for(int k = 0; k < 1820; k++) {
                    cfr4[i][j][k] = new int[3];
                    for(int h = 0; h < 3; h++)
                        cfr4[i][j][k][h] = 0;
                }
            }
        }
        for(int i = 0; i < 7; i++){
            cfr3[i] = new int**[91];
            for(int j = 0; j < 91; j++) {
                cfr3[i][j] = new int*[455];
                for(int k = 0; k < 455; k++) {
                    cfr3[i][j][k] = new int[3];
                    for(int h = 0; h < 3; h++)
                        cfr3[i][j][k][h] = 0;
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
        for(int i = 0; i < 1820; i++)
            id_to_card4[i] = new int[4];
        for(int i = 0; i < 455; i++)
            id_to_card3[i] = new int[3];
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
        for(int i = 0; i < 13; i++) {
            card_to_id4[i] = new int**[13];
            for(int j = 0; j < 13; j++) {
                card_to_id4[i][j] = new int*[13];
                for(int k = 0; k < 13; k++)
                    card_to_id4[i][j][k] = new int[13];
            }
        }
        for(int i = 0; i < 13; i++) {
            card_to_id3[i] = new int*[13];
            for(int j = 0; j < 13; j++)
                card_to_id3[i][j] = new int[13];
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
        for(int i = 0; i < 13; i++)
            for(int j = i; j < 13; j++)
                for(int k = j; k < 13; k++)
                    for(int l = k; l < 13; l++) {
                        card_to_id4[i][j][k][l] = cnt4;
                        id_to_card4[cnt4][0] = i;
                        id_to_card4[cnt4][1] = j;
                        id_to_card4[cnt4][2] = k;
                        id_to_card4[cnt4][3] = l;
                        cnt4++;
                    }
        for(int i = 0; i < 13; i++)
            for(int j = i; j < 13; j++)
                for(int k = j; k < 13; k++) {
                    card_to_id3[i][j][k] = cnt3;
                    id_to_card3[cnt3][0] = i;
                    id_to_card3[cnt3][1] = j;
                    id_to_card3[cnt3][2] = k;
                    cnt3++;
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
    if(cfr5[player_num][handid][riverid][0] == 0 && cfr5[player_num][handid][riverid][1] == 0 && cfr5[player_num][handid][riverid][2] == 0)
        return 0;
    if(cfr5[player_num][handid][riverid][0] <= 0 && cfr5[player_num][handid][riverid][1] <= 0 && cfr5[player_num][handid][riverid][2] <= 0) {
        if(cfr5[player_num][handid][riverid][0] >= cfr5[player_num][handid][riverid][1] && cfr5[player_num][handid][riverid][0] >= cfr5[player_num][handid][riverid][2])
            return 0;
        if(cfr5[player_num][handid][riverid][1] >= cfr5[player_num][handid][riverid][2])
            return 1;
        return 2;
    }
    int cfr5_norm[3];
    for(int i = 0; i < 3; i++)
        cfr5_norm[i] = std::max(0, cfr5[player_num][handid][riverid][i]);
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

int BotPu::get_cfr4(int player_num, int handid, int riverid) {
    if(cfr4[player_num][handid][riverid][0] == 0 && cfr4[player_num][handid][riverid][1] == 0 && cfr4[player_num][handid][riverid][2] == 0)
        return 0;
    if(cfr4[player_num][handid][riverid][0] <= 0 && cfr4[player_num][handid][riverid][1] <= 0 && cfr4[player_num][handid][riverid][2] <= 0) {
        if(cfr4[player_num][handid][riverid][0] >= cfr4[player_num][handid][riverid][1] && cfr4[player_num][handid][riverid][0] >= cfr4[player_num][handid][riverid][2])
            return 0;
        if(cfr4[player_num][handid][riverid][1] >= cfr4[player_num][handid][riverid][2])
            return 1;
        return 2;
    }
    int cfr4_norm[3];
    for(int i = 0; i < 3; i++)
        cfr4_norm[i] = std::max(0, cfr4[player_num][handid][riverid][i]);
    float choice_dist[3];
    for(int i = 0; i < 3; i++)
        choice_dist[i] = 1.0 * cfr4_norm[i] / (1.0 * cfr4_norm[0] + cfr4_norm[1] + cfr4_norm[2]);
    float percentage = rand_float();
    if(percentage - eps <= choice_dist[0])
        return 0;
    else if(percentage - eps <= choice_dist[0] + choice_dist[1])
        return 1;
    else
        return 2;
}

int BotPu::get_cfr3(int player_num, int handid, int riverid) {
    if(cfr3[player_num][handid][riverid][0] == 0 && cfr3[player_num][handid][riverid][1] == 0 && cfr3[player_num][handid][riverid][2] == 0)
        return 0;
    if(cfr3[player_num][handid][riverid][0] <= 0 && cfr3[player_num][handid][riverid][1] <= 0 && cfr3[player_num][handid][riverid][2] <= 0) {
        if(cfr3[player_num][handid][riverid][0] >= cfr3[player_num][handid][riverid][1] && cfr3[player_num][handid][riverid][0] >= cfr3[player_num][handid][riverid][2])
            return 0;
        if(cfr3[player_num][handid][riverid][1] >= cfr3[player_num][handid][riverid][2])
            return 1;
        return 2;
    }
    int cfr3_norm[3];
    for(int i = 0; i < 3; i++)
        cfr3_norm[i] = std::max(0, cfr3[player_num][handid][riverid][i]);
    float choice_dist[3];
    for(int i = 0; i < 3; i++)
        choice_dist[i] = 1.0 * cfr3_norm[i] / (1.0 * cfr3_norm[0] + cfr3_norm[1] + cfr3_norm[2]);
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
        float factor = 0.8 + rand_float() / 2.5;
        float lim = (1.0 / tableInfo.player_num) * factor;
        if(prob_not_lose > 2.0)
            raise_bet(tableInfo.BBValue);
        else if(prob_not_lose >= lim)
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
        int card_num[5];
        for(int i = 0; i < 3; i++)
            card_num[i] = tableInfo.communityCards[i].getValue() - 2;
        std::sort(card_num, card_num + 3);
        int cardid1 = card_to_id3[card_num[0]][card_num[1]][card_num[2]];
        for(int _ = 0; _ < iter_lim; _++) {
            if(abs(cfr3[tableInfo.player_num - 2][player_handid[0]][cardid1][0]) > 500000000 ||
                abs(cfr3[tableInfo.player_num - 2][player_handid[0]][cardid1][1]) > 500000000 ||
                abs(cfr3[tableInfo.player_num - 2][player_handid[0]][cardid1][2]) > 500000000)
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
            std::vector<Card> community = tableInfo.communityCards;
            int value1, suit1;
            while(true) {
                int x = rand_int(0, 12);
                if(cnt_card[x] == 4)
                    continue;
                value1 = x;
                cnt_card[x]++;
                break;
            }
            while(true) {
                int s = rand_int(0, 3);
                if(card_suit[value1][s])
                    continue;
                suit1 = s;
                card_suit[value1][s] = true;
                break;
            }
            card_num[3] = value1;
            community.push_back(Card((Suit) suit1, value1 + 2));
            std::sort(card_num, card_num + 4);
            int cardid2 = card_to_id4[card_num[0]][card_num[1]][card_num[2]][card_num[3]];
            int value2, suit2;
            while(true) {
                int x = rand_int(0, 12);
                if(cnt_card[x] == 4)
                    continue;
                value2 = x;
                cnt_card[x]++;
                break;
            }
            while(true) {
                int s = rand_int(0, 3);
                if(card_suit[value2][s])
                    continue;
                suit2 = s;
                card_suit[value2][s] = true;
                break;
            }
            card_num[4] = value2;
            community.push_back(Card((Suit) suit2, value2 + 2));
            std::sort(card_num, card_num + 5);
            int cardid3 = card_to_id5[card_num[0]][card_num[1]][card_num[2]][card_num[3]][card_num[4]];
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
            int player_action1[8], player_action2[8], player_action3[8];
            for(int i = 1; i < tableInfo.player_num; i++)
                player_action1[i] = get_cfr3(tableInfo.player_num - 2, player_handid[i], cardid1);
            for(int i = 0; i < tableInfo.player_num; i++)
                player_action2[i] = get_cfr4(tableInfo.player_num - 2, player_handid[i], cardid2);
            for(int i = 0; i < tableInfo.player_num; i++)
                player_action3[i] = get_cfr5(tableInfo.player_num - 2, player_handid[i], cardid3);
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(tableInfo.playerInfo[i].isFold)
                    folded[i] = true;
                if(player_action1[i] == 2)
                    folded[i] = true;
            }
            int gain[3];
            gain[2] = - int ((tableInfo.playerInfo[tableInfo.current_player].bet) / tableInfo.BBValue);
            int cnt_folded1 = 0, cnt_raised1 = 0;
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(folded[i]) {
                    cnt_folded1++;
                    continue;
                }
                if(player_action1[i] == 1)
                    cnt_raised1++;
            }
            int cnt_notfolded1 = tableInfo.player_num - cnt_folded1;
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(player_action2[i] == 2)
                    folded[i] = true;
            }
            int cnt_folded2 = 0, cnt_raised2 = 0;
            for(int i = 0; i < tableInfo.player_num; i++) {
                if(folded[i]) {
                    cnt_folded2++;
                    continue;
                }
                if(player_action2[i] == 1)
                    cnt_raised2++;
            }
            int cnt_notfolded2 = tableInfo.player_num - cnt_folded2;
            for(int i = 0; i < tableInfo.player_num; i++) {
                if(player_action3[i] == 2)
                    folded[i] = true;
            }
            int cnt_folded3 = 0, cnt_raised3 = 0;
            for(int i = 0; i < tableInfo.player_num; i++) {
                if(folded[i]) {
                    cnt_folded3++;
                    continue;
                }
                if(player_action3[i] == 1)
                    cnt_raised3++;
            }
            int cnt_notfolded3 = tableInfo.player_num - cnt_folded3;
            if(player_action2[0] == 2) {
                gain[0] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1);
                gain[1] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + 1);
            }
            else if(player_action3[0] == 2) {
                gain[0] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + cnt_raised2);
                gain[1] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + 1 + cnt_raised2);
            }
            else {
                std::vector<int> notFolded;
                notFolded.clear();
                notFolded.push_back(0);
                bool win0;
                int cnt_winner = 0;
                for(int i = 1; i < tableInfo.player_num; i++)
                    if(!folded[i])
                        notFolded.push_back(i);
                for(int i : notFolded) {
                    std::vector<Card> firstvect = playerHand[i];
                    firstvect.insert(firstvect.end(), community.begin(), community.end());
                    PokerHand firstHand(firstvect);
                    bool win = true;
                    for(int j : notFolded) {
                        if(j == i)
                            continue;
                        std::vector<Card> secondvect = playerHand[j];
                        secondvect.insert(secondvect.end(), community.begin(), community.end());
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
                if(win0 == false) {
                    gain[0] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + cnt_raised2 + cnt_raised3);
                    gain[1] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + 1 + cnt_raised2 + cnt_raised3);
                }
                else {
                    gain[0] = (cnt_raised1 * cnt_notfolded1 + cnt_raised2 * cnt_notfolded2 + cnt_raised3 * cnt_notfolded3 + tableInfo.pot) / cnt_winner
                              - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue) - cnt_raised1 - cnt_raised2 - cnt_raised3;
                    gain[1] = ((cnt_raised1 + 1) * cnt_notfolded1 + cnt_raised2 * cnt_notfolded2 + cnt_raised3 * cnt_notfolded3 + tableInfo.pot) / cnt_winner
                              - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue) - cnt_raised1 - 1 - cnt_raised2 - cnt_raised3;
                }
            }
            int choice = get_cfr3(tableInfo.player_num - 2, player_handid[0], cardid1);
            for(int i = 0; i < 3; i++) {
                if(i == choice)
                    continue;
                cfr3[tableInfo.player_num - 2][player_handid[0]][cardid1][i] += (gain[i] - gain[choice]);
            }
        }
        int choice = get_cfr3(tableInfo.player_num - 2, player_handid[0], cardid1);
        if(choice == 0)
            call_bet();
        else if(choice == 1)
            raise_bet(tableInfo.BBValue);
        else
            fold_bet();
    }
    if(round == 4) {
        int card_num[5];
        for(int i = 0; i < 4; i++)
            card_num[i] = tableInfo.communityCards[i].getValue() - 2;
        std::sort(card_num, card_num + 4);
        int cardid = card_to_id4[card_num[0]][card_num[1]][card_num[2]][card_num[3]];
        for(int _ = 0; _ < iter_lim; _++) {
            if(abs(cfr4[tableInfo.player_num - 2][player_handid[0]][cardid][0]) > 500000000 ||
                abs(cfr4[tableInfo.player_num - 2][player_handid[0]][cardid][1]) > 500000000 ||
                abs(cfr4[tableInfo.player_num - 2][player_handid[0]][cardid][2]) > 500000000)
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
            std::vector<Card> community = tableInfo.communityCards;
            int value, suit;
            while(true) {
                int x = rand_int(0, 12);
                if(cnt_card[x] == 4)
                    continue;
                value = x;
                cnt_card[x]++;
                break;
            }
            while(true) {
                int s = rand_int(0, 3);
                if(card_suit[value][s])
                    continue;
                suit = s;
                card_suit[value][s] = true;
                break;
            }
            card_num[4] = value;
            community.push_back(Card((Suit) suit, value + 2));
            std::sort(card_num, card_num + 5);
            int cardid2 = card_to_id5[card_num[0]][card_num[1]][card_num[2]][card_num[3]][card_num[4]];
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
            int player_action1[8], player_action2[8];
            for(int i = 1; i < tableInfo.player_num; i++)
                player_action1[i] = get_cfr4(tableInfo.player_num - 2, player_handid[i], cardid);
            for(int i = 0; i < tableInfo.player_num; i++)
                player_action2[i] = get_cfr5(tableInfo.player_num - 2, player_handid[i], cardid2);
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(tableInfo.playerInfo[i].isFold)
                    folded[i] = true;
                if(player_action1[i] == 2)
                    folded[i] = true;
            }
            int gain[3];
            gain[2] = - int ((tableInfo.playerInfo[tableInfo.current_player].bet) / tableInfo.BBValue);
            int cnt_folded1 = 0, cnt_raised1 = 0;
            for(int i = 1; i < tableInfo.player_num; i++) {
                if(folded[i]) {
                    cnt_folded1++;
                    continue;
                }
                if(player_action1[i] == 1)
                    cnt_raised1++;
            }
            int cnt_notfolded1 = tableInfo.player_num - cnt_folded1;
            if(player_action2[0] == 2) {
                gain[0] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1);
                gain[1] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + 1);
            }
            else {
                for(int i = 0; i < tableInfo.player_num; i++) {
                    if(player_action2[i] == 2)
                        folded[i] = true;
                }
                int cnt_folded2 = 0, cnt_raised2 = 0;
                for(int i = 0; i < tableInfo.player_num; i++) {
                    if(folded[i]) {
                        cnt_folded2++;
                        continue;
                    }
                    if(player_action2[i] == 1)
                        cnt_raised2++;
                }
                int cnt_notfolded2 = tableInfo.player_num - cnt_folded2;
                std::vector<int> notFolded;
                notFolded.clear();
                notFolded.push_back(0);
                bool win0;
                int cnt_winner = 0;
                for(int i = 1; i < tableInfo.player_num; i++)
                    if(!folded[i])
                        notFolded.push_back(i);
                for(int i : notFolded) {
                    std::vector<Card> firstvect = playerHand[i];
                    firstvect.insert(firstvect.end(), community.begin(), community.end());
                    PokerHand firstHand(firstvect);
                    bool win = true;
                    for(int j : notFolded) {
                        if(j == i)
                            continue;
                        std::vector<Card> secondvect = playerHand[j];
                        secondvect.insert(secondvect.end(), community.begin(), community.end());
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
                if(win0 == false) {
                    gain[0] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + cnt_raised2);
                    gain[1] = - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue + cnt_raised1 + 1 + cnt_raised2);
                }
                else {
                    gain[0] = (cnt_raised1 * cnt_notfolded1 + cnt_raised2 * cnt_notfolded2 + tableInfo.pot / tableInfo.BBValue) / cnt_winner
                              - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue) - cnt_raised1 - cnt_raised2;
                    gain[1] = ((cnt_raised1 + 1) * cnt_notfolded1 + cnt_raised2 * cnt_notfolded2 + tableInfo.pot / tableInfo.BBValue) / cnt_winner
                              - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue) - cnt_raised1 - cnt_raised2 - 1;
                }
                int choice = get_cfr4(tableInfo.player_num - 2, player_handid[0], cardid);
                for(int i = 0; i < 3; i++) {
                    if(i == choice)
                        continue;
                    cfr4[tableInfo.player_num - 2][player_handid[0]][cardid][i] += (gain[i] - gain[choice]);
                }
            }
        }
        int choice = get_cfr4(tableInfo.player_num - 2, player_handid[0], cardid);
        if(choice == 0)
            call_bet();
        else if(choice == 1)
            raise_bet(tableInfo.BBValue);
        else
            fold_bet();
    }
    if(round == 5) {
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
                if(!folded[i])
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
                gain[0] = (cnt_raised * cnt_notfolded + tableInfo.pot / tableInfo.BBValue) / cnt_winner
                          - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue) - cnt_raised;
                gain[1] = ((cnt_raised + 1) * cnt_notfolded + tableInfo.pot / tableInfo.BBValue) / cnt_winner
                          - (tableInfo.playerInfo[tableInfo.current_player].bet / tableInfo.BBValue) - cnt_raised - 1;
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
