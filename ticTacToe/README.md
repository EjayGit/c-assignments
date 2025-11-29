# Problem Statement
## Tasks:
Create a game to be played by two players. The board is defined as a 5 x 5 array. Two markers are to be used, ‘X’ and ‘O’. The objective is to place 4 markers, consecutively in a row, column or diagonal. The first player to do this wins, or if the board becomes full and this is not achieved, then it is a draw.
The program must:
    • Give the players instructions:
        ◦ How to play,
        ◦ Aim of the game,
        ◦ How to input marker position.
    • Ask if it is going to be a game of two human players or one human vs the computer,
    • If human vs computer is selected, then give an option for the computer to play first or second,
    • If 2 human players, they must alternate turns. The first player to go will place the ‘X’ markers, the second will place the ‘O’ markers,
    • Input of marker to board position can run on a co-ordinate input system,
    • After each move, the board must be fully visible on the screen with all previous moves,
    • Illegal moves (ie. out of bounds or previous position) must display a message and user allowed to re-enter a co-ordinate,
    • When 4 consecutive ‘X’ or ‘O’ occurs, display “X/O is a winner” and ask if the user wishes to play again.
    • When human vs computer game is played, the computer tactics should be similar to:
        ◦ First check to see if an immediate win is possible, if so, take it,
        ◦ Check to see If the human can win, if so, block it,
        ◦ If neither above is true, select a random space.
I am going to tweak it. Instead of having a fixed 5 x 5 grid, I will create the option for the user to decide between a 4 x 4 and a 9 x 9 grid.
# Analysis
## Inputs:
    • Decide for game to be Human vs Human, or Human vs Computer,
    • If Human vs Computer, decide who will go first,
    • Co-ordinate inputs by human,
    • Once game ends, decide whether to play again or exit the game.
## Outputs:
    • Display game instructions,
    • Request Human vs Human or Human vs Computer,
    • If Human vs Computer, then request Human or Computer to play first,
    • Display grid
## Other tasks:
    • Allocate memory for board,
    • Ensure that space selected has not been chosen previously and that there are still spaces available,
    • Test for win,
    • Computer must win if it is possible,
    • Computer must try block a win,
    • During game, monitor whether “X” or “O” is the appropriate marker to place.
# Design
## General Algorithm:
    • User enter options,
    • Allocate dynamic memory and insert blank spaces ready for gameplay,
    • Print blank board,
    • Determine first player,
    • Check for draw,
    • If human:
        ◦ Scan co-ordinates,
        ◦ Test for space at entered co-ordinates, if no space then re-enter,
        ◦ Place relevant marker,
    • If computer:
        ◦ Check for draw,
        ◦ Check for 3 in a row for the win and win game if possible,
        ◦ Check for 3 in a row for opponent win and block if possible,
        ◦ Check for 2 in a row for opponent set up and block if possible,
        ◦ Check for 2 in a row for own set up and set up for win if possible,
        ◦ Place marker in random position.
    • Print board,
    • Check for win,
    • If no win, pass to computer,
    • If win, option to end game or restart.
# Implementation
## Functions:
    • Main,
    • Restart,
    • Userinfo,
    • Allocateboard,
    • Printboard,
    • Human,
    • Comp,
    • Checkentry,
    • Checkspace,
    • Check4,
    • Test4,
    • Check,
    • Test3,
    • Test2,
    • Placeh,
    • Placev,
    • Placedr,
    • Placedl,
    • Endgo,
    • Deallocateboard,
    • Win,
    • Draw.
### Main
    • Gives initial game information,
    • Requests game options to be selected,
    • Allocates the board into memory,
    • Prints the initial empty board.
### Restart
    • Clears the board of all previous markers,
    • Requests new user information,
    • Prints the new empty board,
    • Starts play.
### Userinfo
    • Collects and saves the values entered by the user into memory via pointers,
    • If human vs human, then makes turn = 1.
### Allocateboard
    • Allocates the maximum memory required for the board,
    • Initialises the board with spaces.
The initial plan was to have the board reallocated onto memory after each game. This would mean that deallocation would be required at the end of each game too. As the board size is only small in this case, I decided that to use the maximum board size available was the best option so that the reallocation of memory was not required after each game. If the boards became huge, then it might be in the interest of memory to only allocate what is required, but in this case I have limited them to 9 x 9.
### Printboard
    • This function only prints the board whenever it is called with the current markers saved to it.
### Human
    • Checks for draw,
    • States whose turn it is (ie. which marker is going to be placed on this turn),
    • Collects user co-ordinates and checks against previous entries,
    • Sends co-ordinates to grid via endgo().
### Comp
    • Checks for draw,
    • Checks for priority marker placement options,
    • If no priority placement required selects random co-ordinates,
    • Sends co-ordinates to grid via endgo().
### Checkentry
    • Checks against previous marker entry.
### Checkspace
    • Counts the number of spaces left on the board.
### Check4
    • Checks for a winning row in any direction.
### Test4
    • Tests for 4 similar markers.
### Check
    • Checks for, in order:
        ◦ 3 in a row for the current players markers,
        ◦ 3 in a row for the opponent players markers,
        ◦ 2 in a row for opponent players markers,
        ◦ 2 in a row for current players markers.
    • If any of these tests came back positive and there was a space available for a marker, then a marker is placed.
### Test3
    • Tests for 3 similar markers.
### Test2
    • Tests for 2 similar markers.
### Placeh
    • Tests for options to place marker dependant on position of the row of similar markers along the horizontal axis.
### Placev
    • Tests for options to place marker dependant on position of the row of similar markers along the vertical axis.
### Placedr
    • Tests for options to place marker dependant on position of the row of similar markers along the diagonal down-right axis.
### Placedl
    • Tests for options to place marker dependant on position of the row of similar markers along the diagonal down-left axis.
### Endgo
    • Enters current marker into row/ col given to function,
    • Swaps turn and marker values ready for next player,
    • Print the board,
    • Calls function to check for a win, test4().
    • 
### Deallocateboard
    • Free memory,
    • Exit program.
### Win
    • Give user option to either restart game or quit the game,
    • Call deallocate() to quit, or restart() to restart.
### Draw
    • Give user option to either restart game or quit the game,
    • Call deallocate() to quit, or restart() to restart.

# Testing
A very large amount of testing has been carried out during the creation of this program. Not all has been recorded due to time constraints. In general, each function had a number of tests placed against it and I did not continue with the next function until I was thoroughly satisfied that it was working properly. I started at the beginning of the game and worked through logically similarly as to how the gameplay would through it, adding functions and sections to functions as I went along. There were initial constraints given in the problem statement. These were tackled immediately where possible so that the design would fit around them as fluidly as possible.
    • Give the players instructions:
        ◦ How to play,
        ◦ Aim of the game,
These instructions were given in the opening welcome message.

        ◦ How to input marker position.

    • Ask if it is going to be a game of two human players or one human vs the computer,
    • If human vs computer is selected, then give an option for the computer to play first or second,

    • If 2 human players, they must alternate turns. The first player to go will place the ‘X’ markers, the second will place the ‘O’ markers,
On top of the variable ‘turn’, I had ‘marker’. While ‘turn’ would keep track of whose turn it was, ‘marker’ would separately keep track of the marker type, ‘X’ or ‘O’. The marker would always start of representing the value meaning ‘X’, but the turn could either start off as ‘1’ or ‘2’.
    • Input of marker to board position can run on a co-ordinate input system,
This as shown above is exactly as I have done it.
    • After each move, the board must be fully visible on the screen with all previous moves,
printboard() is called after each marker is entered into the grid in the function endgo().

    • Illegal moves (ie. out of bounds or previous position) must display a message and user allowed to re-enter a co-ordinate,

    • When 4 consecutive ‘X’ or ‘O’ occurs, display “X/O is a winner” and ask if the user wishes to play again.

On top of this option, when restart is selected, the game play actually restarts, giving the user the reselect options with a fresh grid of their choice. If the option to quit is selected, the program exits successfully.
    • When human vs computer game is played, the computer tactics should be similar to:
        ◦ First check to see if an immediate win is possible, if so, take it,
        ◦ Check to see If the human can win, if so, block it,
The check() function tests for any 3 in a row of its own markers first and places a marker for a win if the option is there, and afterwards finds any 3 in a row of the opponents markers and attempts to block their win, in that order. It also goes further. It subsequently checks for 2 in a row (a set up for a guaranteed win if not blocked) and attempts to set up itself with an own marker at the end of a row of 2. If no own markers are found 2 in a row, then it attempts to block any 2 in a row of the opponents markers.
        ◦ If the above circumstances cannot be found, select a random space.
The comp() function has as its last function (other than ending its turn) to select a random number between 0 and the maximum length (size) for the row, and for the column. It continues to re-select a co-ordinate until it has chosen one that has a space.
Simple testing for these requirements is either above as evidence or below, to prove that such information has been saved into memory and that the program is working as required.
    • When the user selects to play the computer, I am first given the option whether to play first, or whether the computer should play first,
    • If I select to play first, I am always given first go starting as player ‘X’,
    • If I select the computer to play first, then I am always given the second turn as player ‘O’,
    • If I am playing human vs human, then the first player is always player ‘X’,


    • Checking for 2 in a row (and the priority for the check) can be seen working when the comp and myself are put in a situation where we both have 2 in a row,
 





    • The first screenshot I am about to place an ‘X’ into row 4, col 2. This would make it so that both the computer and I have one 2 in a row each. If the priority was to be defensive, it would place an ‘O’ at row 4, col 3 to block any further advance. Instead, we can see in the second screenshot, that it selected row 3, col 2 to advance the 2 in a row it had already.
    • The same occurs for 3 in a row, and thus the computer plays a win over a block to stop the opponent winning.
    • For many parts of the program I have mini programs that test to ensure that the logic is correct for each section before joining them together. I have not got time to lay these out here, but it worked, eventually.
    • I have played many games of this consecutively with human vs human and human vs computer starting computer first and human first. I appear to have squashed all the bugs… finally.
