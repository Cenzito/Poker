#WEEK_1

I tried to formalise the intuitional brut force method for poker in order to optimise it. 
Def probability_of_my_hand_winning(cardA, cardB, n_players):
N = number of possibilities
M = 0                   //number of wins
Iterate N times:
      Me : cardA , cardB            // stays the same
	    For player in range(n_players):
			deal 2 cards 
      Board: 5 cards              //Preflop, you can change this detail depending on the stage of the game
      Simulate the game
      if I win: M+=1
P = M / N                    // Probability of winning with this hand
Return  P

It follows that if P > 0.5 , the bot calls, else it folds.


#WEEK_2

After formalising the brut force method, I tried to find ways to optimise it. However, the number of possibilities (N) is considerably big and would need a long time and a lot of memory. 
Even if the bot doesn’t do the computations each time it’s called but instead it stores it in a table in a file that it refers to later on, this would still be very heavy on the memory and very time consuming.
I thought about using Monte-Carlo but given that N is around 60 trillions, the Monte-Carlo sampling needs to be very big to cover at least most cases. Ex: If we choose randomly 10 000 cases (with would take around 5 seconds), this represents a very small percentage of all possibilities and wouldn’t be enough to draw our conclusions.

Therefore, even after optimisation, this code is too inefficient. However, I did learn all the steps and tactics of poker while trying to understand it, which makes documenting about the subject easier.
 
#WEEK_3

I read few papers that covered most methods that are used for poker bots.


#WEEK_4

Through my search, I finally found a state of the art algorithm that was initially used in order to solve poker: Counterfactual Regret Minimisation (CFR).
Given the complexity of the Texas Holdem Poker game, I decided to first apply this algorithm on Kuhn Poker which is a simplified poker game used as a theoretical model for research to study game theory.


#WEEK_5

I started by creating 2 files: Node and Trainer which store the strategies and train the bot until finding the Nash equilibrium (respectively). By applying the Contrafactual Regret Minimisation on Kuhn Poker, we can find the optimal strategy for playing Kuhn Poker, i.e. in each situation of the game we have that the bot should pass with a probability X and bet with a probability 1-X. It follows that the optimal strategy is to follow these probabilities on every move of the bot.


#WEEK_6

Given that it takes few seconds for the strategy to load (around 40 seconds) and that all the strategies are not needed in each game, I saved the computed strategy in a file (KuhnPokerStrategy.txt). Then I made a new file kuhnbot which loads the strategy from the txt file to a map where each game situation is mapped to the probability of passing (the probability of betting follows from the probability of passing).


#WEEK_7

In the kuhnbot file I added a function decideaction which takes the card that the bot has and the history of the game (what already happened in the game) and returns Pass or Bet. To respect the probabilities previously computed, we generate a number randomly between 0 and 1, and if the number is less than the probability of passing, than the bot returns Pass, else it returns Bet.



