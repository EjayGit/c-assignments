#include <stdio.h>
#include <sys/stat.h> // Contains the stat structure
#include <string.h> // Contains functions dealing with strings
#include <ctype.h> // Used for toupper function
#include <time.h>
#include <math.h>
#include <stdlib.h>

struct account{ //Declaring the needed structure
	char accno[20]; 
	char name[30];
	char dob[20];
	char ads[100];
	char tel[20];	
	char id[20]; // ID type: Passport, ID Card, Driving Licence
	char idno[20]; // ID Number
	int accst; //For blocked (0), for Active (1)
	double bal; // For Account balance
	char other[300];
	int pstat; // For acounts per person
};

struct statistics{ // Used to store statistics information
	int tstat; //For total number of accounts
	int custno; // For number of customers
};

struct date{
	int day;
	int month;
	int year;
};

struct loanacc
{
	char accountno[20];
	int loanno;
	double loanamount;
	char payday[20];
	struct date startdate;
	struct date enddate;
	int duration;
	float apr;
	float monthlyrepayment;
	float totalrepayment;
};

struct depdraw{ 
	char sortfm[20];
	char acctfm[20];
	char nametfm[30];
	double amount;
	char sortto[20];
	char accto[20];
	char ref[30];
	char date[20];
};

struct loantransfer{
	int sortfrom;
	char accountfrom[20];
	char name[50];
	double balance;
	char accountto[20];
	int loanselectto;
	char reference[100];
	struct date paydate;
};

struct loancheque{
	int sortfrom;
	char accountfrom[20];
	char name[50];
	double balance;
	char accountto[20];
	int loanselectto;
	char reference[100];
	struct date paydate;
};

struct loancash{
	char name[50];
	double balance;
	char accountto[20];
	int loanselectto;
	char reference[100];
	struct date paydate;
};

struct inttfr{
	char acctfm[20];
	double amount;
	char accto[20];
	char ref[30];
	char date[8];
};

struct dirdeb{
    char nametfm[30];
	char acctfm[20];
	char sortto[20];
	char acctto[20];
	char startdate[20];
	char enddate[20];
	char payday[20];
	double amount;
	char ref[30];
	char date[8];
};

void startup();					// creates any files that do not already exist, that the program requires
void populate();				// populates essential information files for use by the program, only shows up if population os essential files has not already been carried out
void mainmenu();				// first user menu, select between 3 main parts of program
void usermanual();				// Prints basic program information and instructions for user
void entermanagement();			// asks user to enter password
void management();				// allows user to select between the management options
void statistics();				// allows user to select which statistic to view
int nofcus();					// returns number of cunstomers
int nofstruct(int);				// returns number of structures in file (input: 1 = accounts file; 2 = loans file; 3 = deposit transfers file; 4 = deposit cheque file 5 = deposit cash file; 6 = withdrawal transfer file; 7 = withdrawal cash file; 8 = loan transfer payments file; 9 = loan cheque payments file; 10 = loan cash payments file; 11 = internal transfers file; 12 = direct debits file; 13 = temporary accounts file; 14 = temporary loan file; 15 = temporary direct debits file.
float avgcusacct();				// average accounts per customer
double avgbal();				// average balance across all accounts
void loanacct();				// view all loan histories for any chosen account
double totloaned();				// total loaned out at time of selection
double totdep();				// total deposits made
double totdraw();				// total withdrawals made
int checkacctnum(char[]);		// returns 0 if account exists, returns 1 if account does not exist and 2 for file handling error.
int viewstruct(int, char[]);	// return of 0 = account printed; return of 1 = account not found; return of 2 = file handling error (stated to user before exit)
void delacct();					// directs the deletion of an account
int	delaccount(char[]);			// deletes the account via transferring non selected acoutns to temp accoutns file, trunicating accoutns file and re-writing all accoutns back into it.
int	delloan(char[]);			// deletes all loans relating to accoutn number entered
int	deldirdeb(char[]);			// deletes all direct debits relating to accoutn number entered
int decnumcus(char[]);			// returns the number of accounts that the selected account holder holds
void deccustno();				// reduces the statistic 'number of customers' by 1.
void managevalues();			// change aprs, acct status' and del accts
void bankmode();				// enter bank mode
void add(struct account, struct statistics); // Adds accounts with all necessary information and statistics information
void amend(struct account); // Amends the information of a particular account
void addamend(); // Creates a menu for Bankmode
char uppercase(char[]); // Converts strings to uppercase
void depmenu(); // Creates the main menu
void submdep(); // Creates a submenu for deposits
void submwith(); // Creates a submenu for withdrawals
void depdraw(int); // Does the deposits and withdrawals
void checkdep(); // Shows all records of deposits/withdrawals for a certain account number
void transmenu();
void inttrans();
void dirdeb();
int checkacctstat(char[]); // returns 1 if inputted account number is blocked, returns 0 if active.
void view();
void viewinttfr(char[]);
void viewdirdeb(char[]);
void viewdeptfr(char[]);
void viewdepchq(char[]);
void viewdepcsh(char[]);
void viewwithtfr(char[]);
void viewwithcsh(char[]);
void loan();
void applyloan(char []);
void gettime(struct date*);
void payback();
void lntransfer();
void lncheque();
void lncash();
 
void main()
{
	system("cls");
	startup();
	populate();
	mainmenu();
}

void startup()
{
	FILE *pstartup;
	
	pstartup = fopen("management", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'management' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close'management' file");
	pstartup = fopen("statistics", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'statistics' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close'statistics' file");
	pstartup = fopen("accounts", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'accounts' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'accounts' file");
	pstartup = fopen("deptfr", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'deptfr' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'deptfr' file");
	pstartup = fopen("depchq", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'depchq' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'depchq' file");
	pstartup = fopen("depcsh", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'depcsh' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'depcsh' file");
	pstartup = fopen("drawtfr", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'drawtfr' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'drawtfr' file");
	pstartup = fopen("drawcsh", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'drawcsh' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'drawcsh' file");
	pstartup = fopen("loan", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loan' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loan' file");
	pstartup = fopen("loantfr", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loantfr' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loantfr' file");
	pstartup = fopen("loanchq", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loanchq' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loanchq' file");
	pstartup = fopen("loancsh", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loancsh' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loancsh' file");
	pstartup = fopen("inttfr", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'inttfr' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'inttfr' file");
	pstartup = fopen("dirdeb", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'dirdeb' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'dirdeb' file");
	pstartup = fopen("loan1", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loan1' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loan1' file");
	pstartup = fopen("loan3", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loan3' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loan3' file");
	pstartup = fopen("loan5", "a+");
	if(pstartup == NULL){
		printf("ERROR: 'loan5' data file");
		exit(1);
	}
	if(fclose(pstartup) != 0)
		printf("Cannot close 'loan5' file");
}

void populate()
{
	FILE *ppopulate;
	char password[20];
	float apr = 0.0;
	
	ppopulate = fopen("management", "r+");
	if(ppopulate == NULL){
		printf("ERROR: 'management' data file");
		exit(1);
	}
	rewind(ppopulate);
	if(getc(ppopulate) == EOF){
		printf("\n Management have not set a password. They must set one now...\n\n Please enter a password (maximum 20 characters)...\n\n");
		scanf(" %s", &password);
		system("cls");
		fwrite(&password, sizeof(password), 1, ppopulate);
	}
	if(fclose(ppopulate) != 0)
		printf("Cannot close 'management' file");

	ppopulate = fopen("loan1", "r+");
	if(ppopulate == NULL){
		printf("ERROR: 'loan1' data file");
		exit(1);
	}
	rewind(ppopulate);
	if(getc(ppopulate) == EOF){
		printf("\n Management have not set an APR for the 1 year loan. They must set one now...\n Please enter the APR for a 1 year loan (e.g. '15.5')...\n\n");
		scanf(" %f", &apr);
		system("cls");
		fwrite(&apr, sizeof(apr), 1, ppopulate);
	}
	if(fclose(ppopulate) != 0)
		printf("Cannot close 'loan1' file");
	
	ppopulate = fopen("loan3", "r+");
	if(ppopulate == NULL){
		printf("ERROR: 'loan3' data file");
		exit(1);
	}
	rewind(ppopulate);
	if(getc(ppopulate) == EOF){
		printf("\n Management have not set an APR for the 3 year loan. They must set one now...\n Please enter the APR for a 3 year loan (e.g. '15.5')...\n\n");
		scanf(" %f", &apr);
		system("cls");
		fwrite(&apr, sizeof(apr), 1, ppopulate);
	}
	if(fclose(ppopulate) != 0)
		printf("Cannot close 'loan3' file");
	
	ppopulate = fopen("loan5", "r+");
	if(ppopulate == NULL){
		printf("ERROR: 'loan5' data file");
		exit(1);
	}
	rewind(ppopulate);
	if(getc(ppopulate) == EOF){
		printf("\n Management have not set an APR for the 5 year loan. They must set one now...\n Please enter the APR for a 5 year loan (e.g. '15.5')...\n\n");
		scanf(" %f", &apr);
		system("cls");
		fwrite(&apr, sizeof(apr), 1, ppopulate);
	}
	if(fclose(ppopulate) != 0)
		printf("Cannot close 'loan5' file");
}

void mainmenu() // MAIN MENU
{
	int mainmenu = 0;
	
	system("cls");
	printf("\n Welcome to HSBC© (HONG SOFIA BERMUDEZ CLARK)\n\n Group 6:\n - ERIK CLARK\n - MAURICIO RAMIREZ\n - WEE HONG FONG\n - CHRISTIAN RADEV\n - JAMES EARLY\n\n Please select from the following options... Enter:\n\n 1 - USER MANUAL\n\n 2 - MANAGEMENT (Password Protected)\n\n 3 - BANK MENU\n\n");
	scanf(" %d", &mainmenu);
	while( mainmenu < 1 || mainmenu > 3 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - USER MANUAL\n\n 2 - MANAGEMENT (Password Protected)\n\n 3 - BANK MENU\n\n");
		scanf(" %d", &mainmenu);
	}
	if(mainmenu == 1)
		usermanual();
	if(mainmenu == 2)
		entermanagement();
	if(mainmenu == 3)
		bankmode();
}

void usermanual()
{
	system("cls");
	printf("\n USERMANUAL\n\n Welcome to the banking system user manual. This manual will take you through a step by step user guide as to what options are open to you and a brief overview as to how it works.\n\n");
	printf(" Upon starting for the first time in any folder, the program will check for certain files that it requires If these files do not exist then it will create them and ask the user for information that it will require to be able to carry out all functions within the system. The information it may require on startup should be entered by management. The files that are required could be moved into the same folder as where the program lies and this means that the management password and all history of previous use can be accessed and used. The main menu allows any user to select between 3 options, 1 being to view this usermanual (so congratulations for getting this far), 2 for management options and 3 to enter the main banking system. Management options by this stage are protected by a password that management would have entered on startup. The banking system part of the program will take you down further options to deal with the banks daily routine requirements, loans, withdrawals, etc.\n\n\n");
	printf("\n BANKING SYSTEM\n\n\n MANAGEMENT SYSTEM\n\n The management system allows a user with the management password a set of unique options. Firstly, this allows the user to reset the password and reset new APR values for the 1, 3 and 5 year loan options. Furthermore, the management have a range of statistics open to them ranging from viewing the number of accounts with the bank to the amount of money held by the bank at the time of request. When the user exits this system, to re-enter, the password will be required.\n\n");
	printf(" ACCOUNTS\n\n When adding account there are 3 options new accounts can be added, accounts can be amended and the account information checked. When adding the accounts the function will add all of the information into the account and save it making the account active and giving the user a generated account number based on the number of accounts currently in the banking system, setting the sort code to that of our bank. When amending an account all aspects can be amended. When viewing an account all information is shown. To delete an account please refer to the management section of the user manual.\n\n");
	printf(" DEPOSITS AND WITHDRAWALS\n\n There are two options in the withdrawals and deposits menu, withdrawing and depositing. When depositing money it can be done by bank transfer, cheque or cash. When withdrawing money it can be done by bank transfer or cash. When viewing the withdrawals and deposits it is done historically and it shows all of the withdrawals or deposits. All that is needed is account numbers for these options to work.\n\n");
	printf(" LOANS\n\n The loan program main menu will have 2 selections to choose from, loan application and loan payback. The loan application will prompt you to fill out all the require information to create a loan. Once it has all the information, the program will ask for your confirmation and proceed to create a loan account and save it in “loan” file. The loan payback section will have payback menu with the selections of 3 different methods. The payback section will consists of payback options of bank transfer, cheque and cash. Each of the payback functions will then prompt user to enter all the information require for the loan payback and the loan payback will save in 3 separate files for bank transfer, cheque and cash respectively. The loan program will only allow active user to access its facilities. The program will allow the active user to apply for loans and deposit money to pay off their loan account. The loan application will consist of different apr 1 year, 3 years and 5 years options for repayment that was set by the bank management team. The loan payback will provide three methods of payment to pay off the loan.\n\n");
	printf(" TRANSFERS AND DIRECT DEBITS\n\n There are two options in the transfer menu transfers between accounts and direct debits. When making these transfers and direct debits these functions amend the accounts that have already been created by adding transfer and direct debit information to them, in the case of making a transfer, money is taken away from the account paying and added to the account being paid. For the direct debits the information is saved for later use and reference. When viewing transfers and direct debits they are all viewed historically so the view option will show all of the payments made by a particular account.\n\n");
	printf("\n\n Enter any key to return to the MAIN MENU\n");
	getch();
	mainmenu();
}

void entermanagement() // PASSWORD
{
	FILE *pentermanagement;
	char userword[20],
		 password[20];
	int reselect = 0;
	
	printf(" Please enter the password ->");
	scanf(" %s", &userword);
	pentermanagement = fopen("management", "r");
	if(pentermanagement == NULL){
		printf("\n ERROR: unable to verify password\n");
		mainmenu();
	}
	rewind(pentermanagement);
	fread(&password, sizeof(password), 1, pentermanagement);
	if(fclose(pentermanagement) != 0)
		printf("Cannot close 'management' file");
	if(memcmp(password, userword, strlen(password)) == 0)
		management();
	while( (reselect < 1) || (reselect > 2) ){
		printf("\n Incorrect password. Would you like to try again?\n\n 1. Yes\n\n 2. Return to MAIN MENU\n");
		scanf(" %d", &reselect);
		if( (reselect < 1) || (reselect > 2) ){
			printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1. Retry password\n\n 2. Return to MAIN MENU\n");
			scanf(" %d", &reselect);
		}
	}
	if(reselect == 2)
		mainmenu();
	else
		entermanagement();
}

void management() // MANAGEMENT MENU
{
	int firstsel = 0;

	system("cls");
	printf("\n Welcome. Would you like to:\n\n 1 - View STATISTICS\n\n 2 - APRs, ACCOUNT STATUS and DELETE ACCOUNT MENU\n\n 3 - Return to MAIN MENU\n");
	scanf(" %d", &firstsel);
	while( (firstsel < 1) || (firstsel > 3) ){
			printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - View STATISTICS\n\n 2 - Change APRs and ACCOUNT STATUS'\n\n 3 - Return to MAIN MENU\n");
			scanf(" %d", &firstsel);
	}
	if(firstsel == 1)
		statistics();
	if(firstsel == 2)
		managevalues();
	else
		mainmenu();
}

void statistics()// STATISTICS MENU
{
	int statsel = 0,
		numint = 0;
	double numdouble = 0.0;
	float numfloat = 0.0;

	system("cls");
	printf("Select which statistics you would like to know... Enter:\n\n 1. Number of customers\n\n 2. Number of Accounts\n\n 3. Average number of accounts per customer\n\n 4. Average account balance\n\n 5. Loan information for an account\n\n 6. Total loaned\n\n 7. Average loan\n\n 8. Total deposits made\n\n 9. Total withdrawals made\n\n 10. Return to MANAGEMENT MENU\n\n");
	scanf(" %d", &statsel);
	while( (statsel < 1) || (statsel > 10) ){
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1. Number of customers\n\n 2. Number of Accounts\n\n 3. Average number of accounts per customer\n\n 4. Average account balance\n\n 5. Loan information for an account\n\n 6. Total loaned\n\n 7. Average loan\n\n 8. Total deposits made\n\n 9. Total withdrawals made\n\n 10. Return to MANAGEMENT MENU\n\n");
		scanf(" %d", &statsel);
	}
	switch(statsel){
		case 1 :
			numint = nofcus();
			printf(" The number of customers is %d\n\n Enter any key to return to STATISTICS\n\n", numint);
			getch();
			break;
		case 2 :
			numint = nofstruct(1);
			printf(" The number of accounts is %d\n\n Enter any key to return to STATISTICS\n\n", numint);
			getch();
			break;
		case 3 :
			numfloat = avgcusacct();
			printf(" The average number of accounts per customer is %.2f\n\n Enter any key to return to STATISTICS\n\n", numfloat);
			getch();
			break;
		case 4 :
			numdouble = avgbal();
			printf(" The average balance is %.2lf\n\n Enter any key to return to STATISTICS\n\n", numdouble);
			getch();
			break;
		case 5 :
			loanacct();
			break;
		case 6 :
			numdouble = totloaned();
			printf(" The total amount currently loaned out is %.2lf GBP.\n\n Enter any key to return to STATISTICS.", numdouble);
			getch();
			break;
		case 7 :
			numdouble = totloaned();
			numdouble = numdouble/nofstruct(2);
			printf(" The average loan is %.2lf GBP.\n\n Enter any key to return to STATISTICS.", numdouble);
			getch();
			break;
		case 8 :
			numdouble = totdep();
			printf(" Total deposits are %.2lf GBP.\n\n Enter any key to return to STATISTICS.", numdouble);
			getch();
			break;
		case 9 :
			numdouble = totdraw();
			printf(" Total withdrawals are %.2lf GBP.\n\n Enter any key to return to STATISTICS.", numdouble);
			getch();
			break;
		case 10 :
			break;
		default :
			break;
	}
	management();
}

int nofcus()
{
	FILE *pnofcus;
	struct statistics stats;

	pnofcus = fopen("statistics", "r");

	fread (&stats, sizeof(struct statistics), 1, pnofcus);
	return stats.custno;
}

int nofstruct(int a) // done
{
	FILE *pnofstruct;
	long lastpos;
	int numberof = -1;
	
	if(a == 1){
		pnofstruct = fopen("accounts", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'accounts' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 2){
		pnofstruct = fopen("loan", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'loan' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 3){
		pnofstruct = fopen("deptfr", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'deptfr' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 4){
		pnofstruct = fopen("depchq", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'depchq' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 5){
		pnofstruct = fopen("depcsh", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'depcsh' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 6){
		pnofstruct = fopen("drawtfr", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'drawtfr' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 7){
		pnofstruct = fopen("drawcsh", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'drawcsh' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 8){
		pnofstruct = fopen("loantfr", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'loantfr' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 9){
		pnofstruct = fopen("loanchq", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'loanchq' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 10){
		pnofstruct = fopen("loancsh", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'loancsh' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 11){
		pnofstruct = fopen("inttfr", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'inttfr' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 12){
		pnofstruct = fopen("dirdeb", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'dirdeb' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 13){
		pnofstruct = fopen("tempaccounts", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'tempaccounts' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 14){
		pnofstruct = fopen("temploan", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'temploan' data file... Enter any key to continue");
			getch();
		}
	}
	if(a == 15){
		pnofstruct = fopen("tempdirdeb", "r");
		if(pnofstruct == NULL){
			printf("ERROR: 'tempdirdeb' data file... Enter any key to continue");
			getch();
			}
	}
	fseek(pnofstruct, 0, SEEK_END);
	lastpos = ftell(pnofstruct);
	if(a == 1)
		numberof = lastpos/(sizeof(struct account));
	if(a == 2)
		numberof = lastpos/(sizeof(struct loanacc));	
	if(a == 3)
		numberof = lastpos/(sizeof(struct depdraw));	
	if(a == 4)
		numberof = lastpos/(sizeof(struct depdraw));	
	if(a == 5)
		numberof = lastpos/(sizeof(struct depdraw));	
	if(a == 6)
		numberof = lastpos/(sizeof(struct depdraw));	
	if(a == 7)
		numberof = lastpos/(sizeof(struct depdraw));	
	if(a == 8)
		numberof = lastpos/(sizeof(struct loantransfer));	
	if(a == 9)
		numberof = lastpos/(sizeof(struct loancheque));	
	if(a == 10)
		numberof = lastpos/(sizeof(struct loancash));	
	if(a == 11)
		numberof = lastpos/(sizeof(struct inttfr));	
	if(a == 12)
		numberof = lastpos/(sizeof(struct dirdeb));	
	if(a == 13)
		numberof = lastpos/(sizeof(struct account));	
	if(a == 14)
		numberof = lastpos/(sizeof(struct loanacc));	
	if(a == 15)
		numberof = lastpos/(sizeof(struct dirdeb));	
	if(fclose(pnofstruct) != 0){
		printf("Cannot close data file");
		getch();
	}
	return numberof;
}

float avgcusacct() // done
{
	float numberaccts = 1.1;
			  
	numberaccts = ((float)(nofstruct(1)))/(nofcus()); //(this will give the average number of accounts per customer)
	return numberaccts;
}

double avgbal() // done
{
	FILE *pavgbal;
	int i = 0;
	double total = 0.0;
	struct account avgbal;

	pavgbal = fopen("accounts", "r");
	if(pavgbal == NULL){
		printf("ERROR: 'accounts' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(pavgbal);
	for(i = 0; i < (nofstruct(1)); i++){
		fseek(pavgbal, sizeof(struct account)*i, SEEK_SET);
		fread(&avgbal, sizeof(struct account), 1, pavgbal);
		total = total + avgbal.bal;
	}
	if(fclose(pavgbal) != 0)
		printf("Cannot close 'accounts' file");
	total = total/(nofstruct(1));
	return total;
}

void loanacct() // done
{
	int ch = 0,
		reenter = 0;
	char findacct[20];

	system("cls");
	printf(" Enter loan ACCOUNT NUMBER:\n\n ");
	fflush (stdin);
	fgets (findacct, sizeof(findacct), stdin);
	strtok (findacct, "\n");
	while(checkacctnum(findacct) == 1){
		printf(" That account number does not exist on our records. Would you like to enter a different number? Enter:\n\n 1 - YES\n\n 2 - NO. Return to VIEW\n\n");
		scanf(" %d", &reenter);
		while(reenter < 1 || reenter > 2){
			printf(" That entry was incorrect, please enter 1 - Re-enter account number\n\n 2 - Return to VIEW\n\n");
			scanf(" %d", &reenter);
		}
		if(reenter == 2)
			transmenu();
		else{
			fflush (stdin);
			fgets (findacct, sizeof(findacct), stdin);
			strtok (findacct, "\n");
		}
	}
	viewstruct(2, findacct);
	printf(" Enter any key to return to STATISTICS...");
	getch();
	statistics();
}

double totloaned() // done
{
	FILE *ptotloaned;
	int i = 0;
	double total = 0.0;
	struct loanacc record;

	ptotloaned = fopen("loan", "r");
	if(ptotloaned == NULL){
		printf("ERROR: 'loan' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(ptotloaned);
	for(i = 0; i < (nofstruct(2)); i++){
		fseek(ptotloaned, sizeof(struct loanacc)*i, SEEK_SET);
		fread(&record, sizeof(struct loanacc), 1, ptotloaned);
		total = total + record.loanamount;
	}
	if(fclose(ptotloaned) != 0)
		printf("Cannot close 'loan' file");
	return total;
}

double totdep() // done
{
	FILE *ptotdep;
	int i = 0;
	double total = 0.0;
	struct depdraw dtransfer;
	struct depdraw dcheque;
	struct depdraw dcash;

	ptotdep = fopen("deptfr", "r");
	if(ptotdep == NULL){
		printf("ERROR: 'deptfr' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(ptotdep);
	for(i = 0; i < (nofstruct(3)); i++){
		fseek(ptotdep, sizeof(struct depdraw)*i, SEEK_SET);
		fread(&dtransfer, sizeof(struct depdraw), 1, ptotdep);
		total = dtransfer.amount;
	}
	if(fclose(ptotdep) != 0)
		printf("Cannot close 'deptfr' file");
	ptotdep = fopen("depchq", "r");
	if(ptotdep == NULL){
		printf("ERROR: 'depchq' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(ptotdep);
	for(i = 0; i < (nofstruct(4)); i++){
		fseek(ptotdep, sizeof(struct depdraw)*i, SEEK_SET);
		fread(&dcheque, sizeof(struct depdraw), 1, ptotdep);
		total = total + dcheque.amount;
	}
	if(fclose(ptotdep) != 0)
		printf("Cannot close 'depchq' file");
	ptotdep = fopen("depcsh", "r");
	if(ptotdep == NULL){
		printf("ERROR: 'depcsh' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(ptotdep);
	for(i = 0; i < (nofstruct(5)); i++){
		fseek(ptotdep, sizeof(struct depdraw)*i, SEEK_SET);
		fread(&dcash, sizeof(struct depdraw), 1, ptotdep);
		total = total + dcash.amount;
	}
	if(fclose(ptotdep) != 0)
		printf("Cannot close 'depcsh' file");
	return total;
}

double totdraw() // done
{
	FILE *ptotdraw;
	int i = 0;
	double total = 0.0;
	struct depdraw wtransfer;
	struct depdraw wcash;

	ptotdraw = fopen("drawtfr", "r");
	if(ptotdraw == NULL){
		printf("ERROR: 'drawtfr' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(ptotdraw);
	for(i = 0; i < (nofstruct(6)); i++){
		fseek(ptotdraw, sizeof(struct depdraw)*i, SEEK_SET);
		fread(&wtransfer, sizeof(struct depdraw), 1, ptotdraw);
		total = wtransfer.amount;
	}
	if(fclose(ptotdraw) != 0)
		printf("Cannot close 'drawtfr' file");
	ptotdraw = fopen("drawcsh", "r");
	if(ptotdraw == NULL){
		printf("ERROR: 'drawcsh' data file... Enter any key to return to STATISTICS");
		getch();
		statistics();
	}
	rewind(ptotdraw);
	for(i = 0; i < (nofstruct(7)); i++){
		fseek(ptotdraw, sizeof(struct depdraw)*i, SEEK_SET);
		fread(&wcash, sizeof(struct depdraw), 1, ptotdraw);
		total = total + wcash.amount;
	}
	if(fclose(ptotdraw) != 0)
		printf("Cannot close 'drawcsh' file");
	return total;
}

int checkacctnum(char findacct[20])// return of 0 = account exists; return of 1 = file doesn't exist; return of 2 = file handling error (stated to user before exit)
{
	FILE *pcheckacctnum;
	int i = 0;
	struct account ckacct;

	pcheckacctnum = fopen("accounts", "r");
	if(pcheckacctnum == NULL){
		printf("ERROR: opening 'accounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(1)); i++){
		fseek(pcheckacctnum, sizeof(struct account)*i, SEEK_SET);
		fread(&ckacct, sizeof(struct account), 1, pcheckacctnum);
		if(memcmp(findacct, ckacct.accno, strlen(ckacct.accno)) == 0){
			if(fclose(pcheckacctnum) != 0){
				printf("ERROR: closing 'accounts' data file... Enter any key to continue...");
				getch();
				return 2;
			}
			return 0;
		}
		else
			continue;
	}
	if(fclose(pcheckacctnum) != 0){
		printf("ERROR: closing 'accounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	return 1;
}

int viewstruct(int a, char findacct[20]) // return of 0 = account printed; return of 1 = account not found; return of 2 = file handling error (stated to user before exit)
{
	FILE *pviewstruct;
	int i = 0,
		match = 0;
	struct account acct;
	struct loanacc loan;
	struct depdraw dtfr;
	struct depdraw dchq;
	struct depdraw dcsh;
	struct depdraw wtfr;
	struct depdraw wcsh;
	struct loantransfer ltfr;
	struct loancheque lchq;
	struct loancash lcsh;
	struct inttfr itfr; // will only show records whose account transaction were taken from
	struct dirdeb ddeb;
	
	if(a == 1){// ACCOUNT
		pviewstruct = fopen("accounts", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'accounts' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(1)); i++){
			fseek(pviewstruct, sizeof(struct account)*i, SEEK_SET);
			fread(&acct, sizeof(struct account), 1, pviewstruct);
			if(memcmp(findacct, acct.accno, strlen(acct.accno)) == 0){
				printf("\n\n ACCOUNT INFORMATION\n\n");
				printf(" ACCOUNT NUMBER: %s\n", acct.accno);
				printf(" NAME: %s\n", acct.name);
				printf(" DATE OF BIRTH: %s\n", acct.dob);
				printf(" ADDRESS: %s\n", acct.ads);
				printf(" CONTACT NUMBER: %s\n", acct.tel);
				printf(" ID TYPE: %s\n", acct.id);
				printf(" ID NUMBER: %s\n", acct.idno);
				if(acct.accst == 0)
					printf(" ACCOUNT: BLOCKED\n");
				if(acct.accst == 1)
					printf(" ACCOUNT: ACTIVE\n");
				printf(" ACCOUNT BALANCE: %.2lf GBP\n", acct.bal);
				printf(" OTHER: %s\n\n", acct.other);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find account information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'accounts' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 2){// LOAN
		pviewstruct = fopen("loan", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'loan' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(2)); i++){
			fseek(pviewstruct, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&loan, sizeof(struct loanacc), 1, pviewstruct);
			if(memcmp(findacct, loan.accountno, strlen(loan.accountno)) == 0){
				printf("\n\n LOAN INFORMATION\n\n");
				printf(" ACCOUNT NUMBER: %s\n", loan.accountno);
				printf(" LOAN NUMBER: %d\n", loan.loanno);
				printf(" BALANCE: %.2lf GBP\n", loan.loanamount);
				printf(" INSTALMENTS DUE: %s OF MONTH\n", loan.payday);
				printf(" START DATE: %d %d %d\n", loan.startdate.day, loan.startdate.month, loan.startdate.year);
				printf(" END DATE: %d %d %d\n", loan.enddate.day, loan.enddate.month, loan.enddate.year);
				printf(" TERM: %d YEARS\n", loan.duration);
				printf(" APR: %.2f PER CENT\n", loan.apr);
				printf(" MONTHLY REPAYMENT: %.2f GBP\n", loan.monthlyrepayment);
				printf(" TOTAL REPAYMENT: %.2f GBP\n\n", loan.totalrepayment);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find loan information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'loan' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 3){// DEPOSIT BY TRANSFERS
		pviewstruct = fopen("deptfr", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'deptfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(3)); i++){
			fseek(pviewstruct, sizeof(struct depdraw)*i, SEEK_SET);
			fread(&dtfr, sizeof(struct depdraw), 1, pviewstruct);
			if(memcmp(findacct, dtfr.accto, strlen(dtfr.accto)) == 0){
				printf("\n\n DEPOSIT BY TRANSFER DETAILS\n\n");
				printf(" FROM SORT CODE: %s\n", dtfr.sortfm);
				printf(" FROM ACCOUNT NUMBER: %s\n", dtfr.acctfm);
				printf(" NAME: %s\n", dtfr.nametfm);
				printf(" AMOUNT: %.2lf\n", dtfr.amount);
				printf(" INTO ACCOUNT NUMBER: %s\n", dtfr.accto);
				printf(" REFERENCE: %s\n", dtfr.ref);
				printf(" DATE: %s\n\n", dtfr.date);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find deposit transfer information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'deptfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 4){	// DEPOSIT BY CHEQUE
		pviewstruct = fopen("depchq", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'depchq' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(4)); i++){
			fseek(pviewstruct, sizeof(struct depdraw)*i, SEEK_SET);
			fread(&dchq, sizeof(struct depdraw), 1, pviewstruct);
			if(memcmp(findacct, dchq.accto, strlen(dchq.accto)) == 0){
				printf("\n\n DEPOSIT BY CHEQUE DETAILS\n\n");
				printf(" FROM SORT CODE: %s\n", dchq.sortfm);
				printf(" FROM ACCOUNT NUMBER: %s\n", dchq.acctfm);
				printf(" NAME: %s\n", dchq.nametfm);
				printf(" AMOUNT: %.2lf\n", dchq.amount);
				printf(" INTO ACCOUNT NUMBER: %s\n", dchq.accto);
				printf(" REFERENCE: %s\n", dchq.ref);
				printf(" DATE: %s\n\n", dchq.date);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find deposit cheque information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'depchq' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 5){// DEPOSIT BY CASH
		pviewstruct = fopen("depcsh", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'depcsh' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(5)); i++){
			fseek(pviewstruct, sizeof(struct depdraw)*i, SEEK_SET);
			fread(&dcsh, sizeof(struct depdraw), 1, pviewstruct);
			if(memcmp(findacct, dcsh.accto, strlen(dcsh.accto)) == 0){
				printf("\n\n DEPOSIT BY CASH DETAILS\n\n");
				printf(" NAME: %s\n", dcsh.nametfm);
				printf(" AMOUNT: %.2lf\n", dcsh.amount);
				printf(" INTO ACCOUNT NUMBER: %s\n", dcsh.accto);
				printf(" REFERENCE: %s\n", dcsh.ref);
				printf(" DATE: %s\n\n", dcsh.date);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find deposit cash information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'depcsh' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 6){// WITHDRAW BY TRANSFER
		pviewstruct = fopen("drawtfr", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'drawtfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(6)); i++){
			fseek(pviewstruct, sizeof(struct depdraw)*i, SEEK_SET);
			fread(&wtfr, sizeof(struct depdraw), 1, pviewstruct);
			if(memcmp(findacct, wtfr.acctfm, strlen(wtfr.acctfm)) == 0){
				printf("\n\n WITHDRAW BY TRANSFER INFORMATION\n\n");
				printf(" ACCOUNT NUMBER: %s\n", wtfr.acctfm);
				printf(" AMOUNT: %.2lf\n", wtfr.amount);
				printf(" OUTGOING SORT CODE: %s\n", wtfr.sortto);
				printf(" OUTGOING ACCOUNT NUMBER: %s\n", wtfr.accto);
				printf(" NAME OF RECIPIENT: %s\n", wtfr.nametfm);
				printf(" REFERENCE: %s\n", wtfr.ref);
				printf(" DATE: %s\n\n", wtfr.date);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find withdraw transfer information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'drawtfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 7){// WITHDRAW BY CASH
		pviewstruct = fopen("drawcsh", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'drawcsh' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(7)); i++){
			fseek(pviewstruct, sizeof(struct depdraw)*i, SEEK_SET);
			fread(&wcsh, sizeof(struct depdraw), 1, pviewstruct);
			if(memcmp(findacct, wcsh.acctfm, strlen(wcsh.acctfm)) == 0){
				printf("\n\n WITHDRAW BY CASH INFORMATION\n\n");
				printf(" ACCOUNT NUMBER: %s\n", wcsh.acctfm);
				printf(" NAME OF RECIPIENT: %s\n", wcsh.nametfm);
				printf(" AMOUNT: %.2lf\n", wcsh.amount);
				printf(" DATE: %s\n\n", wcsh.date);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find withdraw cash information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'drawcsh' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 8){// LOAN PAYMENT BY TRANSFER
		pviewstruct = fopen("loantfr", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'loantfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(8)); i++){
			fseek(pviewstruct, sizeof(struct loantransfer)*i, SEEK_SET);
			fread(&ltfr, sizeof(struct loantransfer), 1, pviewstruct);
			if(memcmp(findacct, ltfr.accountto, strlen(ltfr.accountto)) == 0){
				printf("\n\n LOAN PAYMENT BY TRANSFER INFORMATION\n\n");
				printf(" FROM SORT CODE: %d\n", ltfr.sortfrom);
				printf(" FROM ACCOUNT NUMBER: %s\n", ltfr.accountfrom);
				printf(" NAME OF PAYER: %s\n", ltfr.name);
				printf(" AMOUNT: %.2lf GBP\n", ltfr.balance);
				printf(" TO ACCOUNT NUMBER: %s\n", ltfr.accountto);
				printf(" TO LOAN NUMBER: %d\n", ltfr.loanselectto);
				printf(" REFERENCE: %s\n", ltfr.reference);
				printf(" DATE: %d %d %d\n\n", ltfr.paydate.day, ltfr.paydate.month, ltfr.paydate.year);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find loan transfer payment information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'loantfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 9){// LOAN PAYMENT BY CHEQUE
		pviewstruct = fopen("loanchq", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'loanchq' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(9)); i++){
			fseek(pviewstruct, sizeof(struct loancheque)*i, SEEK_SET);
			fread(&lchq, sizeof(struct loancheque), 1, pviewstruct);
			if(memcmp(findacct, lchq.accountto, strlen(lchq.accountto)) == 0){
				printf("\n\n LOAN PAYMENT BY CHEQUE INFORMATION\n\n");
				printf(" FROM SORT CODE: %d\n", lchq.sortfrom);
				printf(" FROM ACCOUNT NUMBER: %s\n", lchq.accountfrom);
				printf(" NAME OF PAYER: %s\n", lchq.name);
				printf(" AMOUNT: %.2lf GBP\n", lchq.balance);
				printf(" TO ACCOUNT NUMBER: %s\n", lchq.accountto);
				printf(" TO LOAN NUMBER: %d\n", lchq.loanselectto);
				printf(" REFERENCE: %s\n", lchq.reference);
				printf(" DATE: %d %d %d\n\n", lchq.paydate.day, lchq.paydate.month, lchq.paydate.year);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find loan cheque payment information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'loanchq' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 10){// LOAN PAYMENT BY CASH
		pviewstruct = fopen("loancsh", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'loancsh' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(10)); i++){
			fseek(pviewstruct, sizeof(struct loancash)*i, SEEK_SET);
			fread(&lcsh, sizeof(struct loancash), 1, pviewstruct);
			if(memcmp(findacct, lcsh.accountto, strlen(lcsh.accountto)) == 0){
				printf("\n\n LOAN PAYMENT BY CASH INFORMATION\n\n");
				printf(" NAME OF PAYER: %s\n", lcsh.name);
				printf(" AMOUNT: %.2lf GBP\n", lcsh.balance);
				printf(" TO ACCOUNT NUMBER: %s\n", lcsh.accountto);
				printf(" TO LOAN NUMBER: %d\n", lcsh.loanselectto);
				printf(" REFERENCE: %s\n", lcsh.reference);
				printf(" DATE: %d %d %d\n\n", lcsh.paydate.day, lcsh.paydate.month, lcsh.paydate.year);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find loan cash payment informtaion. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'loancsh' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 11){// INTERNAL TRANSFER
		pviewstruct = fopen("inttfr", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'inttfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(11)); i++){
			fseek(pviewstruct, sizeof(struct inttfr)*i, SEEK_SET);
			fread(&itfr, sizeof(struct inttfr), 1, pviewstruct);
			if(memcmp(findacct, itfr.acctfm, strlen(itfr.acctfm)) == 0){
				printf("\n\n INTERNAL TRANSFER INFORMATION\n\n");
				printf(" FROM ACCOUNT NUMBER: %s\n", itfr.acctfm);
				printf(" AMOUNT: %.2lf\n", itfr.amount);
				printf(" TO ACCOUNT NUMBER: %s\n", itfr.accto);
				printf(" REFERENCE: %s\n", itfr.ref);
				printf(" DATE: %s\n\n", itfr.date);
				match = 1;
			}
		}	
		if(match == 0){
			printf(" Cannot find internal transfer information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'inttfr' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
	if(a == 12){// DIRECT DEBITS
		pviewstruct = fopen("dirdeb", "r");
		if(pviewstruct == NULL){
			printf("ERROR: opening 'dirdeb' data file. Enter any key to continue...");
			getch();
			return 2;
		}
		for(i = 0; i < (nofstruct(12)); i++){
			fseek(pviewstruct, sizeof(struct dirdeb)*i, SEEK_SET);
			fread(&ddeb, sizeof(struct dirdeb), 1, pviewstruct);
			if(memcmp(findacct, ddeb.acctfm, strlen(ddeb.acctfm)) == 0){
				printf("\n\n DIRECT DEBIT INFORMATION\n\n");
				printf(" ACCOUNT NUMBER: %s\n", ddeb.acctfm);
				printf(" OUTGOING SORT CODE: %s\n", ddeb.sortto);
				printf(" OUTGOING ACCOUNT NUMBER: %s\n", ddeb.acctto);
				printf(" START DATE: %s\n", ddeb.startdate);
				printf(" END DATE: %s GBP\n", ddeb.enddate);
				printf(" PAYMENT DAY: %s OF MONTH\n", ddeb.payday);
				printf(" AMOUNT: %.2lf\n", ddeb.amount);
				printf(" REFERENCE: %s\n", ddeb.ref);
				printf(" DATE: %s\n\n", ddeb.date);
				match = 1;
			}
		}
		if(match == 0){
			printf(" Cannot find direct debit information. Press any key to continue...\n");
			getch();
			return 1;
		}
		if(match == 1){
			printf(" Press any key to return to continue\n");
			getch();
			return 0;
		}
		if(fclose(pviewstruct) != 0){
			printf("ERROR: closing 'dirdeb' data file. Enter any key to continue...");
			getch();
			return 2;
		}
	}
}

void delacct()
{
	char findacct[20];
	int	i = 0,
		confirm = 0,
		reenter = 0,
		delcus = 0;
		
	printf("\n Please enter the account number that you wish to delete... ");
	fflush (stdin);
	fgets (findacct, sizeof(findacct), stdin);
	strtok (findacct, "\n");
	while(checkacctnum(findacct) == 1){
		printf(" That account number does not exist on our records. Would you like to enter a different number? Enter:\n\n 1 - YES\n\n 2 - NO. Return to ACCOUNTS MENU\n\n");
		scanf(" %d", &reenter);
		while(reenter < 1 || reenter > 2){
			printf(" That entry was incorrect, please enter 1 - Re-enter account number\n\n 2 - Return to ACCOUNTS MENU\n\n");
			scanf(" %d", &reenter);
		}
		if(reenter == 2)
			addamend();
		else{
			fflush (stdin);
			fgets (findacct, sizeof(findacct), stdin);
			strtok (findacct, "\n");
		}
	}
	if(checkacctnum(findacct) == 2)
		managevalues();
	else{
		printf("\n The account has been found. Enter any key to view all account information...");
		getch();
		viewstruct(1, findacct);
		viewstruct(2, findacct);
		viewstruct(12, findacct);
	}
	printf(" Would you like to DELETE the ACCOUNT and all related LOANS and DIRECT DEBITS for this ACCOUNT? Enter:\n\n 1 - YES: DELETE\n\n 2 - NO: Return to APRs and ACCOUNT STATUS MENU\n");
	scanf(" %d", &confirm);
	while( (confirm < 1) || (confirm > 2) ){
				printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - YES: DELETE\n\n 2 - NO: Return to APRs and ACCOUNT STATUS MENU\n");
				scanf(" %d", &confirm);
			}
	if(confirm == 2)
		managevalues();
	else{
		confirm = 0;
		printf(" CONFIRM DELETE - THE ACCOUNT, ASSOCIATED LOANS AND DIRECT DEBITS WILL NOT BE RECOVERABLE.\n\n Enter:\n\n 1 - YES: CONFIRM DELETE\n\n 2 - NO: RETURN TO APRs AND ACCOUNT STATUS MENU\n");
		scanf(" %d", &confirm);
		while( (confirm < 1) || (confirm > 2) ){
			printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - YES: CONFIRM DELETE\n\n 2 - NO: RETURN TO APRs AND ACCOUNT STATUS MENU\n");
			scanf(" %d", &confirm);
		}
	}
	if(confirm == 2)
		managevalues();
	delcus = decnumcus(findacct);
	if(delaccount(findacct) != 0){
		printf(" Error deleting account from 'accounts' file. Enter any key to return to APRs and ACCOUNT STATUS MENU");
		getch();
		managevalues();
	}
	if(delcus == 1)
		deccustno();
	if(delloan(findacct) != 0){
		printf(" Error deleting account from 'loan' file. Enter any key to return to APRs and ACCOUNT STATUS MENU");
		getch();
		managevalues();
	}
	if(deldirdeb(findacct) != 0){
		printf(" Error deleting account from 'dirdeb' file. Enter any key to return to APRs and ACCOUNT STATUS MENU");
		getch();
		managevalues();
	}
	printf(" Successfully deleted files. Enter any key to return to APRs and ACCOUNT STATUS MENU");
	getch();
	managevalues();
}
	
int	delaccount(char findacct[20])
{
	FILE *pdelacct,
		 *ptempacct;
	int	i = 0;
	struct account acct;

	pdelacct = fopen("accounts", "r");
	if(pdelacct == NULL){
		printf("ERROR: opening 'accounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	ptempacct = fopen("tempaccounts", "w");
	if(ptempacct == NULL){
		printf("ERROR: opening 'tempaccounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(1)); i++){
		fseek(pdelacct, sizeof(struct account)*i, SEEK_SET);
		fread(&acct, sizeof(struct account), 1, pdelacct);
		if(memcmp(findacct, acct.accno, strlen(acct.accno)) != 0){
			fwrite(&acct, sizeof(struct account), 1, ptempacct);
		}
	}
	if(fclose(pdelacct) != 0){
		printf("Cannot close 'accounts' file... Enter any key to continue...");
		getch();
		return 2;
	}
	if(fclose(ptempacct) != 0){
		printf("Cannot close 'tempaccounts' file... Enter any key to continue...");
		getch();
		return 2;
	}
	pdelacct = fopen("accounts", "w");
	if(pdelacct == NULL){
		printf("ERROR: opening 'accounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	ptempacct = fopen("tempaccounts", "r");
	if(ptempacct == NULL){
		printf("ERROR: opening 'tempaccounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(13)); i++){
		fseek(ptempacct, sizeof(struct account)*i, SEEK_SET);
		fread(&acct, sizeof(struct account), 1, ptempacct);
		fwrite(&acct, sizeof(struct account), 1, pdelacct);
	}
	if(fclose(pdelacct) != 0){
		printf("Cannot close 'accounts' file... Enter any key to continue...");
		getch();
		return 2;
	}
	if(fclose(ptempacct) != 0){
		printf("Cannot close 'tempaccounts' file... Enter any key to continue...");
		getch();
		return 2;
	}
	remove("tempaccounts");
	return 0;
}

int decnumcus(char findacct[20])
{
	FILE *pdecnumcus;
	int i = 0,
		nofcus = 0;
	struct account ckacct,
		ckidno;
	
	pdecnumcus = fopen("accounts", "r");
	for(i = 0; i < nofstruct(1); i++){
		fseek(pdecnumcus, sizeof(struct account)*i, SEEK_SET);
		fread(&ckacct, sizeof(struct account), 1, pdecnumcus);
		if(memcmp(findacct, ckacct.accno, strlen(ckacct.accno)) != 0){
			for(i++; i < nofstruct(1); i++){
				fseek(pdecnumcus, sizeof(struct account)*i, SEEK_SET);
				fread(&ckidno, sizeof(struct account), 1, pdecnumcus);
				if(memcmp(ckidno.idno, ckacct.idno, strlen(ckacct.idno)) != 0){
					nofcus++;
				}
			}
			fclose(pdecnumcus);
			return nofcus;
		}
	}
	fclose(pdecnumcus);
	return nofcus;
}

void deccustno()
{
	FILE *pdeccustno;
	struct statistics stat;

	pdeccustno = fopen("statistics", "r+");
	rewind(pdeccustno);
	fread(&stat, sizeof(struct statistics), 1, pdeccustno);
	stat.custno--;
	rewind(pdeccustno);
	fwrite(&stat, sizeof(struct statistics), 1, pdeccustno);
	fclose(pdeccustno);
}

int	delloan(char findacct[20])
{
	FILE *pdelacct,
		 *ptempacct;
	int	i = 0;
	struct loanacc loan;

	pdelacct = fopen("loan", "r");
	if(pdelacct == NULL){
		printf("ERROR: opening 'loan' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	ptempacct = fopen("temploan", "w");
	if(ptempacct == NULL){
		printf("ERROR: opening 'temploan' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(2)); i++){
		fseek(pdelacct, sizeof(struct loanacc)*i, SEEK_SET);
		fread(&loan, sizeof(struct loanacc), 1, pdelacct);
		if(memcmp(findacct, loan.accountno, strlen(loan.accountno)) != 0){
			fwrite(&loan, sizeof(struct loanacc), 1, ptempacct);
		}
	}
	if(fclose(pdelacct) != 0){
		printf("Cannot close 'loan' file... Enter any key to continue...");
		getch();
		return 2;
	}
	if(fclose(ptempacct) != 0){
		printf("Cannot close 'temploan' file... Enter any key to continue...");
		getch();
		return 2;
	}
	pdelacct = fopen("loan", "w");
	if(pdelacct == NULL){
		printf("ERROR: opening 'loan' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	ptempacct = fopen("temploan", "r");
	if(ptempacct == NULL){
		printf("ERROR: opening 'temploan' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(14)); i++){
		fseek(ptempacct, sizeof(struct loanacc)*i, SEEK_SET);
		fread(&loan, sizeof(struct loanacc), 1, ptempacct);
		fwrite(&loan, sizeof(struct loanacc), 1, pdelacct);
	}
	if(fclose(pdelacct) != 0){
		printf("Cannot close 'loan' file... Enter any key to continue...");
		getch();
		return 2;
	}
	if(fclose(ptempacct) != 0){
		printf("Cannot close 'temploan' file... Enter any key to continue...");
		getch();
		return 2;
	}
	remove("temploan");
	return 0;
}
	
int	deldirdeb(char findacct[20])
{
	FILE *pdelacct,
		 *ptempacct;
	int	i = 0;
	struct dirdeb ddeb;
	
	pdelacct = fopen("dirdeb", "r");
	if(pdelacct == NULL){
		printf("ERROR: opening 'dirdeb' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	ptempacct = fopen("tempdirdeb", "w");
	if(ptempacct == NULL){
		printf("ERROR: opening 'tempdirdeb' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(12)); i++){
		fseek(pdelacct, sizeof(struct dirdeb)*i, SEEK_SET);
		fread(&ddeb, sizeof(struct dirdeb), 1, pdelacct);
		if(memcmp(findacct, ddeb.acctfm, strlen(ddeb.acctfm)) != 0){
			fwrite(&ddeb, sizeof(struct dirdeb), 1, ptempacct);
		}
	}
	if(fclose(pdelacct) != 0){
		printf("Cannot close 'dirdeb' file... Enter any key to continue...");
		getch();
		return 2;
	}
	if(fclose(ptempacct) != 0){
		printf("Cannot close 'tempdirdeb' file... Enter any key to continue...");
		getch();
		return 2;
	}
	pdelacct = fopen("dirdeb", "w");
	if(pdelacct == NULL){
		printf("ERROR: opening 'dirdeb' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	ptempacct = fopen("tempdirdeb", "r");
	if(ptempacct == NULL){
		printf("ERROR: opening 'tempdirdeb' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(15)); i++){
		fseek(ptempacct, sizeof(struct dirdeb)*i, SEEK_SET);
		fread(&ddeb, sizeof(struct dirdeb), 1, ptempacct);
		fwrite(&ddeb, sizeof(struct dirdeb), 1, pdelacct);
	}
	if(fclose(pdelacct) != 0){
		printf("Cannot close 'dirdeb' file... Enter any key to continue...");
		getch();
		return 2;
	}
	if(fclose(ptempacct) != 0){
		printf("Cannot close 'tempdirdeb' file... Enter any key to continue...");
		getch();
		return 2;
	}
	remove("tempdirdeb");
	return 0;
}

void managevalues() // APRs and ACCOUNT STATUS MENU
{
	FILE *paprstat;
	int aprstat = 0,
		i = 0,
		statsel = 0,
		retry = 1,
		term = 0;
	char findacct[20];
	float editapr = 0.0;
	struct account temp;

	printf(" Enter:\n\n 1 - Change APR\n\n 2 - Change customers account status\n\n 3 - Delete account\n\n 4 - Return to MANAGEMENT MENU\n");
	scanf(" %d", &aprstat);
	while( (aprstat < 1) || (aprstat > 4) ){
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Change APR\n\n 2 - Change customers account status\n\n 3 - Delete account\n\n 4 - Return to MANAGEMENT MENU\n");
		scanf(" %d", &aprstat);
	}
	if(aprstat == 1){
		printf("Which term of loan would you like to change? Enter:\n\n 1 - One year loan\n\n 2 - Three year loan\n\n 3 - Five year loan\n\n 4 - Return to APRs and ACCOUNT STATUS' MENU\n");
		scanf(" %d", &term);
		while( (term < 1) || (term > 4) ){
			printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - One year loan\n\n 2 - Three year loan\n\n 3 - Five year loan\n\n 4 - Return to APRs and ACCOUNT STATUS' MENU");
			scanf(" %d", &term);
		}
		if(term == 1){
			paprstat = fopen("loan1", "r+");
			if(paprstat == NULL){
				printf("ERROR: 'loan1' data file... Enter any key to return to MANAGEMENT MENU");
				getch();
				management();
			}
			printf("Enter the new APR for the 1 year loan e.g. '15.5'-> ");
			scanf(" %f", &editapr);
			rewind(paprstat);
			fwrite(&editapr, sizeof(editapr), 1, paprstat);
			if(fclose(paprstat) != 0)
				printf("Cannot close 'loan1' file\n");
			printf("The APR for the 1 year loan has been set to %.2f percent\n", editapr);
			managevalues();
		}
		if(term == 2){
			paprstat = fopen("loan3", "r+");
			if(paprstat == NULL){
				printf("ERROR: 'loan3' data file... Enter any key to return to MANAGEMENT MENU");
				getch();
				management();
			}
			printf("Enter the new APR for the 3 year loan e.g. '15.5'-> ");
			scanf(" %f", &editapr);
			rewind(paprstat);
			fwrite(&editapr, sizeof(editapr), 1, paprstat);
			if(fclose(paprstat) != 0)
				printf("Cannot close 'loan3' file\n");
			printf("The APR for the 3 year loan has been set to %.2f percent\n", editapr);
			managevalues();
		}
		if(term == 3){
			paprstat = fopen("loan5", "r+");
			if(paprstat == NULL){
				printf("ERROR: 'loan5' data file... Enter any key to return to MANAGEMENT MENU");
				getch();
				management();
			}
			printf("Enter the new APR for the 5 year loan e.g. '15.5'-> ");
			scanf(" %f", &editapr);
			rewind(paprstat);
			fwrite(&editapr, sizeof(editapr), 1, paprstat);
			if(fclose(paprstat) != 0)
				printf("Cannot close 'loan5' file\n");
			printf("The APR for the 5 year loan has been set to %.2f percent\n", editapr);
			managevalues();
		}
		if(term == 4)
			managevalues();
	}
	if(aprstat == 2){
		paprstat = fopen("accounts", "r+");
		if(paprstat == NULL){
			printf("ERROR: 'accounts' data file... Enter any key to return to MANAGEMENT MENU");
			getch();
			management();
		}
		rewind(paprstat);
		while(retry == 1){
			printf(" Type in the account number that you wish to wish to change status for ->");
			fflush (stdin);
			fgets (findacct, sizeof(findacct), stdin);
			strtok (findacct, "\n");
			for(i = 0; i < (nofstruct(1)); i++){
				fseek(paprstat, sizeof(struct account)*i, SEEK_SET);
				fread(&temp, sizeof(struct account), 1, paprstat);
				if(memcmp(findacct, temp.accno, strlen(temp.accno)) == 0){
					if(temp.accst == 0){
						printf("\n\n The account is currently BLOCKED. Would you like to set it to ACTIVE? Enter:\n\n 1 - Yes\n\n 2 - No\n");
						scanf(" %d", &statsel);
						while( (statsel < 1) || (statsel > 2) ){
							printf(" That input was invalid. Would you like to set it to ACTIVE? Enter:\n\n 1 - Yes\n\n 2 - No\n");
							scanf(" %d", &statsel);
						}
						if(statsel == 1){
							temp.accst = 1;
							fseek(paprstat, sizeof(struct account)*i, SEEK_SET);
							fwrite(&temp, sizeof(struct account), 1, paprstat);
							printf(" The status has been changed to ACTIVE\n\n");
							if(fclose(paprstat) != 0)
								printf("Cannot close 'accounts' file\n");
							printf(" Enter any key to return to APRs and ACCOUNT STATUS' MENU\n");
							getch();
							managevalues();
						}
						else{
							if(fclose(paprstat) != 0)
								printf("Cannot close 'accounts' file\n");
							managevalues();
						}
					}
					if(temp.accst == 1){
						printf("\n\n The account is currently ACTIVE. Would you like to set it to BLOCKED? Enter:\n\n 1 - Yes\n\n 2 - No\n");
						scanf(" %d", &statsel);
						while( (statsel < 1) || (statsel > 2) ){
							printf(" That input was invalid. Would you like to set it to BLOCKED? Enter:\n\n 1 - Yes\n\n 2 - No\n");
							scanf(" %d", &statsel);
						}
						if(statsel == 1){
							temp.accst = 0;
							fseek(paprstat, sizeof(struct account)*i, SEEK_SET);
							fwrite(&temp, sizeof(struct account), 1, paprstat);
							printf(" The status has been changed to BLOCKED\n\n");
							if(fclose(paprstat) != 0)
								printf("Cannot close 'accounts' file\n");
							printf(" Enter any key to return to APRs and ACCOUNT STATUS' MENU\n");
							getch();
							managevalues();
						}
						else{
							if(fclose(paprstat) != 0)
								printf("Cannot close 'accounts' file\n");
							managevalues();
						}
					}
				}
				else
					continue;
			}
			printf("That account does not exist. Would you like to try writing it again?\n\n 1 - Yes\n\n 2 - Return to APRs and ACCOUNT STATUS' MENU\n");
			scanf(" %d", &retry);
			while( (retry < 1) || (retry > 2) ){
				printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Enter account number again\n\n 2 - Return to APRs and ACCOUNT STATUS' MENU\n");
				scanf(" %d", &retry);
			}
			if(retry == 2){
				if(fclose(paprstat) != 0)
					printf("Cannot close 'accounts' file\n");
				managevalues();
			}
			else
				continue;
		}
	}
	if(aprstat == 3)
		delacct();
	if(aprstat == 4)
		management();
	else
		management();
}

void bankmode() // BANK MENU
{
	int bankmenu = 0;

	system("cls");
	printf("\n Welcome to the BANK MENU. Please select from the following options... Enter:\n\n 1 - TO ADD/ AMEND ACCOUNTS\n\n 2 - DEPOSITS AND WITHDRAWALS\n\n 3 - LOANS\n\n 4 - TRANSFERS AND DIRECT DEBITS\n\n 5 - Return to MAIN MENU\n\n");
	scanf(" %d", &bankmenu);
	while( bankmenu < 1 || bankmenu > 5 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - TO ADD/ AMEND ACCOUNTS\n\n 2 - DEPOSITS AND WITHDRAWALS\n\n 3 - LOANS AND LOAN PAYMENTS\n\n 4 - INTERNAL TRANSFERS AND DIRECT DEBITS\n\n 5 - Return to MAIN MENU\n\n");
		scanf(" %d", &bankmenu);
	}
	if(bankmenu == 1)
		addamend();
	if(bankmenu == 2)
		depmenu();
	if(bankmenu == 3)
		loan();
	if(bankmenu == 4)
		transmenu();
	if(bankmenu == 5)
		mainmenu();
}

void add (struct account add, struct statistics st){
	
	int acn = 0, i, j, c, t = 0, x = -1;
	long y;
	FILE *f;
	FILE *n;
	FILE *s;
	struct stat buf;
	struct account cpy;
	
	system ("cls");
	f = fopen ("accounts", "a"); // Creates the account file in appending mode
	c = nofstruct (1); // Takes the number of structures
	fclose (f);
	x = stat ("statistics", &buf); // Checks if the statistics function exists
	if (x != 0){ // If not creates it
		n = fopen ("statistics", "w+");
		fclose (n);
	} 
	// The next loop is used to set the next logical account number even if accounts have been deleted
	f = fopen ("accounts", "r+");
	for (i = 0; i < c; i++){ // That loop is used to check the account number of the last structure
		fseek (f, sizeof(struct account)*i, SEEK_SET);
		fread (&cpy, sizeof(struct account), 1, f);
		acn = atoi (cpy.accno); // Converts the string accno into an integer
	}
	fclose (f);
	acn++; // Increases the integer accno by 1
	sprintf (add.accno, "%08d", acn); // Converts it back to string with certain leading zeros
	strtok (add.accno, "\n"); // Removes the new line created with sprintf
	printf ("The generated account number is 10-02-44 %s\n\n", add.accno);
	// Enters the needed account information
	printf ("Enter Name: ");
	fflush (stdin); // Flushes the input stream stdin
	fgets (add.name, sizeof(add.name), stdin); // fgets used so as to scan all symbols
	strtok (add.name, "\n"); // Removes the trailing newline after fgets
	uppercase (add.name); // Converts the string input into uppercase
	printf ("Enter Date of Birth (format DD/MM/YYYY): ");
	fflush (stdin);
	fgets (add.dob, sizeof(add.dob), stdin);
	strtok (add.dob, "\n");
	printf ("Enter Address: ");
	fflush (stdin);
	fgets (add.ads, sizeof(add.ads), stdin);
	strtok (add.ads, "\n");
	uppercase (add.ads);
	printf ("Enter Telephone: ");
	fflush (stdin);
	fgets (add.tel, sizeof(add.tel), stdin);
	strtok (add.tel, "\n");
	printf ("Enter ID Type: ");
	fflush (stdin);
	fgets (add.id, sizeof(add.id), stdin);
	strtok (add.id, "\n");
	uppercase (add.id);
	printf ("Enter ID Number: "); 
	fflush (stdin);
	fgets (add.idno, sizeof(add.idno), stdin);
	strtok (add.idno, "\n");
	uppercase (add.idno);
	printf ("Enter Other information: ");
	fflush (stdin);
	fgets (add.other, sizeof(add.other), stdin);
	strtok (add.other, "\n");
	uppercase (add.other);
	add.accst = 1; // Makes the account active by default
	s = fopen ("accounts", "r+");
	for (i = c; i-- > 0;){ // Counts from the end of the file to the beginning 
		fseek (f, sizeof(struct account)*i, SEEK_SET); // "jumps" between the structures
		fread (&cpy, sizeof(struct account), 1, f); // Reads a whole structure
		if (memcmp (add.idno, cpy.idno, strlen(cpy.idno)) == 0){ // Compares the entered idno with the one read, if they are the same proceed
			cpy.pstat++; // Increase the accounts per person by 1
			add.pstat = cpy.pstat;
			fclose (s);
			f = fopen ("accounts", "a");
			fwrite (&add, sizeof(struct account), 1, f); // Write all of the entered information to the accounts file
			fclose (f);
			y = buf.st_size; // Gets the size of the statistics file
			n = fopen ("statistics", "r+");
			for (j = 0; j < y; j++){
				fread (&st, sizeof(struct statistics)*j, 1, n); // Reads the structure in that file
			}
			fclose (n);
			n = fopen ("statistics", "r+");
			st.tstat = nofstruct (1); // Makes the total number of structures equal to the function counting them
			fwrite (&st, sizeof(struct statistics), 1, n); // Writes that number in the statistics file
			fclose (n); 
			printf("\nThe account was added to the system. Enter any key to continue...\n");
			getch();
			return;
		}
	}
	// If the same idno was not found then new person is creating an account
	fclose (s);
	add.pstat = 1; // Makes the acounts per person just 1
	f = fopen ("accounts", "a");
	fwrite (&add, sizeof(struct account), 1, f); // Write all of the entered information to the accounts file
	fclose (f);
	y = buf.st_size;
	n = fopen ("statistics", "r+");
	for (j = 0; j < y; j++){
		fread (&st, sizeof(struct statistics)*j, 1, n); // Reads the structure (so as to get the customers number)
	}
	fclose (n);
	n = fopen ("statistics", "r+");
	st.custno++; // Increase the customers number by one
	st.tstat = nofstruct(1); // Set the value of total accounts determined by the number of structures
	fwrite (&st, sizeof(struct statistics), 1, n);
	fclose (n);
	printf("\nThe account was added to the system.\n");
	return;
}

void addamend (void){

	int ch=0;
	char findacct[20];
	struct account acc = {acc.bal = 0}; // Sets the value of the balance for new accounts 0 by default
	struct statistics st = {st.tstat = 0}; 
	
	system ("cls");
	printf ("\n Welcome to ACCOUNTS.\n\n");
	printf (" Enter:\n\n 1 - Add new accounts\n\n 2 - Check account information\n\n 3 - Amend account information\n\n 4 - Return to the BANK MENU\n\n");
	scanf (" %d",&ch);
	while( ch < 1 || ch > 5 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Add new accounts\n\n 2 - Check account information\n\n 3 - Amend account information\n\n 4 - Return to the BANK MENU\n\n");
		scanf(" %d", &ch);
	}
	switch (ch)
	{ // Calls the respective function depending on user input
		case 1 : 
			add (acc, st);
			break;
		case 2 :
			printf("Please enter the account number: ");
			fflush (stdin);
			fgets (findacct, sizeof(findacct), stdin);
			strtok (findacct, "\n");
			if((checkacctnum(findacct)) == 0)
			viewstruct(1, findacct);
			break;
		case 3 : 
			amend (acc);
			break;
		case 4 : 
			bankmode();
			break;
		default : 
			printf ("\nIncorrect input!\n");
			break;
	}
	bankmode();
}

void amend (struct account am){

	int ch = 0, i, c = -1, reenter = 0;
	FILE *f;
	char acno[20];
	struct stat buf;

	system ("cls");
	c = stat ("accounts", &buf);
	if (c != 0 || nofstruct (1) == 0){ // Checks if the accounts file exists or has any structures in it
		printf ("\n No accounts record!\n");
		return; // If not end the function
	}
	else { // Otherwise proceed
		printf ("\n Account Amending\n");
		printf ("\n Enter account number: 10-02-44 "); // Asks for account number of the account to amend
		fflush (stdin);
		fgets (acno, sizeof(acno), stdin);
		strtok (acno, "\n");
		while(checkacctnum(acno) == 1){
			printf(" That account number does not exist on our records. Would you like to enter a different number? Enter:\n\n 1 - YES\n\n 2 - NO. Return to ACCOUNTS MENU\n\n");
			scanf(" %d", &reenter);
			while(reenter < 1 || reenter > 2){
				printf(" That entry was incorrect, please enter 1 - Re-enter account number\n\n 2 - Return to ACCOUNTS MENU\n\n");
				scanf(" %d", &reenter);
			}
			if(reenter == 2)
				addamend();
			else{
				fflush (stdin);
				fgets (acno, sizeof(acno), stdin);
				strtok (acno, "\n");
			}
		}
		if(checkacctnum(acno) == 2)
			addamend();
		f = fopen ("accounts", "r+");
		for (i=0; i < nofstruct (1); i++){	
			fseek (f, sizeof(struct account)*i, SEEK_SET);
			fread (&am, sizeof(struct account), 1, f);
			if (memcmp (acno, am.accno, strlen(am.accno)) == 0){ // Find that account by the account number
				printf("\n");
				while(ch<1 || ch>7){ 
					// The user makes a choice of what information to amend
					printf("\n Press the corresponding number to amend a particular account information\n");
					printf(" 1 - NAME\n\n");
					printf(" 2 - DATE OF BIRTH\n\n");
					printf(" 3 - ADDRESS\n\n");
					printf(" 4 - TELEPHONE\n\n");
					printf(" 5 - ID TYPE\n\n");
					printf(" 6 - ID NUMBER\n\n");
					printf(" 7 - OTHER\n\n");
					scanf(" %d",&ch);
					fflush (stdin);
					switch(ch){ // Depending on the choice different member in the structure obtains new value
						case 1 :
								printf ("\n Enter new Name: ");
								fgets (am.name, sizeof(am.name), stdin); 
								strtok (am.name, "\n");
								uppercase (am.name);
								break;
						case 2 :
								printf ("\n Enter the new Date of Birth (DD/MM/YYYY): ");
								fgets (am.dob, sizeof(am.dob), stdin);
								strtok (am.dob, "\n");
								break;
						case 3 :
								printf ("\n Enter the new Address: ");
								fgets (am.ads, sizeof(am.ads), stdin);
								strtok (am.ads, "\n");
								uppercase (am.ads);
								break;
						case 4 :
								printf ("\n Enter the new Telephone: ");
								fgets (am.tel, sizeof(am.tel), stdin);
								strtok (am.tel, "\n");
								break;
						case 5 :
								printf("\n Enter the new ID Type: ");
								fgets(am.id, sizeof(am.id), stdin);
								strtok (am.id, "\n");
								uppercase (am.id);
								break;
						case 6 :
								printf("\n Enter the new ID Number: ");
								fgets(am.idno, sizeof(am.idno), stdin);
								strtok (am.idno, "\n");
								uppercase (am.idno);
								break;
						case 7 :
								printf("\n Enter Other Information: ");
								fgets(am.other,sizeof(am.other),stdin);
								strtok (am.other, "\n");
								uppercase (am.other);
								break;
						default : printf("\n Incorrect input!\n");
								break;
					}	
				}
					fseek (f, sizeof(struct account)*i, SEEK_SET); // Finds the structure to write in
					fwrite (&am, sizeof(struct account), 1, f); // Write the change (keeping all other members in the structure intact)
					printf("\n The changes were saved. Press any key to continue...\n");
					getch();
					printf("\n");
					fclose (f);						
					return; 
			}	
		}
		// If the account was not found end the function
		fclose (f);	
		printf ("\nThe account was not found! Press any key to continue...\n"); 
		getch();
	}
	return;
}

char uppercase (char x[]){ // Gets a string as an input

	int i = 0;
	char c;
	while (x[i]) // Loop until it reaches the end of the string
	{
		c = x[i];
		x[i] = toupper(c); // Convert each character in the string to its equivalent uppercase
		i++; // Moves between the characters in the string
	}
	return (*x); // Returns the new uppercase string
}

void depmenu (void){

	int ch = 0;
	
	system ("cls");
	printf ("\n Welcome to DEPOSITS and WITHDRAWALS\n\n Enter:\n\n 1 - Deposit to an account\n\n 2 - Withdraw from an account\n\n 3 - Check deposits and withdrawals\n\n 4 - Return to the BANK MENU\n\n");
	scanf (" %d",&ch);
	while( ch < 1 || ch > 4 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Deposit to an account\n\n 2 - Withdraw from an account\n\n 3 - Check deposits and withdrawals\n\n 4 - Return to the BANK MENU\n\n");
		scanf(" %d", &ch);
	}
	switch (ch){
		case 1 : submdep (); // Calls the deposits submenu
				break;
		case 2 : submwith (); // Calls the withdrawals submenu
				break;
		case 3 : checkdep (); // Calls the check function
				break;
		case 4 : bankmode();
				break;
		default : printf ("Incorrect input!");
				break;
	}
	bankmode();
}

void submdep (void){

	int ch = 0;
	
	system ("cls");
	printf ("\n Welcome to DEPOSITS\n\n Please enter method of deposit:\n\n 1 - Bank transfer\n\n 2 - Cheque\n\n 3 - Cash\n\n 4 - Return to the DEPOSITS and WITHDRAWALS MENU\n\n");
	scanf (" %d",&ch);
	while( ch < 1 || ch > 4 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Bank transfer\n\n 2 - Cheque\n\n 3 - Cash\n\n 4 - Return to the DEPOSITS and WITHDRAWALS MENU\n\n");
		scanf(" %d", &ch);
	}
		switch (ch){
			case 1 :
				depdraw (ch); // Calls the deposits/withdrawals function
				break;
			case 2 :
				depdraw (ch); 
				break;
			case 3 :
				depdraw (ch); 
				break;
			case 4 :
				break;
			default : printf ("Incorrect input!");
					break;
		}
	depmenu();
}

void submwith (void){

	int ch = 0;
	
	system ("cls");
	printf ("\n Welcome to WITHDRAWALS\n\n Please enter method of withdrawal:\n\n 1 - Bank transfer\n\n 2 - Cash\n\n 3 - Return to the DEPOSITS and WITHDRAWALS MENU\n\n");
	scanf (" %d",&ch);
	while( ch < 1 || ch > 3 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Bank transfer\n\n 2 - Cash\n\n 3 - Return to the DEPOSITS and WITHDRAWALS MENU\n\n");
		scanf(" %d", &ch);
	}
	switch (ch){
		case 1 : 
			ch = 4;
			depdraw (ch);
			break;
		case 2 : 
			ch = 5;
			depdraw (ch);
			break;
		case 3 :
			break;
		default : 
			printf ("Incorrect input!");
			break;
	}
	depmenu();
}

void depdraw (int x)
{
	FILE *pdepdraw;
	FILE *pfrom;
	FILE *pto;
	int c = -1, i = 0, a = 0, t = 0, b1 = 0, b2 = 0;
	char sortck[20] = "104244";
	struct stat buf;
	struct account acc;
	struct account cpy;
	struct depdraw y;
	
	system ("cls");
	do {// Enter all the necessery information
		if (x == 1 || x == 2){ // Enter only if deposits by transfer or by cheque
			printf ("\n Enter SORT CODE from: ");
			fflush (stdin); // Flushes the input stream stdin
			fgets (y.sortfm, sizeof(y.sortfm), stdin); // Used to scan all symbols
			strtok (y.sortfm, "\n"); // Removes the trailing newline from done by fgets
		}
		if (x == 1 || x == 2 || x == 4 || x == 5){ // Enter if deposits by transfer, cheque; withdrawals by transfer and cash
			printf ("\n Enter ACCOUNT NUMBER from: ");
			fflush (stdin);
			fgets (y.acctfm, sizeof(y.acctfm), stdin);
			strtok (y.acctfm, "\n");
		}
		if(x == 1 || x == 2 || x == 3){
			printf ("\n Enter depositor's NAME: ");
			fflush (stdin);
			fgets (y.nametfm, sizeof(y.nametfm), stdin);
			strtok (y.nametfm, "\n");
			uppercase (y.nametfm);
		}
		printf ("\n Enter AMOUNT: ");
		scanf (" %lf", &y.amount);
		if (x == 4){ // Enter only if withdrawals by transfer
			printf ("\n Enter SORT CODE to: ");
			fflush (stdin);
			fgets (y.sortto, sizeof(y.sortto), stdin);
			strtok (y.sortto, "\n");
		}
		if (x == 1 || x == 2 || x == 3 || x == 4){ // Enter if deposits by transfer, cheque, cash and withdrawals by transfer
			printf ("\n Enter ACCOUNT NUMBER to: ");
			fflush (stdin);
			fgets (y.accto, sizeof(y.accto), stdin);
			strtok (y.accto, "\n");
		}
		printf ("\n Enter REFERENCE: ");
		fflush (stdin);
		fgets (y.ref, sizeof(y.ref), stdin);
		strtok (y.ref, "\n");
		uppercase (y.ref);
		printf ("\n Enter DATE: ");
		fflush (stdin);
		fgets (y.date, sizeof(y.date), stdin);
		strtok (y.date, "\n");
		printf("\n Enter:\n\n 1 - To CONFIRM the details\n\n 2 - To RE-ENTER the details\n\n 3 - Return to WITHDRAWALS\n\n");
		scanf(" %d", &a);
		while( a < 1 || a > 3 ){
			system("cls");
			printf("\n That option was invalid. Please choose from the following options... Enter\n\n 1 - To CONFIRM the details\n\n 2 - To RE-ENTER the details\n\n 3 - Return to WITHDRAWALS\n\n");
			scanf(" %d", &a);
		}
		switch (a){
			case 1 :
				t = 0;
				if (x == 1 || x == 2 || x == 4 || x == 5)
					if((checkacctnum(y.acctfm)) == 1){
						t = 1;
						printf("\n\n The paying account number does not exist... please RE-ENTER details\n\n Press any key to continue...");
						getch();
						break;
					}
				if(x == 1 || x == 2 || x == 3 || x == 4)
					if((checkacctnum(y.accto)) == 1){
						t = 1;
						printf("\n\n The payed account number does not exist... please RE-ENTER details\n\n Press any key to continue...");
						getch();
						break;
					}
				break;
			case 2 :
				t = 1;
                break;
			case 3 :
				submwith();
			default :
				break;
		}
	}while (t == 1); // If wrong number is pressed repeat the messages
////////////////////////////////////////////////////////////////////// Check blocked
	if( x == 1 || x == 2 ){
		if(memcmp(sortck, y.sortfm, strlen(y.sortfm)) == 0){
			if(checkacctstat(y.acctfm)==1){
				viewstruct(1, y.acctfm);
				printf(" ACCOUNT BLOCKED\n\n Enter any key to return to the DEPOSITS and WITHDRAWALS MENU... ");
				getch();
				depmenu();
			}
			else
				viewstruct(1, y.acctfm);
		}
	}
	if(x == 4 || x == 5){
		if(checkacctstat(y.acctfm)==1){
			viewstruct(1, y.acctfm);
			printf(" ACCOUNT BLOCKED\n\n Enter any key to return to the DEPOSITS and WITHDRAWALS MENU... ");
			getch();
			depmenu();
		}
		else
			viewstruct(1, y.acctfm);
	}
	if(x == 4){
		if(memcmp(sortck, y.sortto, strlen(y.sortto)) == 0){
			if(checkacctstat(y.accto)==1){
				viewstruct(1, y.accto);
				printf(" ACCOUNT BLOCKED\n\n Enter any key to return to the DEPOSITS and WITHDRAWALS MENU... ");
				getch();
				depmenu();
			}
			else
				viewstruct(1, y.accto);
		}
	}
	if(x == 1 || x == 2 || x == 3){
		if(checkacctstat(y.accto)==1){
			viewstruct(1, y.accto);
			printf(" ACCOUNT BLOCKED\n\n Enter any key to return to the DEPOSITS and WITHDRAWALS MENU... ");
			getch();
			depmenu();
		}
		else
			viewstruct(1, y.accto);
	}
	//////////////////////////////////////////////////// Check balance
	if( x == 1 || x == 2 )
		if(memcmp(sortck, y.sortfm, strlen(y.sortfm)) == 0){
			pfrom = fopen("accounts", "r+");
			for(i = 0; i < (nofstruct(1)); i++){
				fseek(pfrom, sizeof(struct account)*i, SEEK_SET);
				fread(&acc, sizeof(struct account), 1, pfrom);
				if(memcmp(y.acctfm, acc.accno, strlen(acc.accno)) == 0){
					if(y.amount > acc.bal){ // Checks if the amount entered is more than the balance in the account
						fclose(pfrom);
						printf ("\n Insufficient account balance!\n");
						printf ("\n The transfering was unsuccessful!\n\n Enter any key to return to the DEPOSITS and WITHDRAWALS MENU...");
						getch();
						depmenu();
					}
					else{
						acc.bal = acc.bal - y.amount; // Subtracts that amount from the balance
						fseek (pfrom, sizeof(struct account)*i, SEEK_SET); // Find the structure
						fwrite (&acc, sizeof(struct account), 1, pfrom); // Write the new balance in it
						fclose(pfrom);
					}
				}
			}
		}
	if(x == 4 || x == 5){
		pfrom = fopen("accounts", "r+");
		for(i = 0; i < (nofstruct(1)); i++){
			fseek(pfrom, sizeof(struct account)*i, SEEK_SET);
			fread(&acc, sizeof(struct account), 1, pfrom);
			if(memcmp(y.acctfm, acc.accno, strlen(acc.accno)) == 0){
				if(y.amount > acc.bal){ // Checks if the amount entered is more than the balance in the account
					fclose(pfrom);
					printf ("\n Insufficient account balance!\n");
					printf ("\n The transfering was unsuccessful!\n\n Enter any key to return to the DEPOSITS and WITHDRAWALS MENU...");
					getch();
					depmenu();
				}
				else{
					acc.bal = acc.bal - y.amount; // Subtracts that amount from the balance
					fseek (pfrom, sizeof(struct account)*i, SEEK_SET); // Find the structure
					fwrite (&acc, sizeof(struct account), 1, pfrom); // Write the new balance in it
					fclose(pfrom);
				}
			}
		}
	}
	if(x == 4)
		if(memcmp(sortck, y.sortto, strlen(y.sortto)) == 0){
			pfrom = fopen("accounts", "r+");
			for(i = 0; i < (nofstruct(1)); i++){
				fseek(pfrom, sizeof(struct account)*i, SEEK_SET);
				fread(&acc, sizeof(struct account), 1, pfrom);
				if(memcmp(y.accto, acc.accno, strlen(acc.accno)) == 0){
					acc.bal = acc.bal + y.amount; // Subtracts that amount from the balance
					fseek (pfrom, sizeof(struct account)*i, SEEK_SET); // Find the structure
					fwrite (&acc, sizeof(struct account), 1, pfrom); // Write the new balance in it
					fclose(pfrom);
				}
			}
		}
	if(x == 1 || x == 2 || x == 3){
		pfrom = fopen("accounts", "r+");
		for(i = 0; i < (nofstruct(1)); i++){
			fseek(pfrom, sizeof(struct account)*i, SEEK_SET);
			fread(&acc, sizeof(struct account), 1, pfrom);
			if(memcmp(y.accto, acc.accno, strlen(acc.accno)) == 0){
				acc.bal = acc.bal + y.amount; // Subtracts that amount from the balance
				fseek (pfrom, sizeof(struct account)*i, SEEK_SET); // Find the structure
				fwrite (&acc, sizeof(struct account), 1, pfrom); // Write the new balance in it
				fclose(pfrom);
			}
		}
	}
	if (x == 1){
		pdepdraw = fopen ("deptfr", "a"); // Opens for appending the "history" file for deposits by transfer
		fwrite (&y, sizeof(struct depdraw), 1, pdepdraw); // Writes all the entered information in it
		fclose (pdepdraw);
	}
	else if (x == 2){
		pdepdraw = fopen ("depchq", "a"); // Opens for appending the "history" file for deposits by cheque
		fwrite (&y, sizeof(struct depdraw), 1, pdepdraw); 
		fclose (pdepdraw);
	}
	else if (x == 3){
		pdepdraw = fopen ("depcsh", "a"); // Opens for appending the "history" file for deposits by cash
		fwrite (&y, sizeof(struct depdraw), 1, pdepdraw); 
		fclose (pdepdraw);
	}
	else if (x == 4){
		pdepdraw = fopen ("drawtfr", "a"); // Opens for appending the "history" file for withdrawals by transfer
		fwrite (&y, sizeof(struct depdraw), 1, pdepdraw); 
		fclose (pdepdraw);						
	}
	else if (x == 5){
		pdepdraw = fopen ("drawcsh", "a"); // Opens for appending the "history" file for withdrawls of cash
		fwrite (&y, sizeof(struct depdraw), 1, pdepdraw); 
		fclose (pdepdraw);
	}
	printf ("\n Details saved. Enter any key to continue... \n\n");
	getch();
	depmenu ();
}

void checkdep (void)
{
	int ch = 0,
		reenter = 0;
	char findacct[20];

	system("cls");
	printf(" Enter the account number that you wish to view details of... ");
	fflush (stdin);
	fgets (findacct, sizeof(findacct), stdin);
	strtok (findacct, "\n");
	while(checkacctnum(findacct) == 1){
		printf(" That account number does not exist on our records. Would you like to enter a different number? Enter:\n\n 1 - YES\n\n 2 - NO. Return to VIEW\n\n");
		scanf(" %d", &reenter);
		while(reenter < 1 || reenter > 2){
			printf(" That entry was incorrect, please enter 1 - Re-enter account number\n\n 2 - Return to VIEW\n\n");
			scanf(" %d", &reenter);
		}
		if(reenter == 2)
			transmenu();
		else{
			fflush (stdin);
			fgets (findacct, sizeof(findacct), stdin);
			strtok (findacct, "\n");
		}
	}
	system("cls");
	printf("\n What would you like to check? Enter:\n\n 1 - Deposits by transfer\n\n 2 - Deposits by cheque\n\n 3 - Deposits by cash\n\n 4 - Withdrawal by transfer\n\n 5 - Withdrawal by cash\n\n 6 - Return to DEPOSITS and WITHDRAWALS MENU\n\n");
	scanf (" %d",&ch);
	while( ch < 1 || ch > 6 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - Deposits by transfer\n\n 2 - Deposits by cheque\n\n 3 - Deposits by cash\n\n 4 - Withdrawal by transfer\n\n 5 - Withdrawal by cash\n\n 6 - Return to DEPOSITS and WITHDRAWALS MENU\n\n");
		scanf(" %d", &ch);
	}
	switch (ch){
		case 1 :
			viewdeptfr(findacct);
			break;
		case 2 :
			viewdepchq(findacct);
			break;
		case 3 :
			viewdepcsh(findacct);
			break;
		case 4 :
			viewwithtfr(findacct);
			break;
		case 5 :
			viewwithcsh(findacct);
			break;
		case 6 :
			depmenu();
            break;
		default :
			break;
	}
	depmenu();
}

void transmenu()
{
	int choice=0;
    
	system ("cls");
	printf("\n Welcome to the TRANSFERS AND DIRECT DEBIT MENU. Please select from the following options... Enter:\n\n 1 - To make an internal transfer\n\n 2 - To set up a direct debit\n\n 3 - To view transfers and direct debits for a particular account\n\n 4 - Return to BANK MENU\n\n");
	scanf(" %d", &choice);
	while( choice < 1 || choice > 5 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - To make an internal transfer\n\n 2 - To set up a direct debit\n\n 3 - To view transfers and direct debits for a particular account\n\n 4 - Return to BANK MENU\n\n");
		scanf(" %d", &choice);
	}
	switch (choice){
		case 1 :
			inttrans();
			break;
		case 2 :
			dirdeb();
			break;
		case 3 :
			view ();
			break;
		case 4 :
			bankmode ();
			break;
		default :
			printf ("\nProgramming error. Please report\n");
			break;
	}
	bankmode();
}

void inttrans ()
{    
	FILE *pinttrans;
	FILE *pfrom;
	FILE *pto;
	int c = -1, i, w = 0, a = 0, b1 = 0, b2 = 0;
	struct stat buf;
	struct account acc;
	struct inttfr t;
	
	system ("cls");
	do{		// Enter all the necessary information
		printf ("Enter the Account Number you are transfering/drawing from: ");
		fflush (stdin);
		fgets (t.acctfm, sizeof(t.acctfm), stdin);
		strtok (t.acctfm, "\n");
		printf ("Enter Amount: ");
		scanf ("%lf", &t.amount);
		printf ("Enter the Account Number you are transfering to: ");
		fflush (stdin);
		fgets (t.accto, sizeof(t.accto), stdin);
		strtok (t.accto, "\n");
		printf ("Enter Reference: ");
		fflush (stdin);
		fgets (t.ref, sizeof(t.ref), stdin);
		strtok (t.ref, "\n");
		uppercase (t.ref);
		printf ("Enter Date: ");
		fflush (stdin);
		fgets (t.date, sizeof(t.date), stdin);
		strtok (t.date, "\n");
		fflush (stdin);
		printf("\n Enter:\n\n 1 - To confirm the details\n\n 2 - To re-enter the details\n\n 3 - Return to TRANSFERS AND DIRECT DEBIT MENU\n\n ");
		scanf(" %d", &a);
		while( a < 1 || a > 3 ){
			system("cls");
			printf("\n That option was invalid. Please choose from the following options... Enter\n\n 1 - To confirm the details\n\n 2 - To re-enter the details\n\n 3 - Return to TRANSFERS AND DIRECT DEBIT MENU\n\n ");
			scanf(" %d", &a);
		}
		switch (a){
			case 1 :
				w = 0;
				if(checkacctnum(t.acctfm) == 1){
					w = 1;
					printf("\n\n The outgoing account number does not exist... please re-enter details\n\n Press any key to continue... ");
					getch();
				}
				if(checkacctnum(t.accto) == 1){
					w = 1;
					printf("\n\n The incoming account number does not exist... please re-enter details\n\n Press any key to continue... ");
					getch();
				}
				break;
			case 2 :
				w = 1;
                break;
			case 3 :
				transmenu();
				break;
			default :
				break;
		}
	}while (w == 1); // If wrong number is pressed repeat the messages
	viewstruct(1, t.acctfm);
	if(checkacctstat(t.acctfm)==1){
		printf(" ACCOUNT BLOCKED\n\n Enter any key to return to the TRANSFERS and DIRECT DEBITS MENU... ");
		getch();
		transmenu();
	}
	viewstruct(1, t.accto);
	if(checkacctstat(t.accto)==1){
		printf(" ACCOUNT BLOCKED\n\n Enter any key to return to the TRANSFERS and DIRECT DEBITS MENU... ");
		getch();
		transmenu();
	}
	pfrom = fopen("accounts", "r+");
	for(i = 0; i < (nofstruct(1)); i++){
		fseek(pfrom, sizeof(struct account)*i, SEEK_SET);
		fread(&acc, sizeof(struct account), 1, pfrom);
		if(memcmp(t.acctfm, acc.accno, strlen(acc.accno)) == 0){
			if(t.amount > acc.bal){ // Checks if the amount entered is more than the balance in the account
				fclose(pfrom);
				printf ("\n Insufficient account balance!\n");
				printf ("\n The transfering was unsuccessful!\n\n Enter any key to return to the TRANSFERS and DIRECT DEBITS MENU...");
				getch();
				transmenu();
			}
			else{
				acc.bal = acc.bal - t.amount; // Subtracts that amount from the balance
				fseek (pfrom, sizeof(struct account)*i, SEEK_SET); // Find the structure
				fwrite (&acc, sizeof(struct account), 1, pfrom); // Write the new balance in it
				fclose(pfrom);
			}
		}
	}
	pto = fopen("accounts", "r+");
	for (i = 0; i < nofstruct(1); i++){
		fseek(pto, sizeof(struct account)*i, SEEK_SET);
		fread(&acc, sizeof(struct account), 1, pto);
		if(memcmp(t.accto, acc.accno, strlen(acc.accno)) == 0){
			acc.bal = acc.bal + t.amount; // Adds the amount to its balance
			fseek (pto, sizeof(struct account)*i, SEEK_SET); // Find the structure
			fwrite (&acc, sizeof(struct account), 1, pto); // Writes the new balance
			fclose(pto);
		}
	}
	printf("\n Successful transfer! Enter any key to continue... \n\n");
	pinttrans = fopen ("inttfr", "a+"); // Opens for appending the "history" file for transfers
	fwrite (&t, sizeof(struct inttfr), 1, pinttrans); // Writes all the entered information in it
	fclose(pinttrans);
	transmenu();
}

void dirdeb () // done
{    
	FILE *f;
	FILE *n;
	char findacct[20],
		sortck[20] = "104244";
	int c = -1, i, w = 0, a = 0, b1 = 0, b2 = 0;
	struct stat buf;
	struct account acc;
	struct dirdeb s;
	
	system ("cls");
	do{		// Enter all the necessary information
		printf ("\n Enter sender's ACCOUNT NUMBER: ");
		fflush (stdin);
		fgets (s.acctfm, sizeof(s.acctfm), stdin);
		strtok (s.acctfm, "\n");
		printf ("\n Enter recipient's NAME: ");
		fflush (stdin);
		fgets (s.nametfm, sizeof(s.nametfm), stdin);
		strtok (s.nametfm, "\n");
		uppercase (s.nametfm);
		printf ("\n Enter AMOUNT: ");
		scanf ("%lf", &s.amount);
		printf ("\n Enter recipient's SORT CODE (format... '104244'): ");
		fflush (stdin);
		fgets (s.sortto, sizeof(s.sortto), stdin);
		strtok (s.sortto, "\n");
		printf ("\n Enter recipient's ACCOUNT NUMBER: ");
		fflush (stdin);
		fgets (s.acctto, sizeof(s.acctto), stdin);
		strtok (s.acctto, "\n");
		printf ("\n Enter REFERENCE: ");
		fflush (stdin);
		fgets (s.ref, sizeof(s.ref), stdin);
		strtok (s.ref, "\n");
		uppercase (s.ref);
		printf ("\n Enter START DATE: ");
		fflush (stdin);
		fgets (s.startdate, sizeof(s.startdate), stdin);
		strtok (s.startdate, "\n");
		fflush (stdin);
		printf ("\n Enter END DATE: ");
		fflush (stdin);
		fgets (s.enddate, sizeof(s.enddate), stdin);
		strtok (s.enddate, "\n");
		fflush (stdin);
		printf ("\n Enter the day of the month you would like the direct debit to be paid (1-28): ");
        fflush (stdin);
        fgets (s.payday, sizeof(s.payday), stdin);
		strtok (s.payday, "\n");
		printf ("\n Enter todays date: ");
		fflush (stdin);
		fgets (s.date, sizeof(s.date), stdin);
		strtok (s.date, "\n");
		fflush (stdin);
		printf("\n Enter:\n\n 1 - To confirm the details\n\n 2 - To re-enter the details\n\n 3 - Return to TRANSFERS AND DIRECT DEBIT MENU");
		scanf(" %d", &a);
		while( a < 1 || a > 3 ){
			system("cls");
			printf("\n That option was invalid. Please choose from the following options... Enter\n\n 1 - To confirm the details\n\n 2 - To re-enter the details\n\n 3 - Return to TRANSFERS AND DIRECT DEBIT MENU");
			scanf(" %d", &a);
		}
		switch (a){
			case 1 :
				w = 0;
				if(checkacctnum(s.acctfm) == 1){
					w = 1;
					printf("\n\n The paying account number does not exist... please re-enter details\n\n Press any key to continue...");
					getch();
				}
				if(memcmp(sortck, s.sortto, strlen(s.sortto)) == 0){
					if(checkacctnum(s.acctto) == 1){
						w = 1;
						printf("\n\n The paying account number does not exist... please re-enter details\n\n Press any key to continue... ");
						getch();
					}
				}
				break;
			case 2 :
				w = 1;
                break;
			case 3 :
				transmenu();
				break;
			default :
				break;
		}
	}while (w == 1); // If wrong number is pressed repeat the messages
	printf("\n\n OUTGOING ACCOUNT");
	viewstruct(1, s.acctfm);
	if(checkacctstat(s.acctfm)==1){
		printf("\n Outgoing ACCOUNT BLOCKED. Setup cancelled. Enter any key to continue... ");
		getch();
		transmenu();
	}
	strcpy(findacct, s.acctto);
	printf("\n INCOMING ACCOUNT");
	viewstruct(1, findacct);
	if(checkacctstat(findacct)==1)
		transmenu();
	strcpy(findacct, s.acctfm);
	
	f = fopen ("dirdeb", "a+"); // Opens for appending the "history" file for transfers
	fwrite (&s, sizeof(struct dirdeb), 1, f); // Writes all the entered information in it
	fclose(f);
	transmenu ();
}
        
int checkacctstat(char findacct[20])// return of 0 = account active; return of 1 = account blocked; return of 2 = file handling error (stated to user before exit)
{
	FILE *pcheckacctstat;
	int i = 0;
	struct account ckacct;
	
 	pcheckacctstat = fopen("accounts", "r");
	if(pcheckacctstat == NULL){
		printf("ERROR: opening 'accounts' data file... Enter any key to continue...");
		getch();
		return 2;
	}
	for(i = 0; i < (nofstruct(1)); i++){
		fseek(pcheckacctstat, sizeof(struct account)*i, SEEK_SET);
		fread(&ckacct, sizeof(struct account), 1, pcheckacctstat);
		if(memcmp(findacct, ckacct.accno, strlen(ckacct.accno)) == 0){
			if(ckacct.accst == 0){
				if(fclose(pcheckacctstat) != 0){
					printf("ERROR: closing 'accounts' data file... Enter any key to continue...");
					getch();
					return 2;
				}
				return 1;
			}
			if(ckacct.accst == 1){
				if(fclose(pcheckacctstat) != 0){
					printf("ERROR: closing 'accounts' data file... Enter any key to continue...");
					getch();
					return 2;
				}
				return 0;
			}
		}
	}
}

void view()
{
	int choice = 0,
		reenter = 0;
	char findacct[20];

	system("cls");
	printf(" Enter the account number that you wish to view details of... ");
	fflush (stdin);
	fgets (findacct, sizeof(findacct), stdin);
	strtok (findacct, "\n");
	while(checkacctnum(findacct) == 1){
		printf(" That account number does not exist on our records. Would you like to enter a different number? Enter:\n\n 1 - YES\n\n 2 - NO. Return to VIEW\n\n");
		scanf(" %d", &reenter);
		while(reenter < 1 || reenter > 2){
			printf(" That entry was incorrect, please enter 1 - Re-enter account number\n\n 2 - Return to VIEW\n\n");
			scanf(" %d", &reenter);
		}
		if(reenter == 2)
			transmenu();
		else{
			fflush (stdin);
			fgets (findacct, sizeof(findacct), stdin);
			strtok (findacct, "\n");
		}
	}
	printf("\n Enter:\n\n 1 - To view transfer information\n\n 2  - To view direct debit information\n\n\n\n 3 - Return to TRANSFERS AND DIRECT DEBIT MENU\n\n");
	scanf(" %d", &choice);
	while( choice < 1 || choice > 3 ){
		system("cls");
		printf("\n That option was invalid. Please choose from the following options... Enter:\n\n 1 - To view transfer information\n\n 2  - To view direct debit information\n\n\n\n 3 - Return to TRANSFERS AND DIRECT DEBIT MENU\n\n");
		scanf(" %d", &choice);
	}
	switch (choice){
		case 1 :
			viewinttfr(findacct);
			break;
		case 2 :
			viewdirdeb(findacct);
			break;
		case 3 :
			transmenu();
			break;
		default :
			transmenu();
	}
}

void viewinttfr(char findacct[20])
{
	viewstruct(11, findacct);
	transmenu();
}

void viewdirdeb(char findacct[20])
{
	viewstruct(12, findacct);
	transmenu();
}

void viewdeptfr(char findacct[20])
{
	viewstruct(3, findacct);
	depmenu();
}

void viewdepchq(char findacct[20])
{
	viewstruct(4, findacct);
	depmenu();
}

void viewdepcsh(char findacct[20])
{
	viewstruct(5, findacct);
	depmenu();
}

void viewwithtfr(char findacct[20])
{
	viewstruct(6, findacct);
	depmenu();
}

void viewwithcsh(char findacct[20])
{
	viewstruct(7, findacct);
	depmenu();
}

void loan()
{

	FILE *ptrbankacc;
	struct account bankacc;
	int accstatus = 0;
	int choice = 0, bankaccexist = 0, errorname = 0, erroraddress = 0, numbankitems = 0;
	double bankaccbalance = 0;
	long sizeofrecs = 0, i;
	char name[30];
	char address[100];
	char accountnumber[20];

	system("cls");
	// Request acc. no
	printf("\nPlease type in your account number (eg: 00000001, 00000101): ");
	scanf("%s", &accountnumber);
	// Check name and address
	checkaccandinfo:
	if(fopen("accounts","rb")==NULL) {
		printf("There are currently no bank accounts in our system.\n");
		bankmode();
	} else {
		ptrbankacc = fopen("accounts","rb");
		fseek(ptrbankacc , 0, SEEK_END);
		sizeofrecs = ftell(ptrbankacc);
		numbankitems = sizeofrecs/sizeof(struct account);
		rewind(ptrbankacc);
		for(i = 0; i < numbankitems ; i++) {
			fseek(ptrbankacc, sizeof(struct account)*i, SEEK_SET);
			fread(&bankacc, sizeof(struct account), 1, ptrbankacc);
			if(strcmp(bankacc.accno, accountnumber)==0) {
				strcpy(name, bankacc.name);
				strcpy(address, bankacc.ads);
				bankaccbalance = bankacc.bal;
				bankaccexist++;
			}
		}
		if(bankaccexist != 0) {
				printf("\nPlease confirm the following information for your account.");
				printf("\nName: %s", name);
				printf("\nAddress: %s", address);
				printf("\n\nEnter any key to confirm: ");
				getch();
				accstatus = checkacctstat(accountnumber);
		} else {
			fflush(stdin);
			printf("\nThe bank account does not exist in our system.\n");
			printf("\nPlease re-enter your account number (eg: 00000001, 00000101): ");
			scanf("%s", &accountnumber);
			fflush(stdin);
			goto checkaccandinfo;
		}
		fclose(ptrbankacc);
	}
	// error message
	if(accstatus == 1) {
		printf("\nThe given account number has been blocked, please contact the bank administrator.");
		bankmode();
	} else if(accstatus == 2) {
		printf("\nFile Handling Error.\n");
		bankmode();
	} else {
		// create/view loan account activity
		choice = 0;
		system("cls");
		printf("\n Welcome to the LOAN FACILITY \n");
		printf("\n Please select from the following options... Enter:\n");
		printf("\n 1 - APPLY FOR A LOAN\n");
		printf("\n 2 - PAY OFF YOUR LOAN\n");
		// printf("\n 3 - VIEW YOUR LOAN ACCOUNT\n");
		printf("\nEnter: ");
		scanf("%d", &choice);
	
		if(choice == 1) {
			applyloan(accountnumber);
		} else if(choice == 2) {
			payback();
		}
	}
}

void applyloan(char accountnumber[20])
{
	FILE *ptrapr1, *ptrapr3, *ptrapr5, *ptrbankacc;
	struct date today;
	struct loanacc loanapp;
	struct date enddate;
	struct account bankacc;
	int amount, period = 0, confirmation = 0, loannumber = 0, num_items, numbankitems = 0, i, choice = 0;
	float rate, repayment, mthint, totalrepayment;
	float x, y, t1, t2, c1;
	long sizeofrecs;
	FILE *interestrate, *ptrloanapplication;
	loanapp.duration = 0;

	// Pre-load information for the next loan application
	ptrloanapplication = fopen("loan","rb");	
	if(fopen("loan","rb")==NULL) {
		printf("No Loan Exist!");
	} else {
		fseek(ptrloanapplication, 0, SEEK_END);
		sizeofrecs = ftell(ptrloanapplication);
		num_items = sizeofrecs/sizeof(struct loanacc);
		loannumber = num_items;
		printf("TESTING_NUMBEROFITEMS: %d\n", num_items);
		printf("\nTESTING_LOANNUMBER: %d\n", loannumber);
		fclose(ptrloanapplication);
	}
	system("cls");
	printf("\n Welcome to the LOAN APPLICATION \n");
	// Autofill account number
	strcpy(loanapp.accountno, accountnumber);
	// Amount you want to borrow
	printf("\nPlease enter the amount you want to borrow: ");
	printf("\nAmount: ");
	scanf("%lf", &loanapp.loanamount);
	// Select your preference of payback durantion and the apr will be assign according to the file set by the management team
	changerepaymentoption:
	system("cls");
	ptrapr1 = fopen("loan1", "r");
	ptrapr3 = fopen("loan3", "r");
	ptrapr5 = fopen("loan5", "r");
	loanapp.duration = 0;
	while(loanapp.duration != 1 && loanapp.duration != 3 && loanapp.duration != 5)
	{
		printf("\n Please select one of the following repayment period:\n");
		printf("\n 1 - 1 year\n");
		printf("\n 3 - 3 years\n");
		printf("\n 5 - 5 years\n");
		printf("\nSelect: ");
		scanf("%d", &loanapp.duration);
		if(loanapp.duration == 1) {
			fread (&loanapp.apr, sizeof(float), 1, ptrapr1);
		} else if(loanapp.duration == 3) {
			fread (&loanapp.apr, sizeof(float), 1, ptrapr3);
		} else if(loanapp.duration == 5) {
			fread (&loanapp.apr, sizeof(float), 1, ptrapr5);
		}
	}
	fclose(ptrapr1);
	fclose(ptrapr3);
	fclose(ptrapr5);
	// Monthly interest, Monthly Repayment and Total Repayment calculation
	mthint = loanapp.apr/12/100;
	loanapp.monthlyrepayment = (mthint+(mthint/(pow(1+mthint,loanapp.duration*12)-1)))*loanapp.loanamount;
	loanapp.totalrepayment = loanapp.monthlyrepayment*loanapp.duration*12;
	// Get the time for start date
	gettime(&today);
	// Get the time for end date
	if(loanapp.duration == 1) {
		enddate.day = today.day;
		enddate.month = today.month;
		enddate.year = today.year + 1;
	} else if(loanapp.duration == 3) {
		enddate.day = today.day;
		enddate.month = today.month;
		enddate.year = today.year + 3;
	} else if(loanapp.duration == 5) {
		enddate.day = today.day;
		enddate.month = today.month;
		enddate.year = today.year + 5;
	}
	// Printing a summary of APR, Monthly payment and total repayment, startdate and enddate
	system("cls");
	printf("\nYour Loan APR will be: %.2f%%", loanapp.apr);
	printf("\nMonthly Payment: %.2f", loanapp.monthlyrepayment);
	printf("\nTotal Repayment: %.2f", loanapp.totalrepayment);
	printf("\nStart date: %d/%d/%d", today.day, today.month, today.year);
	printf("\nEnd date: %d/%d/%d\n", enddate.day, enddate.month, enddate.year);
	choice = 0;
	while(choice != 1 && choice != 2) {
		printf("\nPlease press 1 to confirm and press 2 change the repayment option: ");
		scanf("%d", &choice);
	}
	if(choice == 2) {
		goto changerepaymentoption;
	} 	
	system("cls");
	printf("\nPLEASE REVIEW YOUR LOAN APPLICATION DETAILS.\n");
	printf("Account Number: %s\n", loanapp.accountno+1);			// account number
	printf("Loan Number: %d\n", loannumber+1);	
	printf("Amount: %.2f\n", loanapp.loanamount);					// loan amount
	printf("Payday is on DAY %d of each month.\n", today.day);		// payday
	printf("Start date: %d/%d/%d\n", today.day, today.month, today.year);
	printf("End date: %d/%d/%d\n", enddate.day, enddate.month, enddate.year);
	printf("Duration: %d year(s)\n", loanapp.duration);
	printf("APR: %.2f%%\n", loanapp.apr);
	printf("Monthly Payment: %.2f\n", loanapp.monthlyrepayment);
	printf("Total Repayment: %.2f\n", loanapp.totalrepayment);	
	printf("\nIf the details are correct, please type 1 and enter to confirm / type 2 and enter to restart your loan application / type 3 to return to BANK MENU.\n");
	printf("Confirmation: ");
	scanf("%d", &confirmation);
	if(confirmation == 1) {
		if(fopen("loan","rb")==NULL) {
			printf("No Loan Exist yet!");
			ptrloanapplication = fopen("loan","wb+");
		} else {
			ptrloanapplication = fopen("loan","ab+");
		}
		if(!ptrloanapplication) {
			printf("Unable to open file!");
			bankmode();
		}
		loanapp.loanno = loannumber + 1;
		loanapp.startdate = today;
		loanapp.enddate = enddate;
		sprintf(loanapp.payday,"%d",loanapp.startdate.day);
		fwrite(&loanapp, sizeof(struct loanacc), 1, ptrloanapplication);
		fclose(ptrloanapplication);		
		// MODIFY THE BALANCE IN THE ACCOUNT NUMBER
		// Find the bank account balance and then modifythe account balance
		if(fopen("accounts","rb")==NULL) {
			printf("There are no accounts in our system or file handling error. You are being redirected back to the loan menu.\n");
			loan();
		} else {
			ptrbankacc = fopen("accounts","rb+");
			fseek(ptrbankacc , 0, SEEK_END);
			sizeofrecs = ftell(ptrbankacc);			// set the pointer to the end so we know the max size of the file
			numbankitems = sizeofrecs/sizeof(struct account);
			rewind(ptrbankacc);
			printf("\nFile exists.\n");
			for(i = 0; i < numbankitems ; i++) {
				fseek(ptrbankacc, sizeof(struct account)*i, SEEK_SET);
				fread(&bankacc, sizeof(struct account), 1, ptrbankacc);
				if(strcmp(bankacc.accno, loanapp.accountno)==0) {
					// printf("\nTESTING BANK BALANCE 1: %lf\n", bankacc.bal);
					bankacc.bal = bankacc.bal + loanapp.loanamount;
					// printf("\nTESTING BANK BALANCE: %lf\n", bankacc.bal);
					fseek(ptrbankacc, sizeof(struct account)*i, SEEK_SET);
					fwrite(&bankacc, sizeof(struct account), 1, ptrbankacc);
					break;
				}
			}
			fclose(ptrbankacc);
		}
		system("cls");
		choice = 0;
		printf("\nYour application has been sucessful and the loan has been added to your account. Enter any key to return the BANK MENU... ");
		getch();
		bankmode();
	} else if(confirmation == 2) {
		applyloan(accountnumber);
	} else if(confirmation == 3) {
		bankmode();
	}
}

void gettime(struct date *today)
{
	time_t now;
	struct tm *d;
	char day[10], month[10], year[10];

	time(&now);
	d = localtime(&now);
	strftime(day, 10, "%d", d);
	strftime(month, 10, "%m", d);
	strftime(year, 10, "%Y", d);	
	today->day = atoi(day);
	today->month = atoi(month);
	today->year = atoi(year);
}

void payback()
{
	int choice;
	system("cls");
	printf("\n Welcome to the PAYBACK FACILITIES \n");
	printf("\n Please choose from one the following payback options... Enter:\n");
	printf("\n 1 - TRANSFER\n");
	printf("\n 2 - CHEQUE\n");
	printf("\n 3 - CASH\n");
	printf("\nSelect: ");
	scanf("%d", &choice);
	if(choice == 1) {
		lntransfer();
	} else if(choice == 2) {
		lncheque();
	} else if(choice == 3) {
		lncash();
	}
}

void lntransfer()
{
	FILE *ptrschbankrec1, *ptrtransferfile, *ptrloansearch, *ptrbanksearch, *ptrtfrfile;
	long sizeofrecs;
	int num_items, numbankitems = 0, i, j = 0, loanexist = 0, sortcode = 100244, quit, bankaccexist = 0, choice = 0;
	int numloanchoice[20];
	int loanaccnumbers[10];
	char confirmation;
	struct account banksearch;
	struct loanacc temprec1, schloanrec1;
	struct loantransfer paytransfer;
	double bankbalance = 0, loanaccbalance = 0;	
	// INFORMATION TO BE FILL IN
	system("cls");
	printf("\nPlease enter the following informations: \n");
	// Acoount Number of person paying
	printf("\nAccount Number from:\n");
	scanf("%s", &paytransfer.accountfrom);
	fflush(stdin);
	// Sort Code of paying account
	printf("\nSort Code from:\n");
	scanf("%d", &paytransfer.sortfrom);
	fflush(stdin);	
	// If Sortcode is this bank system, load the bank balance
	if(paytransfer.sortfrom == sortcode) {
		// read the account
		ptrbanksearch = fopen("accounts","rb");
		fseek(ptrbanksearch, 0, SEEK_END);
		sizeofrecs = ftell(ptrbanksearch);			// set the pointer to the end so we know the max size of the file
		numbankitems = sizeofrecs/sizeof(struct loanacc);
		rewind(ptrbanksearch);
		
		for(i = 0; i < numbankitems ; i++) {
			fseek(ptrbanksearch, sizeof(struct account)*i, SEEK_SET);
			fread(&banksearch, sizeof(struct account), 1, ptrbanksearch);
			if(strcmp(banksearch.accno, paytransfer.accountfrom)==0) {
				bankbalance = banksearch.bal;
				strcpy(paytransfer.name, banksearch.name);
				bankaccexist++;
			}
		}
	} else if(bankaccexist == 0 && paytransfer.sortfrom == sortcode) {
		printf("\nBank account does not exist!\n");
		quit = 0;
		while(quit != 1 && quit != 2) {
			printf("\nPlease select the following options:");
			printf("\n1: Return to the payback menu");
			printf("\n2: Start the loan transfer application again");
			printf("\nSelect: ");
			scanf("%d", &quit);
			fflush(stdin);
			if(quit==1) {
				payback();
			} else if(quit==2) {
				lntransfer();
			}
		}
	}	
	if(bankaccexist == 0) {
		printf("\nPlease enter your name (eg: RAMIREZ MB): ");
		gets(paytransfer.name);
		fflush(stdin);
	}
	// Account number pay to
	printf("\nPlease enter the account number you want to pay for: ");
	scanf("%s", &paytransfer.accountto);
	fflush(stdin);
	// Search the binary file for the loan account records
	if(fopen("loan","rb")==NULL) {
		printf("No Loan Account has been created yet!\n");
		quit = 0;
		while(quit != 1 && quit != 2) {
			printf("\nPlease select the following options:");
			printf("\n1: Return to the payback menu");
			printf("\n2: Start the loan transfer application again");
			printf("\nSelect: ");
			scanf("%d", &quit);
			if(quit==1) {
				payback();
			} else if(quit==2) {
				lntransfer();
			}
		}
	} else {
		// Open the loan file, find the number of items for reading,
		system("cls");
		ptrschbankrec1 = fopen("loan","rb");
		fseek(ptrschbankrec1, 0, SEEK_END);
		sizeofrecs = ftell(ptrschbankrec1);			// set the pointer to the end so we know the max size of the file
		num_items = sizeofrecs/sizeof(struct loanacc);
		rewind(ptrschbankrec1);
		printf("\nBelow are the loans under the given account number, please select which loan do you want to pay off by entering the loan number.\n");
		// Goes through the loan file to see if what are the loans under the account
		for(i = 0; i < num_items ; i++) {
			fseek(ptrschbankrec1, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&temprec1, sizeof(struct loanacc), 1, ptrschbankrec1);
			if(strcmp(temprec1.accountno, paytransfer.accountto)==0) {
				printf("\nLoan Number: %d\n", temprec1.loanno);
				printf("Account Number: %d\n", temprec1.accountno);			// account number
				printf("Amount: %.2f\n", temprec1.loanamount);				// loan amount
				printf("Payday is on DAY %s of each month.\n", temprec1.payday);	// payday
				printf("Start date: %d/%d/%d\n", temprec1.startdate.day, temprec1.startdate.month, temprec1.startdate.year);
				printf("End date: %d/%d/%d\n", temprec1.enddate.day, temprec1.enddate.month, temprec1.enddate.year);
				printf("Duration: %d year(s)\n", temprec1.duration);
				printf("APR: %.2f%%\n", temprec1.apr);
				printf("Monthly Payment: %.2f\n", temprec1.monthlyrepayment);
				printf("Total Repayment: %.2f\n", temprec1.totalrepayment);
				loanexist++;
				loanaccnumbers[j] = temprec1.loanno;
				j++;
			}
		}
		// Prompt for which loan to pay off
		if(loanexist != 0) {
			printf("\nLOAN NUMBER: ");
			scanf("%d", &paytransfer.loanselectto);
			fflush(stdin);
			i = 0;
			while(paytransfer.loanselectto != loanaccnumbers[i]) {
				i++;
				if(i == j) {
					printf("\nNo loan account exist for the number you have entered.");
					quit = 0;
					while(quit != 1 && quit != 2) {
						printf("\nPlease select the following options:");
						printf("\n1: Return to the payback menu");
						printf("\n2: Start the loan transfer application again");
						printf("\nSelect: ");
						scanf("%d", &quit);
						if(quit==1) {
							payback();
						} else if(quit==2) {
							lntransfer();
						}
					}
				}
			}
		} else {
			printf("\nLoan does not exist for the account number you had enter.\n");
			quit = 0;
			while(quit != 1 && quit != 2) {
				printf("\nPlease select the following options:");
				printf("\n1: Return to the payback menu");
				printf("\n2: Start the loan transfer application again");
				printf("\nSelect: ");
				scanf("%d", &quit);
				if(quit==1) {
					payback();
				} else if(quit==2) {
					lntransfer();
				}
			}
		}
		fclose(ptrschbankrec1);
	}
	// Ask for the amount that you want to pay
	system("cls");
	printf("\nHow much do you want to pay: \n");
	scanf("%lf", &paytransfer.balance);
	fflush(stdin);
	if(bankbalance == 0)
		bankbalance = paytransfer.balance;
	// Find the loan account balance
	ptrloansearch = fopen("loan","rb");
	rewind(ptrloansearch);
	if(loanexist != 0) {
		for(i = 0; i < num_items ; i++) {
			fseek(ptrloansearch, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&schloanrec1, sizeof(struct loanacc), 1, ptrloansearch);
			if(schloanrec1.loanno == paytransfer.loanselectto) {
				loanaccbalance = schloanrec1.loanamount;
			}
		}
		fclose(ptrloansearch);
	}	
	/* CHECK IF PAYBACK AMOUNT IS MORE THAN THE ACCOUNT BALANCE
		IF MORE, DISPLAY A MESSAGE OF INSUFFICIENT FUND */
	system("cls");
	while(paytransfer.balance > bankbalance) {
		printf("\nThere is insufficient fund in your bank account.\n");
		printf("\nYour bank account only has a balance of %.2lf pounds.\n", bankbalance);
		printf("\nPlease re-enter your payback amount: ");
		scanf("%lf", &paytransfer.balance);
		fflush(stdin);
	}
	/* CHECK IF PAYBACK AMOUNT IS MORE THAN THE lOAN BALANCE
		IF MORE, DISPLAY A MESSAGE OF NOTIFICATION AND PROMPT FOR A CHANGE OF VALUE */
	system("cls");
	while(paytransfer.balance > loanaccbalance) {
		printf("\nThe payback amount is more than the loan amount.\n");
		printf("\nYour loan account only has a balance of %.2lf pounds.\n", loanaccbalance);
		printf("\nPlease re-enter your payback amount: ");
		scanf("%lf", &paytransfer.balance);
		fflush(stdin);
	}	
	// Reference
	system("cls");
	printf("\nPlease enter a reference (eg.Meal, Drinks): \n");
	gets(paytransfer.reference);
	fflush(stdin);
	// Date for payment
	system("cls");
	printf("\nPlease enter the date for transaction(DD/MM/YYYY): \n");
	scanf("%d/%d/%d", &paytransfer.paydate.day, &paytransfer.paydate.month, &paytransfer.paydate.year);
	fflush(stdin);
	// Confirmation of details
	system("cls");
	printf("\nCONFIRMATION OF DETAILS:\n");
	printf("Name: %s\n",paytransfer.name);
	printf("Account Number Paying: %s\n",paytransfer.accountfrom);
	printf("Sort Code of Paying Account: %d\n",paytransfer.sortfrom);
	printf("Loan Account Number: %s\n",paytransfer.accountto);
	printf("Loan Number: %d\n",paytransfer.loanselectto);
	printf("Amount: %.2lf\n",paytransfer.balance);
	printf("Ref: %s\n",paytransfer.reference);
	printf("Pay date: %d/%d/%d\n", paytransfer.paydate.day, paytransfer.paydate.month, paytransfer.paydate.year);
	// If confirm, press 1 and print to a file, To go back and amend the details, press 2
	while(confirmation!='Y' && confirmation!='R') {
		printf("\nPlease enter Y to CONFIRM, R to return to the payback menu");
		printf("\nType in CAPITAL LETTER(Y/N): ");
		scanf("%c", &confirmation);
		fflush(stdin);
	}
	if(confirmation=='Y') {
		ptrtfrfile = fopen("loantfr","ab+");
		fwrite(&paytransfer, sizeof(struct loantransfer), 1, ptrtfrfile);
		fclose(ptrtfrfile);
	} else if(confirmation=='R') {
		payback();
	}
	// Menu for finishing the loan
	system("cls");
	choice = 0;
	printf("Your loan transfer has been saved and it will be process soon.\n");
	printf("\nEnter any key to return to the bank menu.");
	getch();
	bankmode();
}

void lncheque()
{
	struct loancheque paycheque;
	struct account bankacc;
	struct loanacc loanaccount;
	struct date today;
	FILE *ptrbankacc, *ptrloanaccount, *ptrloanchq;
	long sizeofrecs;
	int numloanitems, numbankitems, bankaccexist = 0, loanaccexist = 0, sortcode = 100244, i = 0, j = 0;
	int quit = 0;
	char confirmation;
	int loanaccnumbers[10];
	double bankaccbalance = 0, loanaccbalance = 0;	
	// Find the number of items in the account file
	if(fopen("accounts","rb")!=NULL) {
		ptrbankacc = fopen("accounts","rb");
		fseek(ptrbankacc , 0, SEEK_END);
		sizeofrecs = ftell(ptrbankacc);			// set the pointer to the end so we know the max size of the file
		numbankitems = sizeofrecs/sizeof(struct account);
		rewind(ptrbankacc);
		fclose(ptrbankacc);
	} else {
		numbankitems = 0;
	}
	// Ask for account number
	system("cls");
	printf("\nPlease enter the following informations: \n");
	printf("\nAccount Number from (eg.00000001):\n");
	scanf("%s", &paycheque.accountfrom);
	fflush(stdin);
	// Ask for sort code
	printf("\nSort Code from (eg.101122):\n");
	scanf("%d", &paycheque.sortfrom);
	fflush(stdin);
	// Find the bank account balance
	if(paycheque.sortfrom == sortcode) {
		if(fopen("accounts","rb")==NULL) {
			system("cls");
			printf("CHEQUE DENIED! The account number you had enter does not exist in our system. You will now be redirected ot the payback menu.\n");
			payback();
		} else {
			ptrbankacc = fopen("accounts","rb");
			rewind(ptrbankacc);
			printf("\nFile exists.\n");
			for(i = 0; i < numbankitems ; i++) {
				fseek(ptrbankacc, sizeof(struct account)*i, SEEK_SET);
				fread(&bankacc, sizeof(struct account), 1, ptrbankacc);
				if(strcmp(bankacc.accno,paycheque.accountfrom)==0) {
					bankaccbalance = bankacc.bal;
					strcpy(paycheque.name, bankacc.name);
					printf("\nTESTING BANK BALANCE: %lf\n", bankaccbalance);
					bankaccexist++;
				}
			}
			if(bankaccexist == 0) {
				printf("\nCheque DENIED! The account number you had enter does not exist in our system. You will now be redirected ot the payback menu.\n");
				payback();
			}
		}
		fclose(ptrbankacc);
	}
	// Ask for the name of the person paying
	system("cls");
	if(bankaccexist == 0) {
		printf("\nPlease enter your name (eg: RAMIREZ MB): ");
		gets(paycheque.name);
		fflush(stdin);
	}
	// Account number pay to
	system("cls");
	printf("\nPlease enter the account number you want to pay for: ");
	scanf("%s", &paycheque.accountto);
	fflush(stdin);
	//  Find the number of records in the loan file
	ptrloanaccount = fopen("loan","rb");
	fseek(ptrloanaccount , 0, SEEK_END);
	sizeofrecs = ftell(ptrloanaccount);			// set the pointer to the end so we know the max size of the file
	numloanitems = sizeofrecs/sizeof(struct loanacc);
	rewind(ptrloanaccount);
	fclose(ptrloanaccount);
	// Search the binary file for the loan account records
	system("cls");
	if(fopen("loan","rb")==NULL) {
		printf("\nTransaction DENIED! Loan does not exist for the account number you had enter.\n");
		printf("\nEnter any key to return to PAYBACK MENU");
		getch();	
		payback();
	} else {
		ptrloanaccount = fopen("loan","rb");
		printf("\nBelow are the loans under the given account number, please select which loan do you want to pay off by entering the loan number.\n");
		for(i = 0; i < numloanitems ; i++) {
			fseek(ptrloanaccount, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&loanaccount, sizeof(struct loanacc), 1, ptrloanaccount);
			if(strcmp(loanaccount.accountno, paycheque.accountto)==0) {
				printf("\nLoan Number: %d\n", loanaccount.loanno);
				printf("Account Number: %s\n", loanaccount.accountno);			// account number
				printf("Amount: %.2lf\n", loanaccount.loanamount);				// loan amount
				printf("Payday is on DAY %s of each month.\n", loanaccount.payday);	// payday
				printf("Start date: %d/%d/%d\n", loanaccount.startdate.day, loanaccount.startdate.month, loanaccount.startdate.year);
				printf("End date: %d/%d/%d\n", loanaccount.enddate.day, loanaccount.enddate.month, loanaccount.enddate.year);
				printf("Duration: %d year(s)\n", loanaccount.duration);
				printf("APR: %.2f%%\n", loanaccount.apr);
				printf("Monthly Payment: %.2f\n", loanaccount.monthlyrepayment);
				printf("Total Repayment: %.2f\n", loanaccount.totalrepayment);
				loanaccexist++;
				loanaccnumbers[j] = loanaccount.loanno;
				j++;
			}
		}
		// Prompt for which loan to pay off
		if(loanaccexist != 0) {
			printf("\nLOAN NUMBER: ");
			scanf("%d", &paycheque.loanselectto);
			fflush(stdin);
			i = 0;
			while(paycheque.loanselectto != loanaccnumbers[i]) {
				i++;
				if(i == j) {
					printf("\nNo loan account exist for the number you have entered.");
					quit = 0;
					while(quit != 1 && quit != 2) {
						printf("\nPlease select the following options:");
						printf("\n1: Return to the payback menu");
						printf("\n2: Start the loan transfer application again");
						printf("\nSelect: ");
						scanf("%d", &quit);
						if(quit==1) {
							payback();
						} else if(quit==2) {
							lntransfer();
						}
					}
				}
			}
		} else {
			printf("\nLoan does not exist for the account number you had enter.\n");
			quit = 0;
			while(quit != 1 && quit != 2) {
				printf("\nPlease select the following options:");
				printf("\n1: Return to the payback menu");
				printf("\n2: Start the loan transfer application again");
				printf("\nSelect: ");
				scanf("%d", &quit);
				if(quit==1) {
					payback();
				} else if(quit==2) {
					lntransfer();
				}
			}
		}
		fclose(ptrloanaccount);
	}
	// Enter the amount you wish to pay
	system("cls");
	printf("\nPlease enter the amount you wish to pay: ");
	scanf("%lf", &paycheque.balance);
	bankaccbalance = paycheque.balance;
	fflush(stdin);
	if(bankaccbalance == 0)
		bankaccbalance = paycheque.balance;
	// Find the loan account balance
	ptrloanaccount = fopen("loan","rb");
	rewind(ptrloanaccount);
	if(loanaccexist != 0) {
		for(i = 0; i < numloanitems ; i++) {
			fseek(ptrloanaccount, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&loanaccount, sizeof(struct loanacc), 1, ptrloanaccount);
			if(loanaccount.loanno == paycheque.loanselectto) {
				loanaccbalance = loanaccount.loanamount;
			}
		}
		fclose(ptrloanaccount);
	}	
	/* CHECK IF PAYBACK AMOUNT IS MORE THAN THE ACCOUNT BALANCE
		IF MORE, DISPLAY A MESSAGE OF INSUFFICIENT FUND */
	system("cls");
	while(paycheque.balance > bankaccbalance) {
		printf("\nThere is insufficient fund in your bank account.\n");
		printf("\nYour bank account only has a balance of %.2lf pounds.\n", bankaccbalance);
		printf("\nPlease re-enter your payback amount: ");
		scanf("%lf", &paycheque.balance);
		fflush(stdin);
	}
	/* CHECK IF PAYBACK AMOUNT IS MORE THAN THE lOAN BALANCE
		IF MORE, DISPLAY A MESSAGE OF NOTIFICATION AND PROMPT FOR A CHANGE OF VALUE */
	system("cls");
	while(paycheque.balance > loanaccbalance) {
		printf("\nThe payback amount is more than the loan amount.\n");
		printf("\nYour loan account only has a balance of %.2lf pounds.\n", loanaccbalance);
		printf("\nPlease re-enter your payback amount: ");
		scanf("%lf", &paycheque.balance);
		fflush(stdin);
	}
	// Reference
	system("cls");
	printf("\nPlease enter a reference (eg.Meal, Drinks): \n");
	gets(paycheque.reference);
	fflush(stdin);
	// Set the transaction date to today
	gettime(&today);
	paycheque.paydate.day = today.day;
	paycheque.paydate.month = today.month;
	paycheque.paydate.year = today.year;
	// Confirmation of details
	system("cls");
	printf("\nCONFIRMATION OF DETAILS:\n");
	printf("Name: %s\n",paycheque.name);
	printf("Account Number Paying: %s\n",paycheque.accountfrom);
	printf("Sort Code of Paying Account: %d\n",paycheque.sortfrom);
	printf("Loan Account Number: %s\n",paycheque.accountto);
	printf("Loan Number: %d\n",paycheque.loanselectto);
	printf("Amount: %.2lf\n",paycheque.balance);
	printf("Ref: %s\n",paycheque.reference);
	printf("Pay date: %d/%d/%d\n", paycheque.paydate.day, paycheque.paydate.month, paycheque.paydate.year);
		// If confirm, press 1 and print to a file, To go back and amend the details, press 2
	system("cls");
	while(confirmation!='Y' && confirmation!='R') {
		printf("\nPlease enter Y to CONFIRM, R to return to the payback menu");
		printf("\nType in CAPITAL LETTER(Y/N): ");
		scanf("%c", &confirmation);
		fflush(stdin);
	}
	if(confirmation=='Y') {
		ptrloanchq = fopen("loanchq","ab+");
		fwrite(&paycheque, sizeof(struct loantransfer), 1, ptrloanchq);
		fclose(ptrloanchq);
	} else if(confirmation=='R') {
		payback();
	}
	// Menu for finishing the loan
	system("cls");
	quit = 0;
	printf("Your cheque transfer has been saved and it will be process soon.\n");
	printf("\nEnter any key to return to the bank menu.");
	getch();
	bankmode();
}

void lncash()
{
	FILE *ptrloanaccount, *ptrcashfile;
	long sizeofrecs;
	int numloanitems = 0, i= 0, j = 0, loanexist = 0, choice = 0, loanaccexist = 0;
	int loanaccnumbers[10];
	char confirmation;
	double loanaccbalance = 0;
	struct loancash paycash;
	struct loanacc loanaccount;
	struct date today;

	system("cls");
	fflush(stdin);
	printf("\nPlease enter your name (eg: RAMIREZ MB): ");
	gets(paycash.name);
	fflush(stdin);

	// Ask for account number
	system("cls");
	printf("\nAccount Number to:\n");
	scanf("%s", &paycash.accountto);
	fflush(stdin);

	// Find the number of records in the loan file
	ptrloanaccount = fopen("loan","rb");
	fseek(ptrloanaccount , 0, SEEK_END);
	sizeofrecs = ftell(ptrloanaccount);			// set the pointer to the end so we know the max size of the file
	numloanitems = sizeofrecs/sizeof(struct loanacc);
	rewind(ptrloanaccount);
	fclose(ptrloanaccount);

	// Search the binary file for the loan account records
	system("cls");
	if(fopen("loan","rb")==NULL) {
		printf("\nTransaction DENIED! Loan does not exist for the account number you had enter.\n");
		printf("\nEnter any key to return to PAYBACK MENU... \n");
		getch();
		payback();
	} else {
		ptrloanaccount = fopen("loan","rb");
		printf("\nBelow are the loans under the given account number, please select which loan do you want to pay off by entering the loan number.\n");
		for(i = 0; i < numloanitems ; i++) {
			fseek(ptrloanaccount, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&loanaccount, sizeof(struct loanacc), 1, ptrloanaccount);
			if(strcmp(loanaccount.accountno, paycash.accountto)==0) {
				printf("\nLoan Number: %d\n", loanaccount.loanno);
				printf("Account Number: %s\n", loanaccount.accountno);			// account number
				printf("Amount: %.2lf\n", loanaccount.loanamount);				// loan amount
				printf("Payday is on DAY %s of each month.\n", loanaccount.payday);	// payday
				printf("Start date: %d/%d/%d\n", loanaccount.startdate.day, loanaccount.startdate.month, loanaccount.startdate.year);
				printf("End date: %d/%d/%d\n", loanaccount.enddate.day, loanaccount.enddate.month, loanaccount.enddate.year);
				printf("Duration: %d year(s)\n", loanaccount.duration);
				printf("APR: %.2f%%\n", loanaccount.apr);
				printf("Monthly Payment: %.2f\n", loanaccount.monthlyrepayment);
				printf("Total Repayment: %.2f\n", loanaccount.totalrepayment);
				loanaccexist++;
				loanaccnumbers[j] = loanaccount.loanno;
				j++;
			}
		}
		// Prompt for which loan to pay off
		if(loanaccexist != 0) {
			printf("\nLOAN NUMBER: ");
			scanf("%d", &paycash.loanselectto);
			fflush(stdin);
			i = 0;
			while(paycash.loanselectto != loanaccnumbers[i]) {
				i++;
				if(i == j) {
					printf("\nNo loan account exist for the number you have entered.");
					choice = 0;
					while(choice != 1 && choice != 2) {
						printf("\nPlease select the following options:");
						printf("\n1: Return to the payback menu");
						printf("\n2: Start the loan transfer application again");
						printf("\nSelect: ");
						scanf("%d", &choice);
						if(choice==1) {
							payback();
						} else if(choice==2) {
							lntransfer();
						}
					}
				}
			}
		} else {
			printf("\nLoan does not exist for the account number you had enter.\n");
			choice = 0;
			while(choice != 1 && choice != 2) {
				printf("\nPlease select the following options:");
				printf("\n1: Return to the payback menu");
				printf("\n2: Start the loan transfer application again");
				printf("\nSelect: ");
				scanf("%d", &choice);
				if(choice==1) {
					payback();
				} else if(choice==2) {
					lntransfer();
				}
			}
		}
		fclose(ptrloanaccount);
	}	
	// Amount
	system("cls");
	printf("\nAmount you wish to pay: \n");
	scanf("%lf", &paycash.balance);
	fflush(stdin);
	// Find the loan account balance
	ptrloanaccount = fopen("loan","rb");
	rewind(ptrloanaccount);
	if(loanaccexist != 0) {
		for(i = 0; i < numloanitems ; i++) {
			fseek(ptrloanaccount, sizeof(struct loanacc)*i, SEEK_SET);
			fread(&loanaccount, sizeof(struct loanacc), 1, ptrloanaccount);
			if(loanaccount.loanno == paycash.loanselectto) {
				loanaccbalance = loanaccount.loanamount;
			}
		}
		fclose(ptrloanaccount);
	}
	/* CHECK IF PAYBACK AMOUNT IS MORE THAN THE lOAN BALANCE
		IF MORE, DISPLAY A MESSAGE OF NOTIFICATION AND PROMPT FOR A CHANGE OF VALUE */
	system("cls");
	while(paycash.balance > loanaccbalance) {
		printf("\nThe payback amount is more than the loan amount.\n");
		printf("\nYour loan account only has a balance of %.2lf pounds.\n", loanaccbalance);
		printf("\nPlease re-enter your payback amount: ");
		scanf("%lf", &paycash.balance);
		fflush(stdin);
	}
	// Reference
	system("cls");
	printf("\nPlease enter a reference: \n");
	gets(paycash.reference);
	
	// Set the date for payment
	gettime(&today);
	paycash.paydate.day = today.day;
	paycash.paydate.month = today.month;
	paycash.paydate.year = today.year;	
	fflush(stdin);	
	// Confirnation of details
	system("cls");
	printf("\nCONFIRMATION OF DETAILS:\n");
	printf("Name: %s\n",paycash.name);
	printf("Amount: %.2lf\n",paycash.balance);
	printf("Account Number to: %s\n",paycash.accountto);
	printf("Loan Selection: %d\n",paycash.loanselectto);
	printf("Ref: %s\n",paycash.reference);
	printf("Pay date: %d/%d/%d\n", paycash.paydate.day, paycash.paydate.month, paycash.paydate.year);
	while(confirmation!='Y' && confirmation!='R') {
		printf("\nPlease enter Y to CONFIRM, R to return to the payback menu");
		printf("\nType in CAPITAL LETTER(Y/R): ");
		scanf("%c", &confirmation);
		fflush(stdin);
	}
	if(confirmation=='Y') {
		ptrcashfile = fopen("loancsh","ab+");
		fwrite(&paycash, sizeof(struct loancash), 1, ptrcashfile);
		fclose(ptrcashfile);
	} else if(confirmation=='R') {
		payback();
	}
	// Menu for finishing the loan
	system("cls");
	choice = 0;
	printf("\nYour cash transfer has been saved and it will be process soon.");
	printf("\nEnter any key to return to the BANK MENU... ");
	getch();
	bankmode();
}
