#include "BotLeal.hpp"
#include //mlpack headers


//"C:/Users/Leal Köksal/Documents/a University/Semester 3/CSE201/C++ Project/Poker/Poker/logistic_regression_1"

mlpack::regression::LogisticRegression<> lrModelRaise;
mlpack::regression::LogisticRegression<> lrModelFold;


void TrainRegressionRaise(const std::string& TrainingFile) {
    //first we load the data
    arma::mat TraningData;
    data.load(, arma::raw_ascii);

    arma::mat trainingData;  // Your training data matrix
    trainingData.load(trainingDataFile, arma::raw_ascii);

    //prepare the independent and dependent vars
    arma::mat features = data.cols(1, 2);
    arma::Row<int> labels = arma::conv_to<arma::Row<int>>::from(data.col(0, 3));

    /*data could now be split into training data and testing data. I will use all the data for training and use
    other inputs later to make predictions*/
    lrModelRaise = mlpack::regression::LogisticRegression<>(features, labels);

}

double predictionRaise(int betting_round, float winning_proba) {
    arma::rowvec testData(2);
    testData(0) = betting_round;
    testData(1) = winning_proba;

    arma::Row<double> probabilities; //used to store predicted probabilities
    lrModelRaise.PredictProbabilities(testData, probabilities);

    // The predicted probability of raising  --> class 1
    double raising_proba = probabilities(1);

    // Use probabilityOfRaising as needed
    return raising_proba;
}

void TrainRegressionFold(const std::string& TrainingFile) {
    //first we load the data
    arma::mat TraningData;
    data.load(, arma::raw_ascii);

    arma::mat trainingData;  // Your training data matrix
    trainingData.load(trainingDataFile, arma::raw_ascii);

    //prepare the independent and dependent vars
    arma::mat features = data.cols(1, 2);
    arma::Row<int> labels = arma::conv_to<arma::Row<int>>::from(data.col(0, 3));


    lrModelFold = mlpack::regression::LogisticRegression<>(features, labels);

}

double predictionFold(int betting_round, float winning_proba) {
    arma::rowvec testData(2);
    testData(0) = betting_round;
    testData(1) = winning_proba;

    arma::Row<double> probabilities;
    lrModelFold.PredictProbabilities(testData, probabilities);

    // The predicted probability of folding  --> class 1
    double fold_proba = probabilities(1);

    return fold_proba;
}

void BotLeal::Action() {
    std::string trainingDataFile1 = "C:/Users/Leal Köksal/Documents/a University/Semester 3/CSE201/C++ Project/Poker/Poker/logistic_regression_1";
    std::string trainingDataFile2 = "C:/Users/Leal Köksal/Documents/a University/Semester 3/CSE201/C++ Project/Poker/Poker/logistic_regression_2"; //add that file

    trainRegressionRaise(trainingDataFile1);
    TrainRegressionFold(trainingDataFile2);

    std::vector<Card> bot_hand = hand;
    for (int i = 0; i < tableInfo.communityCards.size(); i++) {
        bot_hand.emplace_back(tableInfo.communityCards[i]);
    }

    //Finally, we can make our prediction for raising
    double probabilityRaise = PredictionRaise(tableInfo.betting_round, Winning_Probability(tableInfo, bot_hand, tableInfo.player_num, 1000 )[0]);
    double probability Fold = PredictionFold(tableInfo.betting_round, Winning_Probability(tableInfo, bot_hand, tableInfo.player_num, 1000 )[0]);

    //make the actual decision...
}

