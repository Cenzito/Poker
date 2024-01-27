## Week of Monday 20 Nov 2023

1. **Player, Game and Deck Class Architecture:**
   - Worked on the architecture w. comments of `Player`, `Game`, `Deck` classes, outlining ideas for essential functions.
   - The objective is to enable a logical flow for a full game of poker.
  
2. **Implementation Concept:**
   - Envisioned a structured approach:
      - `Game` class manages the game flow, rounds, winner determination, and prize distribution.
      - `Player` class creates player instances, each with chips, the ability to play, and potential user interaction.
      - `Deck` class, focused on card distribution, randomly selects integers (1-52) representing cards.

3. **Next step: Code Implementation:**
  - Translate architectural concepts into code for the `Player`, `Game`, and `Deck` classes.

## Weeks of Monday 27 Nov 2023 and Monday 4 Dec 2023

1. **Implementation of `Player`, `Game`, `Deck` classes**
   - Implemented the `Player`, `Game`, `Deck` classes to create most of the logic of a poker game in `logic_scratch.cpp` and `logic_scratch.hpp`
   - Main issue: I was not coordinating my work with my team causing people to overlap work
   - After communicating better I decided to follow the approach idealized by Remi as separating all the classes in different files eases readabiltiy

2. **Finalizing basic logic of poker game**
   - Completed the `PokerPlayer` and `Game` hpp/cpp files to complete the logic of a poker game
   - Added the logic of the rounds of betting: `round_of_betting` to have one round of betting after each step - preflop, flop, etc
   - To make this possible needed to implement `turn` to let player choose to call, raise, fold, `end_round` to determine winner, and resp. methods/attributes to `PokerPlayer` class

## Week of Monday 11 Dec 2023
1. **Optimization of `PokerHand` class**
   - Worked on finding a more optimal way to find a player's hand as the current method loops over the cards for every possible hand
   - Found a way to loop only twice over the cards available (2 cards of player + 5 cards in middle of table)
   - After talking with Lazea, we decided to keep `PokerHand` as is for now as it is more readable and optimize later (in January)

## Weeks of Monday 18 Dec 2023 and Christmas Holidays
1. **Compatibility of Logic with Server**
   - Worked on making the logic code fit with Servers
  
## Weeks of Monday 8 Jan 2024 and Monday 15 Jan 2024
1. **Optimization and Expansion of `GameLocal` class**
   - Implementation of Internal Hand Storage instead of calling player's hands
   - Various optimizations like const-correctness
   - Managed case where 2 or more players tie: splits pot and divides it between them



