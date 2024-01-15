// expected_money.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "expected_money.hpp"


Hand::Hand(std::string& player, std::string& street, std::string& action, double chips, double chips_start)
    : player(player), street(street), action(action), chips(chips), chips_start() {}

Hand::Hand() {}


std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name) {
    std::ifstream file(file_name);
    std::string line;
    std::vector<Hand> player_hands;
    std::string street;
    std::string action;
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
                    std::cout << "Chips at the start of the game of " << player_name << ": " << chips << std::endl;
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
                    std::cout << "Chips after blind bet: " << chips << std::endl;
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
                    std::cout << "Chips won: " << won << std::endl;
                    std::cout << "Chips afer winning: " << chips << std::endl;

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
                std::cout << "Chips at the end of the game: " << chips << std::endl;
                double balance = chips_end - chips_start;

                std::cout << "Margin: " << balance << std::endl;

                

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
                            std::cout << "Chips after call: " << chips << std::endl;
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
                            std::cout << "Chips after bet: " << chips << std::endl;
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
                            std::cout << "Chips after raise: " << chips << std::endl;
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
    return player_hands;
}

int main() {
    // Sample data (replace this with your actual hand history data)
    std::vector<Hand> hand_history = ReadPlayerHands("PokerHands1.txt", "remi418");
    // Print the hand history
    /*for (auto hand : hand_history) {
        std::cout << hand.player << " " << hand.street << " " << hand.action << std::endl;
    }
    return 0;*/


}