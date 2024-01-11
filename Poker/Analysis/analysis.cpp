#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "analysis.hpp"
#include <QApplication>

// Add the missing constructor for the Hand class
Hand::Hand(std::string& player, std::string& street, std::string& action)
    : player(player), street(street), action(action) {}

// Now I want to extract only the lines where the player is involved in the hand, and the action he took.
// I will use a class Hand, that will have the player name, the street and the action taken by the player.
// I will use a vector of Hand to store all the hands of the player.
// I will use a function to read the file and extract the hands of the player.

std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name){
    // Open the file
    std::ifstream file(file_name);
    std::string line;
    std::vector<Hand> player_hands;
    std::string street;
    std::string action;
    
    // Each play of the game is separated by 3 blank lines, separate each play of the game, then in each play we'll look for the street of the play, and then in each line after the street 
    // is declared we'll look for the player name, and if the player name is found, we'll look for the action he took.

    while (std::getline(file,line)){

        if (line.empty()){
            // Print "empty line"
            std::cout << "empty line" << std::endl;
            street = "";
            action = "";
            continue;
        }

        else{
            // Print "not empty line"
            std::cout << "not empty line" << std::endl;
            if (line.find("*** HOLE CARDS ***") != std::string::npos){
                // Print "Hole cards"
                std::cout << "Hole cards" << std::endl;
                street = "Preflop";
                }
            if (line.find("*** FLOP ***") != std::string::npos){
                // Print "Flop"
                std::cout << "Flop" << std::endl;
                street = "Flop";
                }
            if (line.find("*** TURN ***") != std::string::npos){
                // Print "Turn"
                std::cout << "Turn" << std::endl;
                street = "Turn";
                }
            if (line.find("*** RIVER ***") != std::string::npos){
                // Print "River"
                std::cout << "River" << std::endl;
                street = "River";

            if (line.find(player_name) != std::string::npos){
                if (line.find("folds") != std::string::npos){
                    // Print "Fold"
                    std::cout << "Fold" << std::endl;
                    action = "Fold";
                }
                if (line.find("calls") != std::string::npos){
                    // Print "Call"
                    std::cout << "Call" << std::endl;
                    action = "Call";
                }
                if (line.find("bets") != std::string::npos){
                    // Print "Bet"
                    std::cout << "Bet" << std::endl;
                    action = "Bet";
                }
                if (line.find("raises") != std::string::npos){
                    // Print "Raise"
                    std::cout << "Raise" << std::endl;
                    action = "Raise";
                }
            }
            // If we have a defined street , we can create a Hand and add it to the vector of hands.
            if (street != "" && action != ""){
                // Print "Hand created"
                std::cout << "Hand created" << std::endl;
                Hand hand = {player_name, street, action};
                player_hands.push_back(hand);
            }
        }
    
    }
    }
    return player_hands;
}


int Display_Hand_size() {
    // Sample data (replace this with your actual hand history data)
    std::vector<Hand> hand_history = ReadPlayerHands("PokerHands1.txt", "remi418");
    // Print size of hand history
    qDebug() << "Hand history size: " << hand_history.size();
    return 0;
}

