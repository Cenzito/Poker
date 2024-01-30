Week 1: Connected two interfaces (homewindow and gamewindow) and resolved some compiling issues. Still struggling with github, so was merged to main by Remy.

Week 2: I was elected leader for UI/visuals. At this point, we are mainly waiting for the logic section to have moved forward in order to implement parametrized visuals, but we designed the home menu with fonts colors and images.

Week 3: I assigned everyone to a role/section now that the logics section has advanced (still several bugs on main branch so we all stuggled to work during the TD session) :
  - Table Cards
  - Player Cards
  - Implementing a possible visual for chip stacks (seems complicated but trying)
      - Player stacks
      - Pot
  - General game appearance, differentiating active and inactive players, displaying player names, etc...
  I personally tried to set a background for the gamewindow but had problems displaying a png image (only worked for jpg), but resolved now. I have started searching for ways to 
  implement a variable visual for chip stacks, but seems very difficult. For now, I have found images of different chip stack sizes, which should cover for most cases.

Week 4: I have been looking for ways to implement the chip stack, but for now I have not found any useful resources online, and I cannot find a way to overlap the images as I want, since qtdesign uses a 'grid' system for the elements on the page, so it cannot deal with the minute differences in position a chip stack would require. I will keep trying to find a solution during the week, and if I cannot find anything reasonable, we will have to settle with a select number of png images representing chip stacks. The team has advanced well, we have three working windows, and some basic content on each. 

Week 5: Unfortunately, I couldn't find any way of implementing the variable visual for chip stacks, so I'll move on to working on other functionalities. During the td session, I added a dropdown box and AddBot button, to allow the bots team to add bots on the table. Also, I added the opponent's cards to the visual, however only the back of the cards can be displayed for now, as I had trouble accessing the information on the opponent's cards. I also added a poker-style background to the scroll-able part of the Rules Window, as well as to the area designated on Game Window for Player actions (where the buttons and commands are), to differentiate it from the rest of the page.

Week 6: We have decided to try to make the page re-sizable, so that the player can go on full-screen for example, but this means a lot of the work done previously had to be removed or revised. So, this week I merged the changes I had made last week to the main_ui branch, while making my implementations compatible with the "layouts" system. I did not manage to make the background for the player command area work with layouts, so that was erased. 

Week 7: I added the background to the player command area by modifying the original image with photoshop. Added the middle pot image and added a LineEdit box for the Pot Quantity. The middle pot image changes if the pot becomes big (more chips on the table than not). This is done by verifying the size of the pot each time display is updated. I fixed an issue in the Rules Window, where an image was not displaying, and added a function to convert the player hand into a string. This is displayed in a LineEdit above the player cards, where the nametag was (which I have therefore placed at the top of the window instead. I added a box to display the odds of winning a hand in heads-up (1v1), so that a new player can get a general idea of which hands are good and which aren't. This is displayed in the Player command area, on the right.

Week 8: This week, we are coming to the end of our project and visually, we are all very happy with how the ui turned out! Everyone worked on some final visual touches, on bug resolution (quite a few were found after testing on different hardware). I added kick buttons to each visible player, so that the main player can kick others (thought that might be fun) and also so that by using the same function, players with no money can be removed from the table, solving a few bugs. For some reason, the background I had added to the rules window was removed from the images folder, and I could not get it to work again by finding another image... I fixed an issue with the AddBot system, as the dropdown box was being disabled permanently after Next Round was pressed. Now, the add bot button itself is disabled, only during rounds, so that players can see which bots are available even while playing.

