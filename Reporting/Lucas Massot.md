
Week 1 (20.11. - 26.11.) 

We created the gamewindow with other members, and I tried to implement the Card class but had issues with github merging that made me lose half of it.

Week 2 (27.11. - 3.12.) 

I uploaded the images of the cards in the resources and took care of the hierarchy of the ressource file, I also created the test button deal card, the function get_image_path to handle the conversion from a (suit, value) to a image path in the ressource, and implemented the label cards in the gamewindow.ui file (display file).

Week 3 (4.12. - 10.12.)

I Implemented the bet system buttons, that is Call, Raise, Fold and the box on the side to enter your bet on the .ui file and connected the line_edit with the box and the Raise button to display the amout you bet in it when Raise is pressed. I also added two functions to make the link between logic/server and ui, namely update_to_display andf update_from_display (we eventually merged them into update_display) where the team can add their sub_functions to update the dipslay.

Week 4 (11.12. - 17.12.) 

I added the background and the line_players, then I worked on a function to display the stacks of the players, that is how much money they have. My initial idea and the one that i first implemented was to allow the player to click on one's name_line to switch from the name to the stack through slots, but its not the one we kept, rather the extended display_name_bet function which is discussed below. 

Week 5 (18.12. - 24.12.) 

I implemented the function switch_players_display to make sure that the number of line_players and line_bets that were displayed was always matching the actual number of players in the game.

Holidays 

I took care of merging all the ui branch and unify them into a single MAIN_UI one, and checked and perfected display/ui related functions that I had created.

Week 6 (8.1. - 14.1.) 

I started working on the expensible window and reworked the whole display with layouts. I recoded display related functions that weren't working, and added functionalities to these displays functions, especially the display_name_bet that became display_names_stacks_bets, that now work and also displays the stack of the players along their names.

Week 7 (15.1. - 21.1.) 

What is left to do is take care of the display, so I reworked to display in order to add cards for the other players that would show at the end of each rounds what were their cards to the other players using the display_given_cards function. I also added the next_round button on the display and reworked the layouts so that these new widgets would fit and extend correctly. I finally added a display_name_red function which puts your name in red so that it is easier to keep track of where you are around the table

Week 8 (22.1 - 29.1.) 

Up from there we had left to work on was the layouts, and to make sure that they extend correctly and that the window can be resized properly. Hence, I mostly dedicated time to it, and make sure that my work can merge with the rest.


