#ifndef POKER_SCRATCH_H
#define POKER_SCRATCH_H
#include <iostream>
#include <string>
#include <vector>

class Card {
public:
    Card(const std::string& suit, int value);
    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    std::string getSuit() const;
    int getValue() const;
    std::string toString() const; 

private:
    std::string suit; // 'H' is heart 'D' is diamond etc.
    int value;        // cards 1 - 13, 13 is king
};

class Deck {
public:
    Deck();
    void shuffleDeck();
    Card dealCard();

private:
    std::vector<Card> cards;
    int currentCardIndex;
};

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
//functions
    //initializing (new player created)
        //define chips available as int var

    //get_chips()
        //returns chips available
    //get_bet()
        //returns bet
    //get_cards()
        //returns cards
    //get_hand()
        //returns hand
    //is_small_blind()
        //return small_blind
    //is_big_blind()
        //return big_blind
    //is_still_playing()
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
    //find_best_hand(5 cards in middle)
        // if (royal flush) ...
        // else if (straight flush)...

        // else (high card)...
    //win(pot)
        // increase Chips available of player
public:
    Player(const std::string& name, int initialChips);
    const std::string& getName() const { return name; }
    int getChips() const;
    void placeBet(int amount);
    void receiveCards(const std::vector<Card>& cards);
    void showHand() const;
    void winChips(int amount);
    

private://attributes
    std::string name;
    int chips;
    std::vector<Card> hand; 

    
    //Two cards
    //Betting
    //Chips available
    //Best hand (five cards)
    //big_blind (boolean)
    //small_blind (boolean)
    //is_player_still_playing (boolean)


};

class Game_ { //the idea will be to integrate the functions turn() and round() to create a full game within the class
public:
    //intializing default
        //creates 6 Players and assigns small_blind and big_blind, pot = 0
    //intializing customizable (input starting pots of players)
        //creates 6 Players and assigns small_blind randomly and big_blind next to it, pot = 0



    Game_(int numOfPlayers);
    void startGame();

private:
    Deck deck;
    std::vector<Player> players;
    std::vector<Card> communityCards;

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
