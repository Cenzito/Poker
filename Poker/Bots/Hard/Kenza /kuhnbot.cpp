#include "kuhnbot.h"
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <map>
#include <sstream>


void Kuhnbot::loadStrategy() {
    std::ifstream file("KuhnPokerStrategy.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(':') == std::string::npos) continue;
            std::stringstream ss(line);
            std::string key, pass;
            double passVal;
            getline(ss, key, ':');
            ss >> pass >> passVal;
            strategy[key] = passVal;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

std::string Kuhnbot::decideAction() {
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    // Decide the next action based on the given card, the game history and probabilities that have been computed by the cfr training
    double rand = dis(gen); // Generate a random number
    // Treats each one of the cases

    if (card == "Jack") {
        if (history == "") {       // The bot has a Jack and it's the first round.
            if (rand < strategy["1"]){
                history += "p" ;   //Update History
                return "Pass" ;
            } else {
                history += "b" ;
                return "Bet";
            }
        }
        else if (history == "b") {   // The bot has a Jack and the opponent bet.
            history = "" ;           //The round ends: if the bot passes the opponent wins, else Showdownn: The highest card wins
            return rand < strategy["1b"] ? "Pass" : "Bet";
        }
        else if (history == "p") {     // The bot has a Jack and the opponent passed.
            if (rand < strategy["1p"]){
                history = "" ;     //  The round ends: Showdownn, The highest card wins
                return "Pass" ;
            } else {
                history += "b" ;
                return "Bet";
            }
        }
        else if (history == "pb") {       // The bot has a Jack and passed, then the opponent bet.
            history = "" ;               //  The round ends: if the bot passes the opponent wins, else Showdownn: The highest card wins
            return rand < strategy["1pb"] ? "Pass" : "Bet";
        }

    }else if (card == "Queen") {
        if (history == "") {                // The bot has a Queen and it's the first round.
            if (rand < strategy["2"] ){
                history += "p" ;
                return "Pass" ;
            } else {
                history += "b" ;
                return "Bet";
            }
        }
        else if (history == "b") {           // The bot has a Queen and the opponent bet.
            history = "" ;
            return rand < strategy["2b"] ? "Pass" : "Bet";
        }
        else if (history == "p") {          // The bot has a Queen and the opponent passed.
            if (rand < strategy["2p"]){
                history = "" ;
                return "Pass" ;
            } else {
                history += "b" ;
                return "Bet";
            }
        }
        else if (history == "pb") {         // The bot has a Queen and and passed, then the opponent bet.
            history = "" ;
            return rand < strategy["2pb"] ? "Pass" : "Bet";
        }

    } else if (card == "King") {
        if (history == "") {          // The bot has a King and it's the first round.
            if (rand < strategy["3"]){
                history += "p" ;
                return "Pass" ;
            } else {
                history += "b" ;
                return "Bet";
            }
        }
        else if (history == "b") {       // The bot has a King and the opponent bet.
            history = "" ;
            return rand < strategy["3b"] ? "Pass" : "Bet";
        }
        else if (history == "p") {        // The bot has a King and the opponent passed.
            if (rand < strategy["3p"] ){
                history = "" ;
                return "Pass" ;
            } else {
                history += "b" ;
                return "Bet";
            }
        }
        else if (history == "pb") {        // The bot has a King and passed, then the opponent bet.
            history = "" ;
            return rand < strategy["3pb"] ? "Pass" : "Bet";
        }

    }
    return "Pass"; // Default action
}
