#include <stdio.h>

int playorhistory(FILE*);					// allows user to read user history file or to play the game
void giveinfo();							// user game info
void getinfo(char*, int*);					// gets user name and seclist selection
void makeseclist(FILE*);					// create list of secret numebers if not created already
int getsecnum(FILE*, int);					// takes the line number selected by the user and returns the number at the line - the secret number
int userguess(int);							// takes and counts user guesses and returns number of guesses
void saveinfo(FILE*, char*, int, int);		// saves all required information into a file ready to be read by furture users
void reset();								// allows user to decide to play again or exit game

int main()
{
	char name[30];							// stores user name
	int restart,							// allows function to flexibly exit program or continue (1 method)
		numlist,							// stores the user selected number between 1 & 55 with reference to the secret number that will be selected
		secnum,								// stores the secret number held at the line selected by the user
		numguesses;							// stores number of user guesses
	FILE *pseclist,							// file pointer to the file of secret numbers
		 *phistory;							// file pointer to the user history file

	restart = playorhistory(phistory);		// give user option to either view user history or play the game immediately
	if(restart == 0)
		return 0;							// if the function returns a '0' then the user has chosen to end the game, so end now otherwise he has chosen to play, so continue
	giveinfo();								// function delivering information of use to the user
	getinfo(name, &numlist);				// function that collects and saves user information - to be used later for saving in the user history file
	makeseclist(pseclist);					// if the secret list exists already, continue, if not, create file and make list of 55 secret numbers on seperate lines. numbers between 12 and 112.
	secnum = getsecnum(pseclist, numlist);	// select a number from the list dependant on which line the user has selected to choose it from
//	test	printf("test name... %s\n", name); // works
//	test	printf("test number... %d\n", numlist); // works
//	test	printf("%i\n", secnum); // works
	numguesses = userguess(secnum);			// allow user to guess the number, counting the guesses and informing user when they predict high, low or guess correctly. Count the number of guesses and return that int.
//	test	printf("Number of guesses was %d.\n", numguesses); // works
	saveinfo(phistory, name, numlist, numguesses);	// save the user information to the history file. Create if it doesnt exist
	reset();								// After the game has ended, ask the user if they wish to end the game or play again
}

int playorhistory(FILE *phistory)
{
	int option,
		restart;
	char content[60];						// Allow the user up to 60 chars to enter their name

	printf("\nPlease enter '1' if you would like to play the game.\nEnter '2' if you would like to review the game history\n");
	scanf(" %i", &option);
	while( (option != 1) && (option != 2) ){	// do not allow program to pass this point until the user has entered the correct number
		printf("That was not a valid selection, please enter '1', or '2'...\n");
		scanf(" %i", &option);
	}
	if(option == 2){						// if the user would like to view game history, open game history
		phistory = fopen("userhistory.txt", "a+");
		if(phistory == NULL){
			printf("Failure in opening 'history.txt'");
			exit(1);
		}
		rewind(phistory);					// take pointer to beginning of file
		if(getc(phistory) == EOF){			// if at the beginning of the file the first value is 'EOF', then the file is new and empty, so there is no history
			printf("There is no history of this game having being played saved in this location.\nEnter '1' to play the game, or '2' to exit..."); // give user option to play immediately or exit
			scanf(" %i", &restart);
			while( (restart != 1) && (restart != 2) ){ // test for required values
				printf("That was not a valid selection, please enter '1', or '2'...\n");
				scanf(" %i", &restart);
				if(restart == 2)
					return 0; // if user selected to exit then return 0 which will in turn end program in main
				else
					return 1; // if user wants to play game, return 1. This will allow main to continue through and for the game to continue
			}
		}
		else{ // if EOF is not the first value, then there must be some history saved
			rewind(phistory); // take pointer to beginning of file in preparation to read user history
			while(fgets(content, 60, phistory) != NULL) // test so that while the line of txt does not carry the NULL value to copy the content and save it under the char array of 'content'
				printf("%s", content); // print on the screen, the value of content and repeat until value of line is equal to NULL
				printf("Would you now like to play the game? If so, enter '1', if you wish to exit, enter '2'...\n");
				scanf(" %i", &restart);
			while( (restart != 1) && (restart != 2) ){
				printf("That was not a valid selection, please enter '1', or '2'...\n");
				scanf(" %i", &restart);
			}
		if(restart == 2)
			return 0;
		else
			return 1;
		}
	}
	else
		return 1;
}

void giveinfo()
{
	printf("The aim of this game is to guess the secret number\nin as little attempts as possible... good luck.\n"); // give user basic game information
}

void getinfo(char *name, int *numlist) // return values below to the addresses here
{
	printf("Enter you name...\n");
	scanf(" %s", name);
	printf("Enter a number between 1 and 55 to select the secret number\n");
	scanf(" %i", numlist);
	while( ( ("%i", *numlist) < 1) || ( ("%i", *numlist) > 55) ){
		printf("Please only 1 - 55...\n");
		scanf("%i", numlist);
	}
}

void makeseclist(FILE *pseclist)
{
	int i,
		secnum;

	pseclist = fopen("numbers.txt", "a+");
	if(pseclist == NULL){
		printf("Failure in opening 'numbers.txt'");
		exit(1);
	}
	fseek(pseclist, 0, SEEK_SET); // Another method of returning pointer to beginning of file (eg. rewind)
	if(getc(pseclist) == EOF) // test to see if file is empty or not, if it is, then carry out following...
	for(i = 0; i < 55; i++){ // do following 55 times
		secnum = (rand()%(100)) + 12; // select a random number between 0 and 100 inclusive and then add 12 to it to create 55 numbers between 12 and 112
		fprintf(pseclist, "%d\n", secnum); // print to file the number and insert a newline as well ready for the next number
	}
	if(fclose(pseclist) != 0)
		printf("Cannot close file");
}

int getsecnum(FILE *pseclist, int numlist) // at this stage, the secret number list will exist under the file name numbers.txt
{
	int secnum,
		i;

	pseclist = fopen("numbers.txt", "r");
	if(pseclist == NULL){
		printf("Failure in opening 'numbers.txt'");
		exit(1);
	}
	for(i = 0; i < numlist; i++) // carry out the following until the line number that the user requested (-1, but starting at 0 so equivalent) is reached
		fscanf(pseclist, "%i", &secnum); // every secret number on that line is saved under secnum but the last one to be saved is the one that we require by the user
//																							test	printf("%i\n", secnum);
	if(fclose(pseclist) != 0)
		printf("Cannot close 'numbers.txt'");
	return secnum; // return the secret number to be found
}

int userguess(int secnum)
{
	int guess = 0,
		numguesses = 1; // if the user guesses first time then this number will be saved as number of guesses, therefore must be 1.

	while(guess != secnum){ // if guess is incorrect then request guess 
		printf("Enter your guess...\n");
		scanf(" %i", &guess);
		if(guess < secnum){ // if guess is low, inform user
			printf("Your guess was too low, try a higher number...\n");
			numguesses++; // if guess was low add 1 to number of guesses
		}
		if(guess > secnum){ // if guess was high inform user
			printf("Your guess was too high, try a lower number...\n");
			numguesses++; // and add 1 to number of guesses
		}
	} // if guess was correct skip both if statements, do not add 1 and inform user of correct guess
	if(numguesses == 1)
		printf("You are too lucky!! You took %i guess!!\n", numguesses);
	if(numguesses == 2 || numguesses == 3)
		printf("Excellent! You took %i guesses.\n", numguesses);
	if(numguesses == 4 || numguesses == 5)
		printf("Good. You took %i guesses.\n", numguesses);
	if(numguesses > 5)
		printf("OK. You took %i guesses.\n", numguesses);
	return numguesses; // return the number of guesses so that this can be saved in user history
}

void saveinfo(FILE *phistory, char *name, int numlist, int numguesses) // input all info that history file is to contain including the file pointer of course...
{
	phistory = fopen("userhistory.txt", "a+"); // create/ open and append history file
	if(phistory == NULL){
		printf("Failure in opening 'history.txt'");
		exit(1);
	}
	fprintf(phistory, "USER NAME: %s\n", name); // print to file user name
	fprintf(phistory, "NUMBER SELECTED: %i\n", numlist); // print to file the line number on which the secret number this user chose
	fprintf(phistory, "NO. OF GUESSES: %i\n\n", numguesses); // print to file the number of guesses it took the user to guess correctly
	if(fclose(phistory) != 0)
		printf("Cannot close 'history.txt'");
}

void reset()
{
	int end;

	printf("Do you wish to restart this game or exit?\nEnter '1' to restart, or '2' to exit...\n"); // ask user if he wishes to play again or exit
	scanf(" %d", &end);
	if(end == 1)
		main();
	else
		exit(0); // if user selects exit, exit here without error
}
