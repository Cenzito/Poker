
## Week 1

1. Create card.hpp, a card class is defined.
2. Create player.hpp, a player class is defined.

## Week 2

1.  Create bot.hpp, which defined a bot class, derived from PokerPlayer.
2. Declare a member function "action" of PokerPlayer, being called when it is this player's turn. The function is virtual and is overrided if the player is a bot.
3.  Create BotDrunk.hpp and BotDrunk.cpp, which defined a drunk bot who always calls or all-in.

## Week 3
1. Make sure that Bot is a abstract class, and all bots using a specific strategy are derived from it. Make "action" in the Bot class a pure virtual function.
2. Communicate with the game logic team and confirm the return value and parameters of "action". Define a new class Table to record all information on the table for players (especially the bots) to make decisions. 
3. We are still waiting for the game logic team to complete some functions.
