# Problem Statement
You are required to write a program that implements a simple game which involves a user guessing a number. The file "numbers.txt" stores 55 integer numbers between 12 and 112. The game starts by asking the name of the player, and a position for a secret number within the file "numbers.txt". This position is between 1 to 55 and corresponds to a number within the file, so that the player cannot now this initial secret number. Then the objective is for the player to guess this secret number in a series of guesses. Write function(s) to take a number input from the player via the keyboard. If this number as guessed by the player is the secret number then the player wins! If not the computer should explain if the guess is lower or higher than the secret number (but do not reveal what this number is!). The computer should keep asking the player to guess until the answer is right. Finally, depending on the number of guesses the player attempted, the program should give the message: 
"You are too lucky!!" – for 1 guess 
" Excellent!!" – for 2-3 guesses
"Good!" – for 4-5 guesses
"OK" – for over 5 guesses
Also, all play history (name, order, secret number, number of guesses, etc.) for all players should be saved in a file! Previously saved files can be read and shown on the screen with the aid of a menu option.
## Tasks:
    • Make/ call list of 55 (secret) numbers between 12 and 112 in file ‘numbers.txt’,
    • Ask user for name,
    • Ask user to guess a number,
    • Allow user to guess number, counting guesses,
    • Have set message upon high/ low/ correct guess,
    • Save name, order, line of secret number, number of guesses for that secret number,
    • Option to review the history file.
# Analysis
## Inputs:
    • User name,
    • User line selection,
    • User guesses,
    • User option selection.
## Outputs:
    • Game information,
    • Print history file contents,
    • High/ low/ correct guess information.
## Other tasks:
    • Create/ call secret list of numbers,
    • Create/ call history file,
    • Save previous user information,
    • Give user options to view history file, play game, restart game or exit game.
# Design
## General Algorithm:
    • First allow user to either view history or play immediately,
    • Upon play, give game information,
    • Acquire user information,
    • Ensure secret list if numbers exists, if not, create one,
    • Find and save secret number with reference to user line selection,
    • Allow user to guess and notify when high/ low/ correct,
    • Save user info,
    • Option to reset game.
# Implementation
## Functions:
    • Main,
    • Playorhistory,
    • Giveinfo,
    • Getinfo,
    • Makeseclist,
    • Getsecnum,
    • Userguess,
    • Saveinfo,
    • Reset.
### Main
    • Calls all functions through it,
    • Holds all important information for use by whichever functions require them.
### Playorhistory
    • Gives user option to view history, or play the game,
    • If no previous history, gives user option to play game or exit,
    • If history exists, show history and then give user option to play or exit.
### Giveinfo
    • Gives user game information.
### Getinfo
    • Collects and saves user name and line number selected by user.
### Makeseclist
    • Tests to see is numbers.txt exists, if not create and populate.
### Getsecnum
    • Takes user line selection and returns the number on that line (the secret number).
### Userguess
    • Takes user guesses,
    • Informs of high/ low/ correct guess,
    • Counts and returns guesses taken.
### Saveinfo
    • Appends user information to user history file.
### Reset
    • Allows user to either play again or to exit game.

# Testing
Most testing was done through printing variable information throughout the program during its creation. Ie. printf(“test name… %s\n”, name);
I tried running the program from a folder that did not previously have the 2 text files associated with this game to test the creation of them and they were created successfully. I then ran it again and the program ran correctly without creating a second file and successfully appended information, in order, to the history file, so must have worked correctly. I also opened the secret numbers list so to ensure that the numbers I were guesses were within the range required (12 – 112) and also that when I gave a high/ low/ correct guess, that the program responded correctly.
When the user selects a number which is outside what number limits that have been imposed, the program successfully requests the user to enter the correct numbers that are available for selection. 
There is one problem and they are:
    1. When a number is required but the user enters a character, the program stops working as I intended it to. I have created a logical process that requires the user to enter a number as a string instead and for this to be tested char by char to ensure that they are number. This would eventually be turned into an integer by use of adding powers of placement throughout the string. I have not had the time to turn this theory into practice yet.
    2. When I type a space in between 2 names ie “first second”, the program does not work correctly. I do not know why this is as yet.
Other than these 2 issues I could not find any problem with the program.
