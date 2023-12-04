#ifndef POKER_SCRATCH_H
#define POKER_SCRATCH_H

#include <vector>
#include <string>

//The idea of implementation is the following:
//There is a class Game that takes into account the proceeding of the game: succession of rounds, finding winners, distributing wins, etc.
//The class Player that makes player instances in the game: they have chips, they can play and eventually interact with user
//The class Deck is used to randomly pick integers between 1 and 52 which represent cards: much more focused and shallow than the other classes

//TO DO as of 30Nov2023:
//Implement find best hand function in Player class
//Add betting element in functions of the Game class (should be done in call, raise, fold, and end_round() functions)
//Implement the functions that say TO DO
//Start working on interaction with User: printing cards and asking the user if raise call or fold

class Deck {
public:
    //initializing, when new game created
    Deck();
        //define vector cards_distributed_already = NULL

    //get_cards(number of cards needed)
    std::vector<int> get_cards(int);
        //while enough different cards aren't picked
        //function random integer between 1 and 52
        //if integer in vector cards_distributed_already
        //we don't take the card and retry again
    //return vector with n integers randomly picked which represent cards

    //new_round()
    void new_round();
        //makes vector cards_distributed_already NULL again

private:
    std::vector<int> cards_already_given; //vector cards_distributed_already

};

class Player {
public: //functions
    //initializing (new player created)
    Player(int);
        //define chips available as int var

    //Section: Standard get functions
    int get_chips() {return chips_available;}
    int get_bet() {return current_bet;}
    std::vector<int> get_cards() {return two_cards;}
    //get_besthand() {return;} //TO BE COMPLETED WITH BESTHAND
    int is_small_blind() {return small_blind;}
    int is_big_blind() {return big_blind;}
    int stopped_playing() {return player_stopped_playing;}

    //Section: Actions at the start of the game
    void new_round();
        //makes current_bet = 0
        //makes player_stopped_playing false (he is playing now)
    void distribute_cards(std::vector<int>);
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

    int end();
        //function used to zero bet on table to use at end of every round
        //change value of player_stopped_playing to true
        //returns current bet to add to total pot

    //Section: Automatic actions in a round
    void make_bet_zero() { //makes the player's bet zero as we placed it in the pot
        current_bet = 0;
    }

    //Section: Actions at end of game
    //find_best_hand(5 cards in middle)
    // if (royal flush) ...
    // else if (straight flush)...

    // else (high card)...

    void win(pot) { //increase Chips available of player
        chips_available += pot;
    }


private: //attributes
    std::vector<int> two_cards; //two_cards
    int current_bet; //Betting
    int chips_available; //Chips available
    //Best hand (five cards)
    bool big_blind; // big_blind (boolean)
    bool small_blind; // small_blind (boolean)
    bool player_stopped_playing; //player_stopped_playing (boolean)


};

class Game { //the idea will be to integrate the functions turn() and round() to create a full game within the class
public:
    //intializing default
    Game();
        //creates 6 Players and assigns small_blind and big_blind, pot = 0
        //intializing customizable (input number of players and starting chips of players)
    Game(int, int);
        //inputs are: number of players, chips of each player
        //creates n Players and assigns small_blind randomly and big_blind next to it, pot = 0

    //game()
    void game();
        //while True loop that breaks when the app is closed
        //play round()
        //eventual treatment of losers: players with chips = 0
        //fuction option to quit

    //round()
    void round();
    //distribute cards to players
    //players_standing = 6 everyone plays variable useful to determine when everybody placed the same bet to proceed to flop,turn,river...
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

    void turn(Player);
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

    void round_of_betting(int);
        //while (players_standing != number_of_players_who_played)
        //if player is not playing, i.e. has folded
        //increase index_turn by 1
        //and skip to next iteration of while loop
    //if player is still playing, hasn't folded
    //player plays his turn (can raise, call, fold: check turn() function)
    //increase index_of_turn by 1
    //We finished the first round: either >=2 players called or 1 player won as everybody else folded
    //if 1 player won as everybody else folded
    //end_round() function
    //else if >=2 players called we put their bets in the pot
    //we go over the table and collect the bets
    //if player is not playing, i.e. has folded
    //skip to next iteration of while loop
    //else if player has called
    //Add bet to the pot
    //Remove bet from the player's hand

    void end_round();
    //if players_standing == 1 then player won by making rest of player fold
    //player standing gets pot with players[index_of_winner].win(pot)
    //we reset the pot variable to 0
    //else we arrive at the end of river and need to comapre cards
    //for all players left compute their best hand based on their two cards and 5 cards in middle
    //compare the best hands and determine the winner
    //player winner gets pot with players[index_of_winner].win(pot)
    //we reset the pot variable to 0
    //if a player has not chips left, we need to determine what to do

private:
    std::vector<Player> players; //vector with all Players in game
    Deck deck; //deck of cards in game
    std::vector<int> community_cards; //cards in the middle
    int total_pot; //pot variable
    int small_blind; //small_blind value: will be computed automatically as initial_chips/100
    int big_blind = 2*small_blind; //big_blind value: will be computed automatically 2*big_blind
    int total_number_players; //players at every start of the game (is never touched)

    //Following used to determine when to go to next stages of a round (turn, flop, river)
    int players_standing; //players_standing (if players_standing == 1 then round ends as 1 winner)
    int number_callers; //starts at 0 at the start of every raise, etc. check round() function
    int small_blind_index; //very useful to determine which player has small and big blind in any round
    int index_turn; //Will be used to just shift from one player to the other as Players are in a vector
    int bet_on_table; //Used to see if players have matched the bet required to call

};





#endif // POKER_SCRATCH_H
