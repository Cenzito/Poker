#ifndef POKER_SCRATCH_H
#define POKER_SCRATCH_H

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

//The idea of implementation is the following:
//There is a class Game that takes into account the proceeding of the game: succession of rounds, finding winners, distributing wins, etc.
//The class Player that makes player instances in the game: they have chips, they can play and eventually interact with user
//The class Deck is used to randomly pick integers between 1 and 52 which represent cards: much more focused and shallow than the other classes

//TO DO as of 30Nov2023:
//Implement find best hand function in Player class
//Add betting element in functions of the Game class (should be done in call, raise, fold, and end_round() functions)
//Implement the functions that say TO DO
//Start working on interaction with User: printing cards and asking the user if raise call or fold
enum Suit {
    spades = 2,
    clubs = 3,
    hearts = 5,
    diamonds = 7
};

class Card {
public:
    Card(Suit, int);
    Suit getSuit();
    int getValue();
private:
    Suit suit; //based on enum above
    int value; // cards 1 - 13, 13 is king
};

class Deck {
public:
    //initializing, when new game created
    Deck();
        //define vector cards

    //get_cards(number of cards needed)
    std::vector<Card> get_cards(int);

    //new_round()
    void new_round(); //makes vector index_of_card NULL again and shuffles deck

private:
    std::vector<Card> cards; //vector cards_distributed_already
    int index_of_card; //more efficient way to get a card than using pop

};

enum PokerHand {
    HighCard,
    //If no player has a pair or better, the hand with the highest card(s) wins.
    //If there is a tie, compare the next highest cards, and so on, until a winner is determined.
    OnePair,
    //The player with the higher pair wins.
    //If both players have the same pair, the one with the highest kicker (unpaired card) wins.
    //If the kickers are also the same, compare the next highest kicker, and so on.
    TwoPair,
    //The player with the highest pair of the two wins.
    //If there is a tie, compare the second pair.
    //If both pairs are the same, the player with the highest kicker wins.
    ThreeOfaKind,
    //The player with the higher three of a kind wins.
    //If there is a tie, compare the kickers.
    Straight,
    //The player with the highest top card in the straight wins.
    //If there is a tie, the pot is split.
    Flush,
    //The player with the highest card in the flush wins.
    //If there is a tie, compare the second highest, and so on, until a winner is determined.
    FullHouse,
    //The player with the higher three of a kind wins.
    //If there is a tie, compare the pair.
    FourOfaKind,
    //The player with the higher four of a kind wins.
    //If there is a tie, compare the kicker.
    StraightFlush,
    //Similar to a straight, the player with the highest top card in the straight flush wins.
    //If there is a tie, the pot is split.
    RoyalFlush
    //The highest possible hand. Ties are not possible.
};

class Player {
public: //functions
    //initializing (new player created)
    Player(int, int);

    //Section: Standard get functions
    int get_chips() {return chips_available;}
    int get_bet() {return current_bet;}
    int get_name() {return name;}
    PokerHand get_best_hand() {return best_hand;}
    std::vector<int> get_tiebreaker() {return tiebreaker;}
    int get_value(int cardN) {return two_cards[cardN].getValue();}
    Suit get_suit(int cardN) {return two_cards[cardN].getSuit();}
    //get_besthand() {return;} //TO BE COMPLETED WITH BESTHAND
    int is_small_blind() {return small_blind;}
    int is_big_blind() {return big_blind;}
    int stopped_playing() {return player_stopped_playing;}

    //Section: Actions at the start of the game
    void new_round();
        //makes current_bet = 0
        //makes player_stopped_playing false (he is playing now)
    void distribute_cards(std::vector<Card>);
        //defines vector two_cards to the two cards given
        //the randomness of the cards will be covered by Deck class
    void pay_blind(int);
        //makes player pay the small or big blind
        //decreases Chips available by blind
        //changes current_bet = blind

    //Section: Actions a player can make
    void call(int);
        //decreases Chips available by bet_on_table - current_bet
        //changes current_bet = bet_on_table

    int raise(int);
        //decreases Chips available by amount_to_raise
        //changes current_bet = amount_to_raise + current_bet
        //returns new total bet

    int fold();
        //function used to zero bet on table to use at end of every round
        //change value of player_stopped_playing to true
        //returns current bet to add to total pot

    //Section: Automatic actions in a round
    void make_bet_zero() { //makes the player's bet zero as we placed it in the pot
        current_bet = 0;
    }

    //Section: Actions at end of game
    //find_best_hand(5 cards in middle)
    void find_best_hand(std::vector<Card>);
    // if (royal flush) ...
    // else if (straight flush)...

    // else (high card)...

    void win(int pot) { //increase Chips available of player
        chips_available += pot;
    }


private: //attributes
    int name;
    std::vector<Card> two_cards; //two_cards
    int current_bet; //Betting
    int chips_available; //Chips available
    std::vector<int> tiebreaker; //cards used to determine winner or draw if two players have same hand
    PokerHand best_hand;
    bool big_blind; // big_blind (boolean)
    bool small_blind; // small_blind (boolean)
    bool player_stopped_playing; //player_stopped_playing (boolean)
};

class Game { //the idea will be to integrate the functions turn() and round() to create a full game within the class
public:
    //intializing default
    Game();
        //creates 6 Players and assigns small_blind and big_blind, pot = 0
    Game(int, int);
        //inputs are: number of players, chips of each player

    //game()
    void game();
        //while True loop that breaks when the app is closed
        //play round()
        //eventual treatment of losers: players with chips = 0
        //fuction option to quit

    //round()
    void round();

    void turn(int);
    //turn() turn in a round for a player

    int find_winning_hand(std::vector<int>);

    void round_of_betting(int);

    void end_round();

private:
    std::vector<Player> players; //vector with all Players in game
    Deck deck; //deck of cards in game
    std::vector<Card> community_cards; //cards in the middle
    int total_pot; //pot variable
    int small_blind; //small_blind value: will be computed automatically as initial_chips/100
    int big_blind; //big_blind value: will be computed automatically 2*big_blind
    int total_number_players; //players at every start of the game (is never touched)

    //Following used to determine when to go to next stages of a round (turn, flop, river)
    int players_standing; //players_standing (if players_standing == 1 then round ends as 1 winner)
    int number_callers; //starts at 0 at the start of every raise, etc. check round() function
    int small_blind_index; //very useful to determine which player has small and big blind in any round
    int index_turn; //Will be used to just shift from one player to the other as Players are in a vector
    int bet_on_table; //Used to see if players have matched the bet required to call

};





#endif // POKER_SCRATCH_H
