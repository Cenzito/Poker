#include "Game.hpp"
#include <iostream>
#include <string>
#include <vector>

Game::Game(int numOfPlayers) {
    //This will need to be changed
    //Create a Game where people will join
    for (int i = 0; i < numOfPlayers; ++i) {
        players.emplace_back("Player " + std::to_string(i + 1), 1000); //1000 cest les chips
    }
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


void Game::addBot(PokerPlayer bot) {
    Game::JoinGame(bot);
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

void Game::end_round() { //TO COMPLETE!
    //if players_standing == 1 then player won by making rest of player fold
    if (players_standing == 1) {
        //player standing gets pot with players[index_of_winner].win(pot)
        players[index_turn].win(tableInfo.pot);
    }
    else { //else we arrive at the end of river and need to comapre cards
        //for all players left compute their best hand based on their two cards and 5 cards in middle
        for (int i=0; i<tableInfo.player_num; i++) {
            if (players[i].stopped_playing()) { //if player stopped playing
                continue;
            }
            else { //if player is still playing, called until the end
                //players[i].find_best_hand(community_cards); //defines best_hand variable of each standing player

                //TO BE CHANGED: Waiting for the find best hand function we arbitrarily make the first player win
                players[i].win(tableInfo.pot);
                break;

                //TO BE DONE: compare the best hands and determine the winner
                //TO BE DONE: player winner gets pot with players[index_of_winner].win(pot)
            }
        }

    }
    //we reset the pot variable to 0
    tableInfo.pot = 0;
    //TO BE DONE: if a player has no chips left, we need to determine what to do
}


enum Action { //will be used for implementation of turn()
    call,
    raise,
    fold
};

void Game::turn(PokerPlayer player) { //turn() turn in a round for a player //TO COMPLETE
    player.getHand(); //show cards to player
    std::cout << "Pot size: " << tableInfo.pot << std::endl; //show size_of_pot
    std::cout << "Bet to match: " << bet_on_table << std::endl; //show bet_to_match

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
        player.call(bet_on_table);
        //We use player.call() function
        number_callers += 1;
        //We increase number_callers by 1
    }

    else if (action == raise) {
        bet_on_table = player.raise(bet_on_table);
        //bet_on_table variable is updated to raise amount
        // !! A new round starts from here and ends at player next to this player unless new player re-raises
        number_callers = 1;
            //we do this by making number_callers = 1 again
    }
    else if (action == fold) {
        //pot = pot + bet_of_player
        tableInfo.pot += player.fold();
        //Player.end() both makes player stop playing and returns his current bet to add to pot
        players_standing -= 1;
        //decrease players_standing by 1
    }
}


void Game::round_of_betting(int index_turn) {
    //while the players_standing are different from the number of callers
    while (players_standing != number_callers) {

        if (players[index_turn].stopped_playing()) { //if player is not playing, i.e. has folded
            index_turn = (index_turn + 1) % tableInfo.player_num; //increase index_turn by 1
            continue; //and skip to next iteration of while loop
        }

        else { //if player is still playing, hasn't folded
            turn(players[index_turn]); //player plays his turn (can raise, call, fold: check turn() function)
            index_turn = (index_turn + 1) % tableInfo.player_num; //increase index_of_turn by 1
        }
    }
    //We finished the first round: either >=2 players called or 1 player won as everybody else folded
    //Note that index_turn is perfect where it is
    if (players_standing == 1) { //if 1 player won as everybody else folded
        end_round();
        return;
    }
    else { //if >=2 players called we put their bets in the pot
        for (int i = 0; i<tableInfo.player_num; i++) { //we go over the table and collect the bets
            if (players[i].stopped_playing()) { //if player is not playing, i.e. has folded
                continue; //skip to next iteration of while loop as his bets are already in pot
            }
            else {//if player has called
                tableInfo.pot += players[i].bet_in_pot(); //Add bet to the pot and make current_bet 0
            }
        }
    }
}




//update the table information of every player in the game
//every time we have a change we will call that
//ui will need to be changed in each players
void Game::update() {
    for (PokerPlayer& player : players) {
        player.updateTable(tableInfo);
    }
}


void Game::startRound() {
    deck.shuffleDeck();
    //Starting preparations:
    //Indexes for game development
    index_turn = 0; //Will be used to just shift from one player to the other as Players are in a vector
    small_blind_index = (small_blind_index + 1) % tableInfo.player_num; //we shift the small blind (consequently big blind) by 1
        //Cards
    tableInfo.communityCards.clear(); //No cards in the middle
        //Bets
    bet_on_table = 0; //We start with a zero bet on the table (small blinds are treated after)
        //Player counters
    players_standing = tableInfo.player_num; //useful to determine when everybody placed the same bet to proceed to flop,turn,river...
    number_callers = 0;
    //Important difference: players_standing counts the players who HAVEN'T FOLDED, hence if one folds players_standing -= 1
    //number_callers = players who CALLED. If a player raises, everybody needs to recall or fold => number_callers = 0

    //Implement small and big blind
    players[small_blind_index].pay_blind(tableInfo.SBValue);
    players[(small_blind_index + 1) % tableInfo.player_num].pay_blind(tableInfo.BBValue);
    bet_on_table = tableInfo.BBValue;
    index_turn = small_blind_index = (small_blind_index + 2) % tableInfo.player_num; //person to right of bb starts "under the gun"

    // deal two random cards
    for (PokerPlayer& player : players) {
        std::vector<Card> hand = {deck.dealCard(), deck.dealCard()};
        player.receiveCards(hand);
        std::cout << player.getName() << "'s hand: ";
        player.getHand();
    }
    // preFlop
    // bet
    round_of_betting(index_turn);

    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;

    // Flop
    std::cout << "Flop: ";
    for (int i = 0; i < 3; ++i) {
        Card card = deck.dealCard();
        addCard(card);
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;


    // bet
    round_of_betting(index_turn);

    // burn and card
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "Turn: ";
    Card turnCard = deck.dealCard();
    addCard(turnCard);
    std::cout << turnCard.toString() << std::endl;

    // bet
    round_of_betting(index_turn);

    // river
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "River: ";
    Card riverCard = deck.dealCard();
    addCard(riverCard);
    std::cout << riverCard.toString() << std::endl;

    //betting
    round_of_betting(index_turn);

    //if end_round() hasn't been called yet then 2 or more players called until the end: card revelation
    end_round();
}
