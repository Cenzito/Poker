#include "MonkeyBot.hpp"
#include <QApplication>
#include <random>

void MonkeyBot::Action(){
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range [0, 1)
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Generate a random number
    double random_number = dis(gen);
    qDebug()<<"random number is: "<< random_number;

    if (random_number<(1/3)){
        fold_bet();
    } else if (random_number<(2/3)) {
        call_bet();
    } else {
        double another_random_number = dis(gen);
        int bet = another_random_number*find_stack_size();
        raise_bet(bet);
    }
}
