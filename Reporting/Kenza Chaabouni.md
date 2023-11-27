20/11-26/11
Algorithm required to make a medium bot which only looks at its own cards (2 cards) and decide to fold or call in depending on the 
probability of winning with these cards:
This corresponds to the beginnig stage of the game, the pre-flop stage.
The bot only knows its own cards X and Y, and so there are n = 50C2 possibilities of different games with different outcomes. 
We then simulate the different games and keep count of the ones where the bot wins (m number of wins). 
It follows that the probability of winning with the cards X and Y would be m/n. 
For the sake of convenience, as the number of computations would require a long time we only need to assign a value to each pair of cards
X and Y, out of which we conclude a value of each card (in a range between 0 and 20). This is followed by checking if the two cards are 
a pair or have the same suit. In the case of a pair,  we update our pair value to be the maximum of  twice of what it was or 5. In the 
case of the same suit we add 2 to the pair value. We then calculate the difference between the power of the individual cards of the pair,
taking its absolute value, and performing the following in the following cases. 
Difference = 0, no change in value
Difference = 1, increment value by 1
Difference = 2, decrement value by 1
Difference = 3, decrement value by 2
Difference = 4, decrement value by 4
Default, decrement value by 5
The final value is the updated value minus the difference between the two pairs
This algorithm is the Chen algorithm. The Algorithm was developed by solving all the possible games from the pre flop. In all its k 
iterations, k being a sufficiently large natural, computed the average winning odds. This is done for all the possible pairs and then for
all j number of players, where j is between 2 and 8. Doing these in real time is not feasible and thus rely on the Chen formula, which 
has been created after multiple computations and calculations. This algorithm has a success rate of 60-70%, which has been computed to 
be the most efficient. We will use this in our bot.
