#include "Game.hpp"
#include <iostream>
#include <string>
#include <vector>


Game::Game(int numOfPlayers) {
    //This will need to be changed
    //Create a Game where people will join
    //for (int i = 0; i < numOfPlayers; ++i) {
    //    players.emplace_back("Player " + std::to_string(i + 1), 1000); //1000 cest les chips
    //}
    minimumRaise = 10;
    small_blind_index = 0;
}

int Game::getFreeSeat() {
    Table &t = tableInfo;
    for (int i = 0; i<t.seats; i++) {
        if (!(t.playerInfo.find(i) == t.playerInfo.end())) {
            return i;
        }
    }
    return -1;
}

void Game::JoinGame(PokerPlayer player) {

    //player joins game so we add him to the table
    //in future we will not just give money but search for the account of the player and add that much money
    //or do other stuff
    PlayerInfo playerinfo = PlayerInfo(player.getName(), 1000, 0);

    getFreeSeat();
    //would need to do a try in case of error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        return;
    } else {
        tableInfo.playerInfo.insert({getFreeSeat(), playerinfo});
        players.push_back(player);
    }
}




//to implement
void Game::nextHand(){
    for (PokerPlayer& player : players) {
        player.removeCards();
    }


    tableInfo.pot=0;
    tableInfo.smallBlindPlayer += 1;
    tableInfo.communityCards=std::vector<Card>();
}

//to implement
void Game::addBet(int pos, int amount){
    tableInfo.playerInfo.at(pos).stack_size -= amount;
    tableInfo.pot += amount;
}

//to implement
void Game::winMoney(int pos, int amount){
    tableInfo.playerInfo.at(pos).stack_size += amount;
}




void Game::addCard(Card card) {tableInfo.communityCards.push_back(card);}





void Game::pay(PokerPlayer player, int sum) {
    //remove sum amount of money from player
    //update table
    //send table to all players
}


void Game::win(PokerPlayer player, int sum) {
    //add sum amount of money to player
    //update table
    //send table to all players

}

//update the table information of every player in the game
//every time we have a change we will call that
//ui will need to be changed in each players
void Game::update() {
    for (PokerPlayer& player : players) {
        player.updateTable(tableInfo);
    }
}


enum Action { //will be used for implementation of turn()
    call,
    raise_,
    fold
};

void Game::turn(int index_turn, PokerPlayer player) { //turn() turn in a round for a player

    //ask player to bet
    //wait for response


    // all of this is kind of useless but can be used for bot testing

    //DEBUGGING IN CASE ONE WANTS TO SEE OUTPUT UNCOMMENT FOLLOWING (already uncommented)
    std::cout << "Player name: " << players[index_turn].getName() << std::endl; //show name
    //std::cout << "Player's bet: " << players[index_turn].get_bet() << std::endl; //show current bet
    //std::cout << "Player's chips: " << players[index_turn].get_chips() << std::endl; //show chips
    std::cout << "Pot size: " << tableInfo.pot << std::endl; //show size_of_pot
    std::cout << "Bet to match: " << bet_on_table << std::endl; //show bet_to_match
    std::cout << "Player calling: " << number_callers << std::endl; //show number of players calling
    std::cout << "Player standing: " << players_standing << std::endl; //show players standing

    //Ask action
    //returns call, raise, or fold based on enum
    Action action;
    std::string userInput;
    std::cout << "Enter your action (call, raise, fold): ";
    std::cin >> userInput;
    if (userInput == "call") {
        action = call;
    } else if (userInput == "raise") {
        action = raise_;
    } else if (userInput == "fold") {
        action = fold; //TO BE Done: If input is not that desired
    }

    if (action == call) {
        players[index_turn].call(bet_on_table);
        //We use player.call() function
        number_callers += 1;
        //We increase number_callers by 1
        //std::cout << "Player called, his chips are: " << players[index_turn].get_bet() << std::endl; //show bet_to_match
    }
    else if (action == raise_) {
        //bet_on_table = players[index_turn].raise(bet_on_table);
        //bet_on_table variable is updated to raise amount
        // !! A new round starts from here and ends at last unless new player re-raises
        number_callers = 1;
            //we do this by making number_callers = 1 again
    }
    else if (action == fold) {
        //pot = pot + bet_of_player
        //tableInfo.pot += players[index_turn].fold();
        //Player.fold() both makes player stop playing and returns his current bet to add to pot
        players_standing -= 1;
        //decrease players_standing by 1
    }
}

void Game::round_of_betting(int index_turn) {
    /*
    //while (players_standing != number_callers)
    while (players_standing != number_callers) {

        if (players[index_turn].stopped_playing()) { //if player is not playing, i.e. has folded
            index_turn = (index_turn + 1) % tableInfo.player_num; //increase index_turn by 1
            continue; //and skip to next iteration of while loop
        }

        else { //if player is still playing, hasn't folded
            turn(index_turn, players[index_turn]); //player plays his turn (can raise, call, fold: check turn() function)
            index_turn = (index_turn + 1) % tableInfo.player_num; //increase index_of_turn by 1
        }
    }
    //We finished the first round: either >=2 players called or 1 player won as everybody else folded
    if (players_standing == 1) { //if 1 player won as everybody else folded
        end_round();
        return;
    }
    else { //if >=2 players called we put their bets in the pot

        for (int i = 0; i<tableInfo.player_num; i++) { //we go over the table and collect the bets
            if (players[i].stopped_playing()) { //if player is not playing, i.e. has folded
                continue; //skip to next iteration of while loop
            }
            else {//if player has called
                tableInfo.pot += players[i].get_bet(); //Add bet to the pot
                players[i].make_bet_zero(); //Remove bet from the player's hand
            }
        }
        bet_on_table = 0;
    }*/
}

void Game::end_round() { //TO COMPLETE!
    /*
    //if players_standing == 1 then player won by making rest of player fold
    if (players_standing == 1) {
        //player standing gets pot with players[index_of_winner].win(pot)
        win(players[index_turn], tableInfo.pot);
    }
    else { //else we arrive at the end of river and need to comapre cards
        //for all players left compute their best hand based on their two cards and 5 cards in middle
        for (int i=0; i<tableInfo.player_num; i++) {
            if (players[i].stopped_playing()) { //if player stopped playing
                players[i].will_restart_playing(); //player isFold attribute false for new round
                continue;
            }
            else { //if player is still playing, called until the end
                //players[i].find_best_hand(community_cards); //defines best_hand variable of each standing player
                players[i].win(tableInfo.pot);
                break;
                //TO BE DONE: compare the best hands and determine the winner
                //TO BE DONE: player winner gets pot with players[index_of_winner].win(pot)
            }
        }

    }
    //we reset the pot variable to 0
    tableInfo.pot = 0;
    //TO BE DONE: if a player has not chips left, we need to determine what to do
*/
}


void Game::startGame() {
/*
//commented because of conflicts (delete and recreate pull request if this is unneccesary)
//void Game::startRound() {
    index_turn = 0; //Will be used to just shift from one player to the other as Players are in a vector
    small_blind_index = (small_blind_index + 1) % tableInfo.player_num; //we shift the small blind (consequently big blind) by 1
        //Bets
    bet_on_table = 0; //We start with a zero bet on the table (small blinds are treated after)
        //Player counters
    players_standing = tableInfo.player_num; //useful to determine when everybody placed the same bet to proceed to flop,turn,river...
    number_callers = 0;

    deck.shuffleDeck();

    // deal two random cards
    for (PokerPlayer& player : players) {
        std::vector<Card> hand = {deck.dealCard(), deck.dealCard()};
        player.receiveCards(hand);
        std::cout << player.getName() << "'s hand: ";
        player.getHand();
    }

    //Round 0 - make small blind and big blind play, bet_on_table = big blind
    players[small_blind_index].pay_blind(tableInfo.SBValue);
    players[(small_blind_index + 1) % tableInfo.player_num].pay_blind(tableInfo.BBValue);
    bet_on_table = tableInfo.BBValue;

    //Round 1 - pre-flop
    index_turn = (small_blind_index + 2) % total_number_players; //The player to the left of big blind is "under the gun": he starts
    //while (players_standing != number_callers)
    round_of_betting(index_turn);

    //Round 2 - flop
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "Flop: ";
    for (int i = 0; i < 3; ++i) {
        Card card = deck.dealCard();
        addCard(card);
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;
    //betting
    number_callers = 0; //we reinitialize the counter for number of CALLS
    //Notice we ended naturally at the player who raised last, hence index_turn is naturally correct, we start immediately
    round_of_betting(index_turn);

    //Round 3 - turn (adding 1 card in middle for 3 + 1 = 4 total)
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "Turn: ";
    Card turnCard = deck.dealCard();
    addCard(turnCard);
    std::cout << turnCard.toString() << std::endl;
    //betting
    number_callers = 0; //we reinitialize the counter for number of CALLS
    round_of_betting(index_turn);

    //Round 4 - river (adding 1 card in middle for 4 + 1 = 5 total)
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "River: ";
    Card riverCard = deck.dealCard();
    addCard(riverCard);
    std::cout << riverCard.toString() << std::endl;
    //betting
    number_callers = 0; //we reinitialize the counter for number of CALLS
    round_of_betting(index_turn);

    //End of 4 rounds:
    end_round(); //for all players standing compute their best hands and determine best hand check end_round() function
*/
}
