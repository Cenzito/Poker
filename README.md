**DOCUMENTATION** for the logic part of the project:

**PokerCombinations** class- enumerates all the possible poker combinations and ranks them, useful for future hand comparisons

Functions:

    combinationToString (takes as argument an object of type PokerCombinations) -> computes a String representation of the given Poker combination

**Suit class** - enumerates all poker suits and ranks them, useful to avoid conflicts when comparing cards

Functions:

    suitToString ( takes as input an object of type Suit) -> returns the string representation of that given suit

    stringToSuit (takes as input an object of type string) -> returns the Suit object of that given string, whenever possible

**Card Class:**
It is the most basic representation in C++ of a Card, containing two attributes, a rank and a suit.

Data members:   

        suit (an **object of class Suit**) : (Hearts, Diamonds etc.)

		    value (int) (2-14 with 14=ace)

Member Functions:   

        The constructor, Card(Suit suit, int value) 


        getSuit (returns the suit)

		    getValue (retuns the value of the card)

		    toString (represents the card in a string format)

		    Overloaded < , >, =, != operators, for comparing cards

		    Overloaded << operator, for printing and debugging purposes

		         

**Class Deck:**
Representation of the deck, stores all possible cards and has specific functions.

Data members: 

    cards (all the remaining cards in the deck represented as **a vector of cards**) 
    
    currentCardIndex (**int**) shows where we find ourselves among the cards of the deck when dealing cards

Member functions:   

    Constructor -> initializes a deck with all possible cards and initializes the currentCardIndex to 0

    shuffleDeck (**void**) -> creates a random shuffling of the deck

    dealCard (of type **Card**) -> returns the card at the current index and increases the currentCardIndex

    getCurrentCard (of type **Card**)-> returns the card at the current index without increasing the currentCardIndex

**Class PlayerInfo:**

Contains all the relevant data that identifies a Player

Data members: 

    name (a **string**) -> represents the name of the Player

    stack_size (an **int**) -> represents the total amount of chips left to the player

    bet (**int**) -> represents the bet that the player makes

    isAllin, isFold (of type **bool)** -> booleans used for identifying players that fold or are all-in

    cards (of type **std::vector <Card>**) -> attribute that keeps the cards of the player

Member functions:    the constructors 

    Print (of type **void**) -> a function that prints all data members of a player, used for debugging

**Class PokerHand**

Used for comparisons and hand valuation of any vector of cards.	         

Data members: 

    cards (of type **std::vector <Card>**)

Member functions:

    The basic constructor

    get_cards (of type **vector of objects of type Card)** -> returns the cards from the respective hand

    is_member (Card card) -> takes** as input a card** and checks if the card is inside the hand or not **(returns a boolean)**

    order_cards (of type void) -> orders the cards in the hand in descending order

    get_combination (of type PokerCombinations) -> returns the best PokerCombination inside a PokerHand

    **void** order_cards -> order the cards in descending order

    boolean function: implemented `has_high_card, has_pair, has_three_of_a_kind, has_two_pairs, has_straigt, has_flush, has_full_house, has_four_of_a_kind, has_straight_flush, has_royal_flush `returns a boolean if the poker combination can be formed in the hand or not

    **int** max_straight -> gets the best straight in hand with potentially more straights. Returns **an int** representing the highest rank of a card that is in a straight in the given hand.

    **std::vector <int>** get_score -> given a hand, it “scores” the best combination that can be formed along with all potential kickers in a hierarchical order for potential ties. Returns an object of type std::vector <int>, where hands are to be compared by comparing their respective scores in a lexicographic manner.

    **int** compare_hands (PokerHand hand1, PokerHand hand2) -> checks the winning hand, returns 1 if hand1 wins, 2 if hand2 wins and 0 if there is a draw.

**CommandType** Class -> enumerates all possible actions that might change the state of the table (bets, changes of rounds, etc.). These commands are transmitted to the table and processed via the function updateTable

**Class Table:**

The table contains all relevant data regarding the state of the game and the characteristics of the players and ways of processing different signals from the players (seen as objects of type CommandType).

Data members:

    communityCards (of **type std::vector <Card>**) -> stores the cards publicly available at a given stage

    seats (of **type int**) -> stores the maximum number of players at the table

    player_num (of **type int**) -> stores the number of players playing 

    current_player (of **type int**) -> stores the number of the player to play

    ButtonPlayer (of **type int**) -> defines the type of player at a particular stage of the game (big blind, small blind)

    SBValue (of **type int**) -> stores the value of the small blind

    BBValue (of **type int**) -> stores the value of the big blind

    pot (of **type int**) -> stores the current pot

    betting_round(of **type int**) -> stores the current stage of the game (0:preflop, 1:flop…)

    current_biggest_bet (of **type int**) -> stores the value of the current highest bet 

    lastRaiser (of **type int**) -> stores the number of the player that was last to raise

    PlayerInfo (of type **std::unordered map <int, PlayerInfo>**)  -> hash map associating each position to the player there (playerInfo[0] is the first player that joined)

Member functions:

    active_player() (of **type int**) -> returns the number of players currently in game (that did not fold)

    playerIndex (std::string &name)  (of **type int**)-> taking a name, returns the position of the player with that name in the hash map PlayerInfo

    updateTable (std::string Command) (of **type void**) -> taking a command as input, the table processes it

    parseCommand (const std::string &command) (of **type CommandType**) -> taking a string, this function transforms it into the corresponding CommandType object.

    getPlayerInfo (std::string name) (of **type pointer to an object of type PlayerInfo)** -> receiving the name of a player, this function returns the PlayerInfo data member of the player that has that name, information retained in the hash map PlayerInfo.

**Class PokerPlayer**

The class representing every PokerPlayer, contains all important information regarding a PokerPlayer and ways of processing signals from the table and sending commands to the table.

Data members:

    tableInfo (of **type Table**) -> each player has a state of the table available 

    name (of **type std::string**) -> keeps the name of the player 

    hand (of **type std::vector <Card>**) -> keeps the cards of a player

    isBot (of **type bool**) -> boolean to identify the players that are bots

    isActive (of **type bool**) -> boolean to identify the active players at a given stage of the game

Member functions:

    showHand(of **type void**) -> prints the hand of the player (not implemented)

    receiveCards(std::vector <Card> ) (of **type void**) -> initializes the hand of a player with the cards it receives as argument

    removeCards() (of **type void**) -> deletes the cards from the player’s hand

    getHand() (of **type std::vector <Card>**) -> returns the cards of the player

    getName() (of type **std::string**) -> returns the name of the player

    updateTable(std::string command) (of **type void**) -> sends a specific command (in the form of a string) to the table to update it

    updatePInf (std::string commandPInf) (of **type void**) -> initializes the table information for new joiners in the game.

    Raise (int amount) (of **type void**) -> the action for raising the bet at the specified amount, taken as input (the new bet is exactly the input). It is a signal

    Fold (of **type void**) -> the action called for folding

    Call (of **type void**) -> the action called for calling 

    callUpdateDisplay (of **type void**) -> signal making the connection between the logic and the visuals parts of the project

**Monte_Carlo_Probability_Simulator**

Takes as input the table (of type Table), a hand(of type std::vector<Card>), a number of active players (of type int), and a number of simulations (of type int).

Returns an object of type std::vector<float>, of the type **(winning_proba, draw_proba, losing_proba)** ,which contains the winning probability, drawing probability, and losing probability given the current hand and the exact stage of the game.

**Bot**

The bot class is inherited from the PokerPlayer class, which makes all the functionalities of the PokerPlayer reusable for each bot. Furthermore, all other bots are obtained from a public inheritance of the Bot class. When a bot is constructed, it calls the constructor of a PokerPlayer and also initializes the level of the bot and the boolean **isBot** to 1. The specific functions added to this class are the public slots:

	call_bet() (of **type void**) -> is called when the bot decision is to call the bet
 
	fold_bet() (of **type void**) -> is called when the bot decides to fold
 
	raise_bet( int amount) (of **type int**) -> is called when the bot decides to raise, the amount received as input being the new bet 

 	find_stack_size () (of **type int**) -> function that returns the remaining wealth available to the bot

The last function of the bot class is:

	Action( of **type void**) -> a virtual function, when called, the bot decides between one of call_bet, fold_bet, raise_bet. 

 Furthermore, all other bots integrated different functions and data members to run a specific strategy.

