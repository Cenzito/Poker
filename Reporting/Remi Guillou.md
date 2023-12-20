# Rémi Guillou's Report file
### Role: Project Leader

--------------------------

## Week 1 (27/11 -> 02/12)

First week of actually working on the project. Last week and those before were mostly talking about what we wanted to implement and the goals of the project.  
During the Monday discussion session, I assigned tasks to each team. The objectives of this week will be to have a working Poker game. Meaning we can play against very basic robot players.  
###### Here are the tasks for the different teams: 
  - The team in charge of the UI aspect of the project will create a main menue and the game scene. I divided them in two groups for those two tasks. 
  - The Logic team will need to have finished working on the logic behind the game of Poker and have incorporated it into the app.  
  - The Server team is mostly autonom as their contribution isn't urgent. They are working on creating a working server in order first to play in local on multiple windows and the end goal will be to be able to play online.
  - The Bot team is starting by weak bots and will then work on one "Strong" bot each that we will then make compete against each other at the end. Their progress is really promising and I can't wait to see the end product.
  - One more team was created that will in the future be joined by the Logic team. This team will be called the Analysis team. Their goal is to create a window where we can analyse our Poker games. First we will need a way to save them then replay them. I also want statistics about them such as money gained over time, how much you bet in different positions etc... This feature would be akin to the app PokerTracker albeit less advanced.

After the organisation, I undertook to create the basic layout of the project and understanding how qmake works. I created directories for each part of the project and linked them all together. This gives us a foundation to start building our app. 
I also gave information about the workflow we would adopt and how Github works to those that struggled.

I will regularly be checking the files and commits made to the repository, making sure everything is working.

I also worked on the Game logic aspect of the project. I created a Table class which will contain information that each player will have access to at any time at the table. This object will be updated by the server and sent to every player everytime a change is detected.


## Week 2 (03/12 09/12)

Second week. Decided to focus on the logic of the project. 
Upgraded the Table class with missing information and removed functions from it. Now a Table object is simply used as a way to pass information. It has no practical functionalities. As such all of it's variables are public. The Game will directly modify them and the Player will be able to access them. 
Also decided on the way the player would interact with the server. Mainly explained the interactions of the player and the server to the people working on the logic part. The Game class will run on the server and the Player class on the user's computer. These two classes will need to be able to interact.

## Week 3

The developpment of the logic is taking some time. The previous implementations weren't addapted for a client/server relation so made remarks to the people in charge as to what to change. Meanwhile decided to start implementing a local version of the game in order for the team in charge of making the bots to have a way of testing them. Made a subclass of Game and PokerPlayer and implementing functions that would be different then that of the online version. 
In the end, got stuck on how to ask the player his raise amount. Spent some time on that. Cenzo also offered to help me and took on the rest of the functions in the local game. 
About the Visuals, I asked the people in charge for a function that would update the display based on the current state of the Table inside the PokerPlayer instance. The Table contains all the information available to the player and can thus be used to display it. The objective would be to call this function every time the Table is modified.
We also need a function to create betting buttons when it is the players turn to bet.

## Week 4




