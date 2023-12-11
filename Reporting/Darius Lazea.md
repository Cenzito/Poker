Week 1  (20/11 -26/11)
Learning to merge a branch
Researched an option to implement a bot, using Monte-Carlo simulations to find an approximate of the winning rate, then making an optimal bet using Kelly's criterion having that approximate winning rate. Quite a solid play, but it does not take into account other players behaviour.

Week 2 (27/11 - 4/12)
 Added implementations for basic functionalities of the player class (in the logic branch). Commented code, added a file for documenting how we implement some aspects of the project (data attributes used, so that other people can start working on their part).
 Commented some code, rewrote the suit attribute of the Card class (to make everything more readable and easier to work with).
 Reimplemented some of the functions of the card class using this new attribute, integrated the changes on the Deck class. Added code lines for testing our methods in the main.cpp
 Had quite an adventure making the code run on VS code.

 Week 3 (5/12- 11/12)
 Created and implemented the PokerHand class. A PokerHand is just an object containing a vector of cards, and then implemented some member functions to it. Some of them were helping functions in implementing the characteristic functions that check if any specific poker combination can be formed using the cards in the hand. All of these culminated with the compute_score function, that creates a score for each hand, scoring the best poker combination that is contained in the hand as well as numerical score for all kickers to settle draws. The function compare_hands has the ultimate goal, it takes two hands and determines the winner (or determines if we have a draw) and will be used to playing the game. Created lots of test cases in main.cpp and some random hands, getting good results. Also, added lots of comments and tried to make everything as readable as possible.