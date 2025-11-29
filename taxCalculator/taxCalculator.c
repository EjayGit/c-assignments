#include <stdio.h>

#define OVERTIME 1.5 //The value to which the employee will be paid extra, per hour of overtime.
#define OT_START 38 // The value after which the employee will be paid overtime.
#define T1 0.15 // Percentage of TAX to be paid up to the value of TL1.
#define T2 0.2 // Percentage of TAX to be paid up to the value of TL2.
#define T3 0.25 // Percentage of TAX to be paid up to the value of TL3.
#define T4 0.3 // Percentage of TAX to be paid after the value of TL3.
#define TL1 300 // The value of money earnt up to which T1 is applied.
#define TL2 500 // The value of money earnt that which T2 is applied (after TL1).
#define TL3 650 // The value of money earnt that which T3 is applied (after TL2).

float gross(float, float); // Three functions calculating the value of gross earnt, tax paid and net paid.
float tax(float);
float net(float, float);

void main(void)
{
	int option = 0; // The value 0 has been given so that the program may test against a value later during a while loop.
	float scale;	// This variable will hold the wage/hr.
	float hours;		// This will hold the number of hours worked given by the user.
	float a;		// The variables a, b and c will hold the values of the three functions called by main.
	float b;
	float c;
	
	while ( (option != 1) && (option != 2) && (option != 3) && (option != 4) ) // While the value of 'option' does not equal 1, 2, 3 or 4, this loop will continuously ask for a new value for 'option'. 
	{
	printf("*******************************************************\nEnter the number corresponding to the desired pay rate:\n1 - $8.50/hr				2 - $9.90/hr\n3 - $22.40/hr				4 - $30.00/hr\n*******************************************************\n");
	scanf("%d", &option); // inputs the user value into the variable 'option'.
	} // as the loop suggests, if the value of 'option' is not 1, 2, 3 or 4, then request for a value again.

	switch(option)			// The variable 'option' will (after it gets past the while loop) be one of 4 values... 1,2,3,4. so...
	{
	case 1 : scale = 8.5;	// if 'option' = 1 then make 'scale' = 8.5 (to represent $8.50). Make the value for 'scale' equal to the value that was printed for the user during their selection.
		break;
	case 2 : scale = 9.9;
		break;
	case 3 : scale = 22.4;
		break;
	case 4 : scale = 30;
		break;
	}
	
	printf("Please enter the number of hours worked for week...\n");
	scanf("%f", &hours); // store number of hours into variable 'hours'.

	a = gross(scale, hours); // Call gross function and save return value as 'a'.
	printf("Gross income is $%0.2f for the week.\n", a); // Print value of 'a'. This value is the gross pay.

	b = tax(a); // Call tax function which takes the input 'a' (which is now the gross pay), and save return value as 'b'.
	printf("Tax to be paid is $%0.2f for the week.\n", b);// Print value of 'b'. This is the total tax paid.

	c = net(a, b); // Call net funtion and save it as 'c'.
	printf("Net income is $%0.2f for the week... Spend it well ;-)\n", c); // Print value of 'c'. This is the Net pay.
}

float gross(float scale, float hours)
{
	float g; // create working variable. To be returned.

	if (hours <= OT_START) // test to decide whether the user will start earning overtime based on their hours worked.
		g = scale * hours; // If the number of hours worked does not go into overtime then a simple hours worked multiplied by pay rate is saved as 'g'.

	else
	g = (scale * OT_START) + ( scale * OVERTIME * (hours - OT_START) ); // If the user did go into overtime, then add the total paid up to the overtime figure and plus that amount to the rate earnt by going into overtime, for every hour OVER the overtime figure.
	
	return g;
}



float tax(float a) // input is gross pay
{
	float t;

	if (a <= TL1) // These following four tests determine which bracket the value of gross pay lies within. Whether it is in the 15% tax bracket...
		t = T1 * a; // in which case multiply the value by the tax mark.

	if ( (a > TL1) && (a <= TL2) ) // The 20% tax bracket...
		t = (T1 * TL1) + (T2 * (a - TL1)); // In which case add the tax to be paid in the first tax bracket to the amount to be paid from the money earnt in the second tax bracket.

	if ( (a > TL2) && (a <= TL3) ) // The 25% tax bracket...
		t = (T1 * TL1) + ( T2 * (TL2 - TL1) ) + ( T3 * (a - TL2) ); // The tax from the first tax bracket + the tax from the second tax bracket + the tax to be paid from the amount earnt in the third tax bracket.

	if (a > TL3) // or for any money earnt over the third tax limit, the 30% tax... 'bracket' with no close bracket. :)
		t = (T1 * TL1) + ( T2 * (TL2 - TL1) ) + ( T3 * (TL3 - TL2) ) + ( T4 * (a - TL3) ); // The tax from the 3 tax brackets summed with the tax to be paid from any money earnt over the 4th tax bracket (ie over the last tax limit).

	return t;
}



float net(float a, float b) // inputs are the gross pay and the tax to be paid.
{
	float n;

	n = a - b; // simple sum of, gross pay subtract tax equals net pay.

	return n;
}
