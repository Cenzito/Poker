# CSE201 Project Individual Report

Student Name: Pu Yang

Project name: Poker

GitHub repository: https://github.com/Cenzito/Poker

My Github account: CChanis

Brief description of my work: I am a member of the bot team. I created a simple bot that always calls and a hard bot based on Counterfactual Regret Minimization (CFR). I also communicate with the logic team and write a little bit of code in the game logic part.

## Week 1

I created card.hpp, player.hpp. (Later they were deleted and merged into Card.hpp, PokerPlayer.hpp)

## Week 2

I created Bot.hpp, which defined a Bot class, derived from PokerPlayer. I also declared a member function "Action" of PokerPlayer, being called when it is this player's turn. The function is overridden in Bot.

## Week 3

I made Bot an abstract class. All bots using a specific strategy are derived from it. The function "Action" in the class Bot is a pure virtual function. I also defined a class Table to record all information on the table for players (especially the bots) to make decisions.

## Week 4

I created a drunk bot, who always calls. It can be used to test our project. I also communicated with the logic team and waited for some functions from them.

## Week 5

I learned some algorithms to design a hard bot. Finally, I chose CFR and sketched my CFR bot.

## Week 6

I completed the decision process of my CFR bot in the first round (pre-flop) and the last round (When there are 5 community cards).

## Week 7

I completed the decision process of my CFR bot when there are 3 or 4 community cards. Now, I finished my CFR bot and my work.
