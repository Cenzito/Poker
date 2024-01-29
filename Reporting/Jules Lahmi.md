Week 1 & 2: 

Started working on GameLogic and basic functions such as bet mainly through comments since most of the classes were not entirely implemented there yet.
Work on functions in the Game.hpp and .cpp files. (these files that are currently deleted and replaced with GameLocal, which do sensibly the same thing).

Week 3 & 4: 

Worked on the table class, and making it so that each player has its own table object.

Made it so that each function in the Game file (and class) updates the players tableInfo, which is a table object, though the updatetable function.

Week 5 :

Bug fixing on the previous functions, adjusting the switch from Game to GameLocal files/class.
Making sure the PlayerInfo objects associated to the player are always updated.

Week 6 : 

Implemented a function that computes pre-flop odds in a heads up using a 13*13 matrix to give an idea to new players of how strong their hand is.
This function does not take into account the board, or the possible fold/bluff of the opponent (ie assumes that the hand will be played trough until the river).

Week 7 & 8 : 

Tried for a long time to implement a LeaveTable function, that would ideally in multiplayer games make the player leave the table trough a button,
while being able to spectate the other people playing. This function would have been called through an onLeaveTableClicked in GameWindow that would use the
GameLocal object to call the GameLocal function LeaveTable. Sadly, since multiplayer is not yet here, this button is a bit useless so I never implemented it 
(watching 2 bots play each other is not very interesting). Also, I actually didn't manage to finish the function : instead of removing the player from the table,
it removed the bot that was last added, always. I also didn't bother to take in account exceptions such as leaving on your turn, or when you're the big/small blind
or other stuff like this. 

Week 9: 

Bug fixing, and a few ui changes to make the interface a bit prettier.
