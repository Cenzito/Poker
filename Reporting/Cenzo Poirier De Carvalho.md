# Cenzo Poirier De Carvalho's Report file
### Role: Git Leader

--------------------------

Created the repository November 14th.

## Week 1 (27/11 -> 03/12)

#### Git
Added everyone to the repository and explained how we would be working on Github
and did some organisation.

#### Coding
Started coding a simple bot that plays entirely at random called monkeybot
but couldn't get far because of the lack of logic implemented at this point.
Fixed other small details.

#### Research
Looked into different algorithms for simple bots and watched videos
about coding poker bots.


## Week 2 (04/12 -> 12/12)

#### Git
Organised the repository and looked into branch protection since people were
force pushing. Bunch of merges and associated conflict/bug resolutions.

#### Coding
Discussed with the bot group on how to structure the bot class and we implemented a skeleton for that code.
Helped logic with sorting cards. Also fixed bugs here and there.

#### Research
Researched different ideas for bots, mainly counterfactual regret minimization
and how reinforcement learning techniques could be applied to bots.

## Week 3 (11/12 -> 17/12) 

#### Git
Found a way of effectively protecting the branches which was to simply 
protect main from force pushes. Other solutions seemed too tedious. Now me and Remi
are mostly in charge of merging though we sometimes tell people to check with their group
when the code is too specific. This is an extra responsability since we sometimes have to solve conflicts
and bugs, on top of merging everyone's branches. I told people to simply create a new branch every time they wanted to implement a new feature.
This creates a lot of branches but simplifies merging since branches are kept fresh.


#### Coding
Organized the Table class and inserted constructors to make sure no trash variables appeared anywhere.
Started working on a testGameLocal function which would help the Bot team run simulations, or at least 
test their bots. Fixed a couple things.


#### Research
Continued researching bot ideas but couldn't get to it since logic doesn't work.

## Week 4 (18/12 -> 24/12)

#### Git
Now people can't force push, main compiles and I solve conflicts when merging if people
don't do it themselves, solving bugs and making small modifications or comments. Deleted useless branches.

#### Coding
Simplified/fixed some parts of the code. Made small changes to details of the game,
who starts first, how to index players. Separated and fixed functions when the code
was unclear/too full.

#### Research
Researching very specific game rules of poker to make sure of the accuracy of the game.
For example the player with the button is the last to act pre-flop, button+1 is small blind,
button + 2 is big blind etc...

## Week 5 ( 08/01 -> 14/01)

#### Git
At this point, most people in our group know git basics and don't need helping in that
regard anymore. I still merge solve issues that creates. Deleted useless branches.

#### Coding
Started coding the beginnings of a bot with Leal. We settled on the idea
of using reinforcement learning using the MonteCarloWinningProbability as a variable as well
as the opponent call amount. To this effect, I tried fixing the MonteCarlo function
to take into account the player's hand directly instead of the player variable.
Fixed other small bugs/issues.

#### Research
Spent time with Leal trying to find a creative way of making our own bot.

## Week 6 ( 15/01 -> 21/01)

#### Git
Made some fixes to the file names. For some reason, "Table.hpp" was now appearing as "table.hpp" which
confused the compilers. Made many merges as well as solved conflicts/bugs.

#### Coding
Continued trying to fix the MonteCarlo function. Made some more small updates to the bot
with Leal. We spent most of the TD time planning out what it should do and how.

#### Research
Researched a bit into what C++ libraries could be used for reinforcement learning.

## Week 7 ( 22/01 -> 29/01)

#### Git
Final week of work, a lot of merging happened. I did a lot of conflict resolution with Remi.
I have taken care of deleting some branches because there were too many but we decided to keep some in case
people wanted to showcase some work which didn't make it to main.

#### Coding
Seeing that there remained a lot of work to do in logic, I decided to move my efforts to the logic side.
I coded all in functionalities, subpots, a function to determine the winner(s). I coded distribute()
which distributes the money taking everything into account, including the possibility of a tie or everyone being all in.
This was a lot of work and it needed many hours of debugging (~10 hours), even if the errors turned out to be many tiny issues. I still wanted to code a bot and since now the logic worked,
I decided to return to my MonkeyBot idea which I decided to implement using special random functions which work
better than random() which returns bad values. Decided to comment the entire GameLocal file to make the code clearer.
To implement bot names I coded a function that returns a random available bot name. I then added fun little details like
MonkeyBot only having monkey names and DariusBot having joke names. Made many other small fixes.

#### Research
Researched Poker specific rules to check who wins in specific multi way ties and all ins.

