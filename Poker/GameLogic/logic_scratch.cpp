#include "logic_scratch.h"

#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>

Card::Card(Suit suit, int value) : suit(suit), value(value) {} //Implemented

Suit Card::getSuit() { //Implemented
    return suit;
}

int Card::getValue() { //Implemented
    return value;
}

Deck::Deck() { //initializing, when new game created //Implemented
    for (int i=1;i<14;i++) { //for i between 1 and 13 (from ace to king)
        cards.push_back(Card(spades, i)); //create a card of each sign
        cards.push_back(Card(clubs, i));
        cards.push_back(Card(hearts, i));
        cards.push_back(Card(diamonds, i));
    }
}

//get_cards(number of cards needed)
std::vector<Card> Deck::get_cards(int number_cards_needed) { //Implemented
    std::vector<Card> cards_to_give;
    for (int i=0; i<number_cards_needed; i++) {
        cards_to_give.push_back(cards[index_of_card]);
        index_of_card += 1; //increase index_of_card to get next card in shuflled deck
    }
    return cards_to_give; //return vector with n integers randomly picked which represent cards
}

//new_round()
void Deck::new_round() { //Implemented
    std::random_device rd;
    std::mt19937 g(rd()); //shuffle deck using standard shuffle of vectors
    std::shuffle(cards.begin(), cards.end(), g);

    index_of_card = 0; //makes vector cards_distributed_already NULL again
}


Player::Player(int name_given, int chips) { //Implemented
    name = name_given; //name given
    chips_available = chips; //Chips available
}

void Player::new_round() { //Implemented
    //makes current_bet = 0
    current_bet = 0;
    //makes player_stopped_playing false (he is playing now)
    player_stopped_playing = false;
}

void Player::distribute_cards(std::vector<Card> distributed) { //Implemented
    //defines vector two_cards to the two cards given
    two_cards.assign(distributed.begin(), distributed.end());
    //the randomness of the cards will be covered by Deck clas
}

void Player::pay_blind(int blind) { //makes player pay the small or big blind //Implemented
    //decreases Chips available by blind
    chips_available -= blind;
    //changes current_bet = blind
    current_bet = blind;
}


void Player::call(int bet_on_table) {//TO BE DONE: manage the case where Not enough chips DO THIS IN OTHER Function
    //decreases Chips available by bet_on_table - current_bet
    chips_available -= (bet_on_table - current_bet);
    //changes current_bet = bet_on_table
    current_bet = bet_on_table;
}

int Player::raise(int bet_on_table) { //TO BE DONE
    //: Ask raise amount !!!there are minimums (check poker rules)
    std::string userInput;
    std::cout << "By how much woud you like to raise: ";
    //TO BE DONE: minimum based on small_blind and bet_on_table
    std::cin >> userInput;
    //minimum based on small_blind and bet_on_table
    int amount_to_raise = std::stoi(userInput);
    //CHECK IF amount_to_raise + current bet > bet on table + big blind or something
    chips_available -= amount_to_raise; //decreases Chips available by amount_to_raise
    current_bet += amount_to_raise; //changes current_bet = amount_to_raise + current_bet
    //returns current_bet + amount_to_raise = updated current bet
    return current_bet; //this returns allows us to redefine the general bet on the table
}

int Player::fold() {
    //change value of player_stopped_playing to true
    player_stopped_playing = true;
    //returns current bet to add to total pot
    int current_bet_2 = current_bet; //allows us to make current bet 0 while returning current_bet_2
    current_bet = 0;
    return current_bet_2;
}

void Player::find_best_hand(std::vector<Card> community_cards) {
    //Make a 7 card hand to compute best hand
    std::vector<Card> all_cards = community_cards;
    all_cards.assign(two_cards.begin(), two_cards.end());

    std::vector<int> values; //vector of all values: !! ACES are represented by 1 and 14 to get low and high straights
    long check_flush = 1; //Check flush with product of prime numbers
    bool is_flush = false;
    for (int i=0; i<7; i++) {
        check_flush *= all_cards[i].getSuit();
        if (all_cards[i].getValue() == 1) {
            values.push_back(1);
            values.push_back(14);
        }
        else {
            values.push_back(all_cards[i].getValue());
        }
    }

    //Checking flush and potentially straight/royal flush
    if (!(check_flush%32 && check_flush%243 && check_flush%3125 && check_flush%16807)) {
        is_flush = true;
        int suit_of_flush; //used to check if straight flush is achieved
        if (check_flush%32 == 0) { suit_of_flush = 2;}
        else if (check_flush%243 == 0) { suit_of_flush = 3;}
        else if (check_flush%3125 == 0) { suit_of_flush = 5;}
        else { suit_of_flush = 7;}

        std::vector<int> check_straight_flush;
        for (int i=0; i<7; i++) {
            if (all_cards[i].getSuit() == suit_of_flush) { //need to replace suit_of_flush with 2, 3, 5, or 7
                check_straight_flush.push_back(all_cards[i].getValue());
            }
        }
        std::sort(check_straight_flush.begin(), check_straight_flush.end()); //we have the 5 ordered cards forming flush
        bool is_straight_flush = false; //will be used in if statements
        int count_straight_flush = 1; //counts how many successive cards for straight
        int max_of_straight_flush = 0;
        for (std::size_t i = 0; i < check_straight_flush.size(); ++i) {
            if (check_straight_flush[i] == check_straight_flush[i-1] + 1) { //find straight flush
                count_straight_flush += 1;
                if (count_straight_flush >= 5) {
                    is_straight_flush = true;
                    max_of_straight_flush = check_straight_flush[i];
                }
                else {
                    count_straight_flush = 1;
                }
            }
        }

        //if we have a straight flush with highest 3 cards 14 (A) 13 (K) 12 (Q) then we're sure we have a royal flush
        if (is_straight_flush && max_of_straight_flush == 14) { //mathematical certainty to have royal flush
            best_hand = RoyalFlush;
            //we don't update tiebreaker as there is only one possible RoyalFlush per game
            return;
        }
        else if (is_straight_flush) { //if we have a straight flush
            best_hand = StraightFlush;
            tiebreaker.push_back(max_of_straight_flush); //we only push back the highest card value as sufficient to determine victory
            return;
        }
    }

    //Checking straight and counting pairs
    std::sort(values.begin(), values.end());
    bool is_straight = false; //will be used in if statements
    int pair_counter = 1; //will be multiplied by prime numbers: 2 = pair, 3 = trips, 5 = four of a kind

    int count_straight = 1; //counts how many successive cards for straight
    int count_pairs = 1;
    int value_best_pair, value_secondary_pair, value_best_trips, value_best_quads;
    for (int i=1; i<7; i++) {
        if (values[i] == values[i-1] + 1) { //find straights
            count_straight += 1;
            if (count_straight == 5) {
                is_straight = true;
            }
            else {
                count_straight = 1;
            }
        }

        else {
            count_straight = 1; //reinitializes count of straights
            if (values[i] == values[i-1]) { //find pairs, trips, etc.
                if (values[i] != 1) { //as we represented aces twice with 1 and 14 so will be counted after
                    count_pairs += 1;
                }
            }
            else {
                if (count_pairs == 1) { //no straight and no pairs
                    continue;
                }
                else if (count_pairs == 2) { //if we have pairs
                    pair_counter *= 2;
                    //if different than zero and we have a pair then we know we have 2 different pairs
                    value_secondary_pair = value_best_pair;
                    value_best_pair = values[i];
                }
                else if (count_pairs == 3) { //if we have 3 of a kind
                    pair_counter *= 3;
                    value_best_trips = values[i];
                }
                else { //if we have 4 of a kind
                    pair_counter *= 5;
                    value_best_quads = values[i];
                }
                count_pairs = 1; //we reinitialize count_pairs
            }
        }
    }

    if (pair_counter%5 == 0) {
        best_hand = FourOfaKind;
        tiebreaker.push_back(value_best_quads);
        //The player with the higher four of a kind wins.
        for (int i=1; i<8; i++) {
            if (values[7-i] != value_best_quads) {
                //If there is a tie, compare the, highest, kicker.
                tiebreaker.push_back(values[7-i]);
                break;
            }
        }
    }
    else if (pair_counter%3 == 0 && pair_counter%2 == 0) {
        best_hand = FullHouse;
        //The player with the higher three of a kind wins.
        tiebreaker.push_back(value_best_trips);
        //If there is a tie, compare the pair.
        tiebreaker.push_back(value_best_pair);
    }
    else if (is_flush) {
        best_hand = Flush;
        //The player with the highest card in the flush wins.
    //If there is a tie, compare the second highest, and so on, until a winner is determined.
    }
    else if (is_straight) {
        best_hand = Straight;
         //The player with the highest top card in the straight wins.
    //If there is a tie, the pot is split.
    }
    else if (pair_counter%3 == 0) {
        best_hand = ThreeOfaKind;
        //The player with the higher three of a kind wins.
        tiebreaker.push_back(value_best_trips);
        int j = 0;
        for (int i=1; i<8; i++) {
            if (values[7-i] != value_best_trips) {
                //If there is a tie, compare the, highest, kicker.
                tiebreaker.push_back(values[7-i]);
                j += 1;
                if (j == 2) {
                    break;
                }
            }
        }
    }
    else if (pair_counter%4 == 0) {
        best_hand = TwoPair;
        //The player with the highest pair of the two wins.
        tiebreaker.push_back(value_best_pair);
        //If there is a tie, compare the second pair.
        tiebreaker.push_back(value_secondary_pair);
        //If both pairs are the same, the player with the highest kicker wins.
        for (int i=1; i<8; i++) {
            if (values[7-i] != value_best_pair && values[7-i] != value_secondary_pair) {
                //If there is a tie, compare the, highest, kicker.
                tiebreaker.push_back(values[7-i]);
                break;
            }
        }
    }
    else if (pair_counter%2 == 0) {
        best_hand = OnePair;
        //The player with the higher pair wins.
        tiebreaker.push_back(value_best_pair);
        int j = 0;  //If both players have the same pair, the one with the highest kicker (unpaired card) wins.
        for (int i=1; i<8; i++) {
            if (values[7-i] != value_best_pair) {
                //If there is a tie, compare the, highest, kicker.
                tiebreaker.push_back(values[7-i]);
                j += 1;
                if (j == 3) {
                    break;
                }
            }
        }
    }
    else {
        best_hand = HighCard;
        tiebreaker.assign(values.rbegin(), values.rbegin() + 5);
        //If no player has a pair or better, the hand with the highest card(s) wins.
        //If there is a tie, compare the next highest cards, and so on, until a winner is determined.
    }
}

Game::Game() {
    for (int i = 0; i < 6; ++i) { //initializes vector of Player instances
        players.push_back(Player(i, 1000)); //6 players with 1000 chips at the start
    }
    deck = Deck(); //initialized a deck instance
    total_number_players = 6;
    small_blind_index = 0;
    small_blind = 10; //small_blind is chips/100 = 10
    big_blind = 2*small_blind;
    total_pot = 0; //intializes the pot to 0
}


Game::Game(int numOfPlayers, int chips_of_players) { //initializes vector of Player instances
    for (int i = 0; i < numOfPlayers; ++i) {
        players.push_back(Player(i, chips_of_players)); //numOfPlayers players with chips_of_players chips at the start
    }
    deck = Deck(); //initialized a deck instance
    total_number_players = numOfPlayers;
    small_blind_index = 0;
    small_blind = chips_of_players/100; //small_blind is chips/100
    big_blind = 2*small_blind;
    total_pot = 0; //intializes the pot to 0
}

enum Action { //will be used for implementation of turn()
    call,
    raise,
    fold
};

void Game::turn(int index_turn) { //turn() turn in a round for a player
    //std::cout << "Your cards: " << player.get_cards() << std::endl; //show cards of player
    //std::cout << "Cards in middle: " << community_cards << std::endl; //show cards in middle
    std::cout << "Player name: " << players[index_turn].get_name() << std::endl; //show name
    std::cout << "Player's bet: " << players[index_turn].get_bet() << std::endl; //show current bet
    std::cout << "Player's chips: " << players[index_turn].get_chips() << std::endl; //show chips
    std::cout << "Player's Card 1: " << players[index_turn].get_value(0) << players[index_turn].get_suit(0) << std::endl; //show card1
    std::cout << "Player's Card 2: " << players[index_turn].get_value(1) << players[index_turn].get_suit(1) << std::endl; //show card1
    std::cout << "Pot size: " << total_pot << std::endl; //show size_of_pot
    std::cout << "Bet to match: " << bet_on_table << std::endl; //show bet_to_match

    std::cout << "Player calling: " << number_callers << std::endl; //show bet_to_match
    std::cout << "Player standing: " << players_standing << std::endl; //show bet_to_match

    //Ask action
    //returns call, raise, or fold based on enum
    Action action;
    std::string userInput;
    std::cout << "Enter your action (call, raise, fold): ";
    std::cin >> userInput;
    if (userInput == "call") {
        action = call;
    } else if (userInput == "raise") {
        action = raise;
    } else if (userInput == "fold") {
        action = fold; //TO BE Done: If input is not that desired
    }

    if (action == call) {
        players[index_turn].call(bet_on_table);
        //We use player.call() function
        number_callers += 1;
        //We increase number_callers by 1
        std::cout << "Player called, his chips are: " << players[index_turn].get_bet() << std::endl; //show bet_to_match
    }
    else if (action == raise) {
        bet_on_table = players[index_turn].raise(bet_on_table);
        //bet_on_table variable is updated to raise amount
        // !! A new round starts from here and ends at last unless new player re-raises
        number_callers = 1;
            //we do this by making number_callers = 1 again
    }
    else if (action == fold) {
        //pot = pot + bet_of_player
        total_pot += players[index_turn].fold();
        //Player.fold() both makes player stop playing and returns his current bet to add to pot
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
            turn(index_turn); //player plays his turn (can raise, call, fold: check turn() function)
            index_turn = (index_turn + 1) % total_number_players; //increase index_of_turn by 1
        }
    }
    for (int i = 0; i < total_number_players; i++) {
            std::cout << "Player " << i << " current bet: " << players[i].get_bet() << std::endl;
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
        bet_on_table = 0;
    }
}

int Game::find_winning_hand(std::vector<int> indexes) {
    PokerHand best_hand = HighCard;
    std::vector<int> tiebreaker;
    int winner_index;
    for (int i : indexes) {
        players[i].find_best_hand(community_cards);
        if (players[i].get_best_hand() > best_hand) {
            best_hand = players[i].get_best_hand();
            tiebreaker = players[i].get_tiebreaker();
            winner_index = i;
        }
        else if (players[i].get_best_hand() < best_hand) {
            continue;
        }
        else {
            PokerHand playerhand = players[i].get_best_hand();
            if (playerhand == StraightFlush) {
                
            }
            else if (playerhand == FourOfaKind) {

            }
            else if (playerhand == FullHouse) {

            }
            else if (playerhand == Flush) {

            }
            else if (playerhand == Straight) {

            }
            else if (playerhand == ThreeOfaKind) {

            }
            else if (playerhand == TwoPair) {

            }
            else if (playerhand == OnePair) {

            }
            else {

            }
        }
    }
    return winner_index;
}

void Game::end_round() { //TO COMPLETE!
    //if players_standing == 1 then player won by making rest of player fold
    if (players_standing == 1) {
        //player standing gets pot with players[index_of_winner].win(pot)
        players[index_turn].win(total_pot);
    }
    else { //else we arrive at the end of river and need to comapre cards
        std::vector<int> indexes_callers;
        //for all players left compute their best hand based on their two cards and 5 cards in middle
        for (int i=0; i<total_number_players; i++) {
            if (players[i].stopped_playing()) { //if player stopped playing
                continue;
            }
            else { //if player is still playing, called until the end
                indexes_callers.push_back(i);
            }
        }
        //players[i].find_best_hand(community_cards);
        players[find_winning_hand(indexes_callers)].win(total_pot);
    }
    //we reset the pot variable to 0
    total_pot = 0;
    small_blind_index = (small_blind_index + 1) % total_number_players; //we shift the small blind (consequently big blind) by 1
    //TO BE DONE: if a player has not chips left, we need to determine what to do
}



void Game::round() {
    //Starting preparations:
    //Indexes for game development
    index_turn = 0; //Will be used to just shift from one player to the other as Players are in a vector
        //Cards
    deck.new_round(); //we cancel the memory of the cards already distributed to start redistributing
    community_cards.clear(); //No cards in the middle
        //Bets
    bet_on_table = 0; //We start with a zero bet on the table (small blinds are treated after)
        //Player counters
    players_standing = total_number_players; //useful to determine when everybody placed the same bet to proceed to flop,turn,river...
    number_callers = 0;
    //Important difference: players_standing counts the players who HAVEN'T FOLDED, hence if one folds players_standing -= 1
    //number_callers = players who CALLED. If a player raises, everybody needs to recall or fold => number_callers = 0

    //distribute cards to players
    std::vector<Card> two_cards; //will be used to tr ansfer cards from Deck to Player instances (for readability)
    for (int i=0; i<players_standing; i++) { //for loop
        two_cards = deck.get_cards(2); //two cards for each player: Texas Hold'em
        players[i].new_round(); //function to initialize variables of player at start of round (check class Player)
        players[i].distribute_cards(two_cards); //player receives cards
    }

    //Round 0 - make small blind and big blind play, bet_on_table = big blind
    players[small_blind_index].pay_blind(small_blind);
    players[(small_blind_index + 1) % total_number_players].pay_blind(big_blind);
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
