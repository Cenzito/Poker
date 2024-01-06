Week 1 and 2 (23 and 30 november) : 
Almost finished the basic logic of the game :
- Created Different classes to start implementing the Poker game (Cards, Deck, Player, Gameloop)
Next Week: 
- Continuing finalising the game loop by implementing betting and taking input from the players

Week 3-4 (07-12/14-12) : 
-Started implementing the betting system in poker player and game (on the logic updated branch for now since I wasn't able to test everything).

Week 5

I did research on different ways in which we could implement poker hands in our game. Here are some ways that I found and started toying with: 
Using Structs and Enums
Object-Oriented Approach with Classes
Vector of Structs or Objects for Hand History
Overloading Operators for Hand Comparisons

Week 6 

I worked on bug fixing and helped finalise the logic code: adding some error handling functions.

Week 7

I looked over code that Remi did in a pull request, testing it to make sure there were no errors as he created to work locally.

Weeks 8 and 9

Diego and I worked on different ways of dealing with poker hands:

PokerHand Class Definition and Methods: A PokerHand class was defined, encapsulating details like player name, street, and action (Bet, Raise, Call, Fold). We added methods to calculate aggression factor (calculate_af) and VPIP (Voluntarily Put in Pot) percentage (calculate_vpip_percentage) based on a player's hand history.

Hand History Parsing: We implemented a function (parseHandHistory)to read and parse poker hand history from a file, creating a vector of PokerHand objects. This function handles different game stages and player actions.

Main Function Usage: In the main function, we used sample hand history data to show the functionality of the calculations, in order to display the player's aggression factor and VPIP percentage. We used this to testing and practical application of the class and methods defined.