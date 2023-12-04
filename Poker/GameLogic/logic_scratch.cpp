#include "logic_scratch.hpp"

#include <vector>
#include <string>

Deck::Deck() { //initializing, when new game created
    cards_already_given = NULL; //define vector cards_distributed_already = NULL
}

//get_cards(number of cards needed)
std::vector<int> Deck::get_cards(int number_cards_needed) {
    std::vector<int> cards = NULL;
    int new_card;

    //while enough different cards aren't picked
    while (std::vector::size(cards) < number_cards_needed) {

        //function random integer between 1 and 52
        new_card = std::rand() % 52 + 1;

        //if integer is not in vector cards_distributed_already
        if (std::find(cards_already_given.begin(), cards_already_given.end(), new_card) == cards_already_given.end()) {
            //we take the card and remember we already picked it by adding it to cards_already_given too
            cards.push_back(new_card); //we take the card
            cards_already_given.push_back(new_card); //we remember we already picked it
        }
        else { //if integer in vector cards_distributed_already
            ; //we don't take the card and retry again by doing another iteration of while loop
        }
    }
    return cards; //return vector with n integers randomly picked which represent cards
}

//new_round()
void Deck::new_round() {
    cards_already_given = NULL; //makes vector cards_distributed_already NULL again
}


Player::Player(int chips) {
    chips_available = chips; //Chips available
}
void Player::new_round() {
    //makes current_bet = 0
    current_bet = 0;
    //makes player_stopped_playing false (he is playing now)
    player_stopped_playing = false;
}

void Player::distribute_cards(std::vector<int> distributed) {
    //defines vector two_cards to the two cards given
    two_cards.assign(distributed.begin(), distributed.end());
    //the randomness of the cards will be covered by Deck class
}

void Player::call(int bet_on_table) {//TO BE DONE: manage the case where Not enough chips DO THIS IN OTHER Function
    //decreases Chips available by bet_on_table - current_bet
    chips_available -= (bet_on_table - current_bet);
    //changes current_bet = bet_on_table
    current_bet = bet_on_table;
}

int Player::raise(int bet_on_table) { //TO BE DONE
    //TO BE DONE: Ask raise amount !!!there are minimums (check poker rules)
    //minimum based on small_blind and bet_on_table
    //decreases Chips available by amount_to_raise
    //changes current_bet = amount_to_raise + current_bet
    //returns current_bet + amount_to_raise
    return bet_on_table;
}

int Player::end() {
    //change value of player_stopped_playing to true
    is_player_still_playing = true;
    //returns current bet to add to total pot
    return current_bet;
}


Game::Game() {
    for (int i = 0; i < 6; ++i) { //initializes vector of Player instances
        players.push_back(Player(1000)); //6 players with 1000 chips at the start
    }
    deck = Deck(); //initialized a deck instance
    total_number_players = 6;
    small_blind = 10; //small_blind is chips/100 = 10
    total_pot = 0; //intializes the pot to 0
}


Game::Game(int numOfPlayers, int chips_of_players) { //initializes vector of Player instances
    for (int i = 0; i < numOfPlayers; ++i) {
        players.push_back(Player(chips_of_players)); //numOfPlayers players with chips_of_players chips at the start
    }
    deck = Deck(); //initialized a deck instance
    total_number_players = numOfPlayers;
    small_blind = chips_of_players/100; //small_blind is chips/100
    total_pot = 0; //intializes the pot to 0
}


void Game::turn(Player player) { //turn() turn in a round for a player //TO COMPLETE
    //TO BE DONE: show cards to player
    //TO BE DONE: show cards in middle of pot
    //TO BE DONE: show size_of_pot
    //TO BE DONE: show bet_to_match

    string action;
    //TO BE DONE: Ask action
    //returns call, raise, or fold

    if (action == "call") {
        player.call(bet_on_table);
        //We use player.call() function
        number_callers += 1;
        //We increase number_callers by 1
    }

    else if (action == "raise") {
        bet_on_table = player.raise(bet_on_table);
        //bet_on_table variable is updated to raise amount
        // !! A new round starts from here and ends at last unless new player re-raises
        number_callers = 1;
            //we do this by making number_callers = 1 again
    }
    else if (action == "fold") {
        //pot = pot + bet_of_player
        total_pot += player.end();
        //Player.end() both makes player stop playing and returns his current bet to add to pot
        players_standing -= 1;
        //decrease players_standing by 1
    }
}


void Game::round_of_betting(int index_turn) {
    //while (players_standing != number_callers)
    while (players_standing != number_callers) {

        if (players[index_turn].stopped_playing()) { //if player is not playing, i.e. has folded
            index_turn = (index_turn + 1) % total_number_players; //increase index_turn by 1
            continue; //and skip to next iteration of while loop
        }

        else { //if player is still playing, hasn't folded
            turn(players[index_turn]); //player plays his turn (can raise, call, fold: check turn() function)
            index_turn = (index_turn + 1) % total_number_players; //increase index_of_turn by 1
        }
    }
    //We finished the first round: either >=2 players called or 1 player won as everybody else folded
    if (players_standing == 1) { //if 1 player won as everybody else folded
        end_round();
        return;
    }
    else { //if >=2 players called we put their bets in the pot
        for (int i = 0; i<total_number_players; i++) { //we go over the table and collect the bets
            if (players[i].stopped_playing()) { //if player is not playing, i.e. has folded
                continue; //skip to next iteration of while loop
            }
            else {//if player has called
                total_pot += players[i].get_bet(); //Add bet to the pot
                players[i].make_bet_zero(); //Remove bet from the player's hand
            }
        }
    }
}

void Game::end_round() { //TO COMPLETE!
    //if players_standing == 1 then player won by making rest of player fold
    if (players_standing == 1) {
        //player standing gets pot with players[index_of_winner].win(pot)
        players[index_turn].win(total_pot);
    }
    else { //else we arrive at the end of river and need to comapre cards
        //for all players left compute their best hand based on their two cards and 5 cards in middle
        for (int i=0; i<total_number_players; i++) {
            if (players[i].player_stopped_playing()) { //if player stopped playing
                continue;
            }
            else { //if player is still playing, called until the end
                players[i].find_best_hand(community_cards); //defines best_hand variable of each standing player
                //TO BE DONE: compare the best hands and determine the winner
                //TO BE DONE: player winner gets pot with players[index_of_winner].win(pot)
            }
        }

    }
    //we reset the pot variable to 0
    total_pot = 0;
    //TO BE DONE: if a player has not chips left, we need to determine what to do
}



void Game::round() {
    //Starting preparations:
    //Indexes for game development
    index_turn = 0; //Will be used to just shift from one player to the other as Players are in a vector
    small_blind_index = (small_blind_index + 1) % total_number_players; //we shift the small blind (consequently big blind) by 1
        //Cards
    deck.new_round(); //we cancel the memory of the cards already distributed to start redistributing
    community_cards = NULL; //No cards in the middle
        //Bets
    bet_on_table = 0; //We start with a zero bet on the table (small blinds are treated after)
        //Player counters
    players_standing = total_number_players; //useful to determine when everybody placed the same bet to proceed to flop,turn,river...
    number_callers = 0;
    //Important difference: players_standing counts the players who HAVEN'T FOLDED, hence if one folds players_standing -= 1
    //number_callers = players who CALLED. If a player raises, everybody needs to recall or fold => number_callers = 0

    //distribute cards to players
    std::vector<int> two_cards; //will be used to tr ansfer cards from Deck to Player instances (for readability)
    for (int i=0; i<players_standing; i++) { //for loop
        two_cards = deck.get_cards(2); //two cards for each player: Texas Hold'em
        players[i].new_round(); //function to initialize variables of player at start of round (check class Player)
        players[i].distribute_cards(two_cards); //player receives cards
    }

    //Round 0 - make small blind and big blind play, bet_on_table = big blind
    players[small_blind_index].pay_blind(small_blind);
    players[small_blind_index + 1].pay_blind(big_blind);
    bet_on_table = big_blind;

    //Round 1 - pre-flop
    index_turn = (small_blind_index + 2) % total_number_players; //The player to the left of big blind is "under the gun": he starts
    //while (players_standing != number_callers)
    round_of_betting(index_turn);

    //Round 2 - flop
    community_cards = deck.get_cards(3); //three cards in the middle
    number_callers = 0; //we reinitialize the counter for number of CALLS
    //Notice we ended naturally at the player who raised last, hence index_turn is naturally correct, we start immediately
    round_of_betting(index_turn);

    //Round 3 - turn (adding 1 card in middle for 3 + 1 = 4 total)
    community_cards.push_back(deck.get_cards(1).front()); //one card extra
    number_callers = 0; //we reinitialize the counter for number of CALLS
    round_of_betting(index_turn);

    //Round 4 - river (adding 1 card in middle for 4 + 1 = 5 total)
    community_cards.push_back(deck.get_cards(1).front()); //one card extra
    number_callers = 0; //we reinitialize the counter for number of CALLS
    round_of_betting(index_turn);

    //End of 4 rounds:
    end_round(); //for all players standing compute their best hands and determine best hand check end_round() function
}

