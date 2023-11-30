#ifndef POKER_SCRATCH_H
#define POKER_SCRATCH_H
#include <vector>
#include <string>
#include <algorithm>
class Cards {
};
enum class PokerCombinations {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};  //class listing all the possible combinations of poker hands, used to fully specify the best hand of a player 


class poker_scratch
{
public:
    poker_scratch();
};

class PlayerHand {//input player hand and cards in middle
public:
    //
    //
    //
    //function best hand
        // if (royal flush) ...
        // else if (straight flush)...

        // else (high card)...

private:
    //
    //variable hand

};

class Player {
public: //functions
    //initializing (new player created)
        //define chips available as int var
    Player(int chips_available, std::vector<Cards> cards, int small_blind, int big_blind, bool is_player_still_playing);
    int get_chips();
        //returns chips available
    int get_bet();
        //returns bet
    std::vector<Cards> get_cards();
        //returns cards, as a vector with two elements 
    //get_hand()
        //returns hand
    //is_small_blind()
        //return small_blind
    //is_big_blind()
        //return big_blind
    bool is_still_playing();
        //return is_player_still_playing

    //Section: Actions a player can make
    //call(bet on table = bet to match)
        //decreases Chips available by bet_on_table - current_bet
        //changes current_bet = bet_on_table

    //raise(bet on table = bet to match, amount to raise)
        //decreases Chips available by amount_to_raise
        //changes current_bet = amount_to_raise + current_bet

    //end()
        //function used to zero bet on table to use at end of every round
        //change value of is_player_still_playing to False

    //Section: Actions at end of game
   std::vector<Cards> find_best_hand(std::vector<Cards> cards_in_middle); 
        // if (royal flush) ...
        // else if (straight flush)...

        // else (high card)...
    //win(pot)
        // increase Chips available of player


private: //attributes
    std::vector<Cards> cards;//  a vector of two cards consisting of the player cards
    //Betting
    long chips; //the number of hips available
    std::vector<Cards> best_hand;//Best hand (five cards)
    int big_blind ;// the current amount of the big blind
    int small_blind ;// the current amount of the small blind
    bool is_player_still_playing ;//boolean, 1 if the player is still in the game, 0 otherwise


};

class Game_ { //the idea will be to integrate the functions turn() and round() to create a full game within the class
public:
    //intializing default
        //creates 6 Players and assigns small_blind and big_blind, pot = 0
    //intializing customizable (input starting pots of players)
        //creates 6 Players and assigns small_blind randomly and big_blind next to it, pot = 0


private:
    //Players
    //pot variable
    //small_blind value
    //big_blind value
    //players_standing (if players_standing == 1 then game ends)

};

//The following functions will be integrated in Game class

//round()
    //distribute cards to players
    //players_standing = 6 everyone plays variable useful to determine when everybody placed the same bet
    //number_of_players_who_played = 0 will be used to see if round ends when equal to players_standing

    //Round 1 - pre-flop
    //index_of_turn = position of player with small blind
    //while (players_standing != number_of_players_who_played)
        //find player at index_of_turn
        //check if player is still playing, i.e. hasn't folded
            //if not playing increase index_of_turn by 1
            //and skip to next iteration of while loop
        //turn() as we know player is playing
        //number_of_players_who_played += 1
        //index_of_turn += 1
    //if players_standing == 1
        //end round

    //Round 2 - flop (3 cards in middle)
    //add three random cards to board
    //the rest works the same as in Round 1

    //Round 3 - turn (adding 1 card in middle for 3 + 1 = 4 total)
    //add one random cards to board
    //the rest works the same as in Round 1

    //Round 4 - river (adding 1 card in middle for 4 + 1 = 5 total)
    //add one random cards to board
    //the rest works the same as in Round 1

    //End of 4 rounds:
    //for all players standing compute their best hands
    //determine best hand in case of draw split pot


//turn() turn in a round for a player,
    //show cards to player
    //show cards in middle of pot
    //show size_of_pot
    //show bet_to_match
    //Ask action
    //if call:
        //Player.call(bet_to_match)
    //
    //else if raise:
        //Ask raise amount !!!there are minimums
        //Player.raise(bet_to_match, amount_of_raise)
        //bet_on_table variable is updated to raise amount
        // !! A new round starts from here and ends at last unless new player re-raises
            //we do this with making number_of_players_who_played = 0 again
    //
    //else if fold:
        //pot = pot + bet_of_player
        //Player.end()
        //decrease players_standing by 1







#endif // POKER_SCRATCH_H
