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
int checkacctstat(char[]); // returns 1 if inputted account number is blocked, returns 0 if active.

 
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
	printf("\n Welcome to HSBC© (HONG SOFIA BERMUDEZ CLARK)\n\n Group 6:\n - ERIK CLARK\n - MAURICIO RAMIREZ\n - WEE HONG FONG\n - CHRISTIAN RADEV\n - JAMES EARLY (did not participate).\n\n Please select from the following options... Enter:\n\n 1 - USER MANUAL\n\n 2 - MANAGEMENT (Password Protected)\n\n 3 - BANK MENU\n\n");
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
