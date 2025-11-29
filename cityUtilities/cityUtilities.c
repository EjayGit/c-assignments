#include <stdio.h>

#define R_INITIAL 4 // initial charge for residential use
#define R_RATE 0.03 // rate per kWh for residential use
#define C_THRESHOLD 1500 // commercial threshold after which the commercial rate is applied
#define C_INITIAL 40 // initial charge for commercial use
#define C_RATE 0.02 // rate per kWh for commercial use
#define I_P_THRESHOLD 1600 // peak usage threshold for industrial use
#define I_P_INITIAL 53 // initial charge for peak industrial use
#define I_P_RATE 0.07 // rate per kWh for peak industrial use
#define I_OP_THRESHOLD 1600 // the off-peak usage threshold for industrial use
#define I_OP_INITIAL 32 // initial charge for off-peak industrial use
#define I_OP_RATE 0.04 // rate per kWh for off-peak industrial use

double residential(int); // this function calculates the total cost for a residential user.
double commercial(int); // this function calculates the total cost for a commercial user.
double industrial(int, int); // this function calculates the total cost for a industrial user.

void main()
{
	int acct, // variable to store the users accout number.
		peak, // variable to store the kWh used by industrial users during peak time.
		off_peak; // variable to store the number of kWh used by industrial users during off peak time.
        
	char code; // variable to store the code value entered by the user to determine the type of usage the user requires.
	double cost; // variable to save the value to be charged to the user.

	printf("Please enter your account number...\n"); // request the account number of the user to be associated to the charge.
	scanf("%d", &acct); // store the account number at the address of 'acct'.

	printf("\nPlease choose the appropriate code from the following...\n\n- R for Residential\n\n- C for Commercial\n\n- I for Industrial\n\n"); // request the user to enter the code associated to their type of usage. Note that I have catered for the user placing either a lower or upper case character associated with their code character.
	scanf(" %c", &code); // save the code at the address of 'code'.

	while( (code != 'R') && (code != 'r') && (code != 'C') && (code != 'c') && (code != 'I') && (code != 'i') ) // while the code entered by the user is not any of the codes that the program requests this loop requests for the code again until the user inputs a relevant code.
	{
		printf("\nERROR... Please select an appropriate code, R, C or I.\n"); // if the test does not test true for a required char, then the loop firsts states to the user that they have inputted an icorrect code and to try again.
		scanf(" %c", &code); // save the new input into the address of 'code'.
	}
// if the while loop tests true, then the user must have inputted a char that the program requires to continue.
	if ( (code == 'I') || (code == 'i') ) // Testing for industrial users.
	{
		printf("Please enter the amount of PEAK hours used to the nearest kilowatt hour...\n"); // peak hours for industrial use requested.
		scanf("%d", &peak); // Peak kWh saved at the address of 'peak'.
		printf("Please enter the amount of OFF-PEAK hours used to the nearest kilowatt hour...\n"); // off peak kWh requested.
		scanf("%d", &off_peak); // off peak kWh saved at address of 'off_peak'.
	}
	else // This else statement requests and saves a user input of kWh to the address 'peak'. In this situation, the industrial type has not been selected which means that the variable 'peak' and 'off peak' is not longer required by the industrial calculation, so to save on variables, I use the variable peak as a memory location to save the kWh for the remaining type of users (as each user only requires one value for kWh).
	{
		printf("Please enter the amount of hours used to the nearest kilowatt hour...\n"); // request user to input kWh.
		scanf("%d", &peak); // save value at address of 'peak'.
	} // after the else statement, if the user type was industrial, then the values of 'peak' and 'off_peak' have been saved with values requested for industrial user. If not, then the user will just recieve a request to enter the number of kWh.
	if ( (code == 'R') || (code == 'r') ) // if the user type is residential then make the variable 'cost equal to the output of the relevant function.
		cost = residential(peak);

	if ( (code == 'C') || (code == 'c') ) // if the user type is commercial then make the variable 'cost equal to the output of the relevant function.
		cost = commercial(peak);

	if ( (code == 'I') || (code == 'i') ) // if the user type is industrial then make the variable 'cost equal to the output of the relevant function.
		cost = industrial(peak, off_peak);

		printf("The cost applied to the account number %d is %c%0.2f\n", acct, 156, cost); // printing the account number and the value of the cost returned from the relavent function based on the type entered by the user.
}

double residential(peak) // the calculation for residential cost only requires the number of kWh used by the user.
{
	double res; // a double will be returned and this variable will be returned.

	res = R_INITIAL + (R_RATE * peak); // the calculation for cost given.
	return res; // returning the value.
}

double commercial(peak) // the calculation for commercial cost only requires the number of kWh used by the user.
{
	double com; // a double will be returned and this variable will be returned.

	if (peak > C_THRESHOLD) // test if the kWh is above the threshold.
		com = C_INITIAL + (C_RATE * (peak - C_THRESHOLD)); // if true, then charge the initial charge plus the rate for every kWh above the threshold.
	else
		com = C_INITIAL; // if not true then return this value (which is the amount to be charged up to the threshold).

	return com; // return the value.
}

double industrial(peak, off_peak) // the industrial type will hold a value given by the user for peak and off_peak.
{
	double p, // returning variable will be a double and so i have used doubles to hold values during the calculation process. 'p' will hold the value for the sum for any peak kWh entered by the user.
		   o_p, // variable to hold the sum for the off peak calculation.
		   ind; // variable to hold the total sum and to be returned by the function.

	if (peak > I_P_THRESHOLD) // test if the kWh is above the industrial peak threshold.
		p = I_P_INITIAL + (I_P_RATE * (peak - I_P_THRESHOLD)); // if true charge the initial value plus the rate for every kWh over the peak threshold.
	else
		p = I_P_INITIAL; // if not true then return this value (which is the amount to be charged up to the peak threshold).

	if (off_peak > I_OP_THRESHOLD) // test if the kWh is above the industrial off-peak threshold.
		o_p = I_OP_INITIAL + (I_OP_RATE * (off_peak - I_OP_THRESHOLD)); // if true charge the off-peak initial charge plus the rate for every kWh over the off-peak threshold.
	else
		o_p = I_OP_INITIAL; // otherwise charge the off-peak initial.

	ind = p + o_p; // sum the 2 totals and save them under the address of 'ind'.
	
	return ind; // return the total cost.
}
