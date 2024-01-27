#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "analysis.hpp"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

// Add the missing constructor for the Hand class
Hand::Hand(std::string& player, std::string& street, std::string& action, double chips, double chips_start)
    : player(player), street(street), action(action), chips(chips), chips_start() {}

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
            street = "";
            action = "";
            continue;
        }

        else{
            
            if (line.find("*** HOLE CARDS ***") != std::string::npos){

                street = "Preflop";
                }
            if (line.find("*** FLOP ***") != std::string::npos){

                street = "Flop";
                }
            if (line.find("*** TURN ***") != std::string::npos){

                street = "Turn";
                }
            if (line.find("*** RIVER ***") != std::string::npos){

                street = "River";
                }
            

            if (line.find(player_name) != std::string::npos){

                if (line.find("folds") != std::string::npos){

                    action = "Fold";
                }
                if (line.find("calls") != std::string::npos){

                    action = "Call";
                }
                if (line.find("bets") != std::string::npos){

                    action = "Bet";
                }
                if (line.find("raises") != std::string::npos){

                    action = "Raise";
                }
            }
            else{
                action = "";
            }


            if (street != "" && action != ""){

                Hand hand = {player_name, street, action, 0, 0};
                player_hands.push_back(hand);
            }
        }
    
    }
    return player_hands;
}



std::vector<double> ReadMargins(std::string file_name, std::string player_name) {
    std::ifstream file(file_name);
    std::string line;
    std::vector<Hand> player_hands;
    std::string street;
    std::string action;
    std::vector<double> margins; //Vector to store margins
    double chips = 0.0;
    double chips_start = 0.0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            street = "";
            action = "";
            chips = 0.0;
            chips_start = 0.0;
            continue;
        
        } else {

            // Extract chip count
            if (line.find("Seat") != std::string::npos && line.find(player_name) != std::string::npos) {
            
                std::string chipsStartSubstring = " (";
                std::string chipsEndSubstring = " in chips)";

                // Find the position of the chips start substring
                size_t chipsStartPos = line.find(chipsStartSubstring);
        
                // If the chips start substring is found, proceed to extract the chip count
                if (chipsStartPos != std::string::npos) {
                // Adjust the start position to point to the character after the chips start substring
                chipsStartPos += chipsStartSubstring.length();
            
                // Find the position of the chips end substring
                size_t chipsEndPos = line.find(chipsEndSubstring, chipsStartPos);
            
                // If the chips end substring is found, extract the chip count substring
                if (chipsEndPos != std::string::npos) {
                    std::string chipsStr = line.substr(chipsStartPos, chipsEndPos - chipsStartPos);
                
                    // Convert the extracted chip count substring to an integer
                    chips_start = std::stod(chipsStr);

                    chips = chips_start;

                
                    // Print the result
                    //std::cout << "Chips at the start of the game of " << player_name << ": " << chips << std::endl;
            }
        } }

           
            //blind bets
           if (line.find("blind") != std::string::npos && line.find(player_name) != std::string::npos) {
               
               int i = line.length()-1;
            

               while(line[i] != ' ') {
                  i--;
               }

               if (i >= 0) {
                  std::string value = line.substr(i + 1);

                try {
                    double blindAmount = std::stod(value);
                    chips -=  blindAmount;
                    //std::cout << "Chips after blind bet: " << chips << std::endl;
                } catch (const std::invalid_argument& e) {
                // Silently skip the line or handle the error accordingly
                }
                }
            }

             //Money won
            if (line.find("collected") != std::string::npos && line.find(player_name) != std::string::npos) {
            
                std::string chipsStartSubstring = "collected ";
                std::string chipsEndSubstring = " from pot";

                // Find the position of the chips start substring
                size_t chipsStartPos = line.find(chipsStartSubstring);
        
                // If the chips start substring is found, proceed to extract the chip count
                if (chipsStartPos != std::string::npos) {
                // Adjust the start position to point to the character after the chips start substring
                chipsStartPos += chipsStartSubstring.length();
            
                // Find the position of the chips end substring
                size_t chipsEndPos = line.find(chipsEndSubstring, chipsStartPos);
            
                // If the chips end substring is found, extract the chip count substring
                if (chipsEndPos != std::string::npos) {
                    std::string chipsStr = line.substr(chipsStartPos, chipsEndPos - chipsStartPos);
                
                    // Convert the extracted chip count substring to an integer
                    double won = std::stod(chipsStr);
                    chips += won;
                
                    // Print the result
                    //std::cout << "Chips won: " << won << std::endl;
                    //std::cout << "Chips afer winning: " << chips << std::endl;

            }
        } }


            if (line.find("*** HOLE CARDS ***") != std::string::npos) {
                street = "Preflop";
            }
            if (line.find("*** FLOP ***") != std::string::npos) {
                street = "Flop";
            }
            if (line.find("*** TURN ***") != std::string::npos) {
                street = "Turn";
            }
            if (line.find("*** RIVER ***") != std::string::npos) {
                street = "River";
            }

            if (line.find("*** SUMMARY ***") != std::string::npos){
                double chips_end = chips;
                //std::cout << "Chips at the end of the game: " << chips << std::endl;
                double balance = chips_end - chips_start;
                margins.push_back(balance);

                //std::cout << "Margin: " << balance << std::endl;

                

            }

            if (line.find(player_name) != std::string::npos) {
                if (line.find("folds") != std::string::npos) {
                    action = "Fold";
                }
                if (line.find("calls") != std::string::npos) {
                    action = "Call";

                    int i = line.length()-1;
            

                    while(line[i] != ' ') {
                        i--;
                    }

                    if (i >= 0) {
                        std::string value = line.substr(i + 1);

                        try {
                            double blindAmount = std::stod(value);
                            chips -=  blindAmount;
                            //std::cout << "Chips after call: " << chips << std::endl;
                        } catch (const std::invalid_argument& e) {
                        // Silently skip the line or handle the error accordingly
                        }
                        }

                }
                if (line.find("bets") != std::string::npos) {
                    action = "Bet";

                    int i = line.length()-1;
            

                    while(line[i] != ' ') {
                        i--;
                    }

                    if (i >= 0) {
                        std::string value = line.substr(i + 1);

                        try {
                            double blindAmount = std::stod(value);
                            chips -=  blindAmount;
                            //std::cout << "Chips after bet: " << chips << std::endl;
                        } catch (const std::invalid_argument& e) {
                        // Silently skip the line or handle the error accordingly
                        }
                        }




                }
                if (line.find("raises") != std::string::npos) {
                    action = "Raise";
                    int i = line.length()-1;
            

                    while(line[i] != ' ') {
                        i--;
                    }

                    if (i >= 0) {
                        std::string value = line.substr(i + 1);

                        try {
                            double blindAmount = std::stod(value);
                            chips -=  blindAmount;
                            //std::cout << "Chips after raise: " << chips << std::endl;
                        } catch (const std::invalid_argument& e) {
                        // Silently skip the line or handle the error accordingly
                        }
                        }
                }


    
            } else {
                action = "";
            }

            if (street != "" && action != "") {
                Hand hand = {player_name, street, action, chips, chips_start};
                player_hands.push_back(hand);
            }
        }
    }
    return margins;
}



double calculate_af(const std::vector<Hand>& hand_history, const std::string& player_name) {
    int total_bets_raises = 0;
    int total_calls = 0;

    for (const auto& hand : hand_history) {
        if (hand.player == player_name) {
            if (hand.action == "Bet" || hand.action == "Raise") {
                total_bets_raises++;
            } else if (hand.action == "Call") {
                total_calls++;
            }
        }
    }

    double aggression_factor = (total_calls > 0) ? static_cast<double>(total_bets_raises) / total_calls : total_bets_raises;

    return aggression_factor;
}

double calculate_vpip_percentage(const std::vector<Hand>& hand_history, const std::string& player_name) {
    int total_hands = 0;
    int vpip_hands = 0;

    for (const Hand& hand : hand_history) {
        if (hand.player == player_name && hand.street == "preflop") {
            total_hands++;

            if (hand.action != "Fold") {
                vpip_hands++;
            }
        }
    }

    double vpip_percentage = (total_hands > 0) ? static_cast<double>(vpip_hands) / total_hands : 0.0;

    return vpip_percentage * 100.0; // Convert to percentage
}

double average_margin(const std::vector<double>& margins){
    // Initialize sum to zero
    double sum = 0.0;
    double mean = 0.0;

    // Iterate through the vector and accumulate the values
    for (const double& value : margins) {
        sum += value;
    }

    // Print the result
    std::cout << "Total Chips won or loss: " << sum << std::endl;

     // Calculate the mean
    if (!margins.empty()) {
        mean = sum / margins.size();
        std::cout << "Mean of chips: " << mean << std::endl;
    } else {
        std::cout << "Vector is empty. Cannot calculate the mean." << std::endl;
    }
}

int main() {

    // Sample data (replace this with your actual hand history data)
    std::string name_player = "arazua";
    std::string file_name = "PokerHands2.txt";

    // Print in a stylish way a header that says "Poker Analysis: (player_name)" for what player the analysis is done
    std::cout << "Poker Analysis: " << name_player << "\n" << std::endl;

    std::vector<Hand> hand_history = ReadPlayerHands(file_name, name_player);
    // Use ReadMargins
    std::vector<double> margins = ReadMargins(file_name, name_player);

    // Calculate the AF and VPIP percentage, and print the results
    double af = calculate_af(hand_history, "arazua");

    double vpip_percentage = calculate_vpip_percentage(hand_history, "arazua");

    std::cout << "AF: " << af << std::endl;
    std::cout << "VPIP percentage: " << vpip_percentage << std::endl;

    // Calculate the average margins and print them
    double average = average_margin(margins);

    std::vector<double> af_values;
    std::vector<double> hand_intervals;

    for (size_t i = 10; i <= hand_history.size(); i += 10) {
        std::vector<Hand> subset(hand_history.begin(), hand_history.begin() + i);
        af_values.push_back(calculate_af(subset, name_player));
        hand_intervals.push_back(static_cast<double>(i));
    }

    plt::plot(hand_intervals, af_values);
    plt::title("Aggression Factor Over Time");
    plt::xlabel("Hand Number");
    plt::ylabel("Aggression Factor");
    plt::show();

    std::vector<double> vpip_values;

    for (int i = 0; i < hand_history.size(); i += 10) {
        std::vector<Hand> subset(hand_history.begin(), hand_history.begin() + i);
        vpip_values.push_back(calculate_vpip_percentage(subset, name_player));
    }

    plt::plot(hand_intervals, vpip_values);
    plt::title("VPIP Percentage Over Time");
    plt::xlabel("Hand Number");
    plt::ylabel("VPIP Percentage");
    plt::show();


    std::vector<double> chip_balances;

    for (const auto& hand : hand_history) {
        chip_balances.push_back(hand.chips);
    }

    plt::plot(chip_balances);
    plt::title("Chip Balance Over Time");
    plt::xlabel("Hand Number");
    plt::ylabel("Chip Balance");
    plt::show();


    plt::plot(margins);
    plt::title("Win/Loss Margins Over Hands");
    plt::xlabel("Hand Number");
    plt::ylabel("Margin");
    plt::show();






    return 0;
}




