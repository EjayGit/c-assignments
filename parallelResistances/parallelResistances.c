#include <stdio.h>

#define N_RES 20 // NOTE: Enables 19 resistances to be entered. The last value must be '0' to continue with the program. Enables easier access for a user to edit the maximum number of resistors that they may have to enter.

void input(int*, float*); // function to insert values into variables required for calculations.
float calculate(int*, float*); // function to calculate Total Resistance.
void output(int, float); // function to print values required by the user.

void main()
{
	int i = 0; // counter for array memory position.
	float TRes, // variable for total resistance.
		  R[N_RES], // array to store values for up to 9 resistors. (last variable has to be 0 for while loop to end).
		  *pArray; // pointer to be used for array R for use of saving data easily between functions.
			
	pArray = R; // Make pArray point to the first memory location of R.
	input(&i, pArray); // run function for input of user. Inputs required is a pointer to the counter 'i' and pArray (the pointer to the Array R).
	TRes = calculate(&i, R); // Equal the variable TRes to the output which is the equivalent resistance. Inputs required are the pointer to the counter 'i' and the array R.
	output(i, TRes); // Run the output function. Requires the counter value and the equivalent resistance.
}



void input(int* i, float* pArray) // the counter 'i' is an int so the pointer must be an int too. R is an array of floats, thus pArray must be a float.
{
	printf("This program will calculate the equivalent resistance for up to %d resistors in parallel. Once you have entered the last resistance to be calculated, enter 0 to calculate.\n\nPlease enter value of resistance in ohms...\n", (N_RES - 1)); // This statement informs the user how many resistors they may enter and how to continue with the program once they have entered them all.
	scanf("%f", pArray); // Enters the first resistance into array 'R' at the position that pArray is pointing. Which will be R[0] at this point.

	while(*pArray != 0) // test so that while the last value entered is not '0', the while loop continues.
	{
		pArray++; // increase where pArray is pointing to by one memory location.
		*i=*i+1; // increase the value that the pointer is looking to by a value of 1. NOTE '*i++' increases the value of the memory location by 1 not the value stored there.
		printf("Please enter value of resistance in ohms...\n"); // each time the while loop has not read a '0' input, it requests another input from the user to enter into the next location of 'R' via 'pArray'.
		scanf(" %f", pArray); // Enters the value into 'R' via 'pArray'.
	}
}

float calculate(int* i, float *R) // the counter 'i' is used to limit how much of the array R is read during the calculation.
{
	
	int a = 0; // initialising a counter to 0. This will count through the memory locations of R while calculating the sum required to find the equivalent resistance.
	float t = 0; // this variable will be used to store the sum required to find the equivalant resistance as R is worked through each memory location. It has been initialised to 0 so that the initial sum has a value to sum it against.

	printf("The resistances entered are:\n"); // preparing to print a list of the entered resistances by the user.

	while(a != *i) // test so that while the counter 'a' does not equal the last memory location counted by 'i', the loop continues to calculate the equivalent resistances.
	{
		t = t + (1 / R[a]); // making t equal the previous required sum value plus the value of the current value being read (counted by 'a').
		printf(" - %0.1f Ohms\n", R[a]); // prints each resistor in a list for the user to see.
		a++; // plus one to 'a' so that the test may test to find the end of the user entered resistance (ie. '0') or read the next resistance so that it may be used for the calculation.
	}
	
	t = 1 / t; // to find the equivalent resistance take the sum of the resistances (individually been divided by 1) and find the inverse of this sum. Make t now equal to this.
	
	return t; // return the equivalent resistance.
}

void output(int i, float TRes) // this function requires the inputs 'i', that is the counter for the resistances and 'TRes', that hold the value of the equivalent resistance.
{
	printf("\nThe number of resistors entered is %d.\n\n", i); // print for the user the counted total of resistances.
	printf("The equivalent resistance of the resistors entered, when in parallel is, %0.3f Ohms.\n", TRes); // print for the user, the equivalent resistance.
}
