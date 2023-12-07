#ifndef GAME_HPP
#define GAME_HPP

#include "./PokerPlayer.hpp"
#include "Deck.hpp"
#include "table.hpp"
#include "PokerPlayer.hpp"
#include "PlayerInfo.hpp"
//#include "./Bots/Bot.hpp"
#include <string>
#include <vector>

class Game {
public:
    Game(int numOfPlayers);
    void JoinGame(PokerPlayer);
    void startRound();

    void addBot(PokerPlayer bot);

    //start a new hand
    void nextHand();


    void addBet(int pos, int amount);
    void winMoney(int pos, int amount);

    int getFreeSeat();

    void addCard(Card card);

    //Functions in a round
    void round_of_betting(int); //round of betting
    void turn(PokerPlayer);
    void end_round();

    void leaveGame(PokerPlayer);   
private:
    void update();
    Deck deck; //deck of cards in game
    Table tableInfo;
    std::vector<PokerPlayer> players; //vector with all Players in game
    //Variables covered by Table
    //std::vector<Card> communityCards; cards in the middle
    //int pot; pot variable
    //int SBValue; small_blind value: will be computed automatically as initial_chips/100
    //int BBValue; big blind value: will be computed automatically 2*big_blind
    //int player_num; //total number of players at every start of the game (is never touched)

    //Following used to determine when to go to next stages of a round (turn, flop, river)
    int players_standing; //players_standing (if players_standing == 1 then round ends as 1 winner)
    int number_callers; //starts at 0 at the start of every raise, etc. check round() function
    int small_blind_index; //very useful to determine which player has small and big blind in any round
    int index_turn; //Will be used to just shift from one player to the other as Players are in a vector
    int bet_on_table; //Used to see if players have matched the bet required to call

};


#endif // GAME_HPP
