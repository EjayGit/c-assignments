#include <stdio.h>
#include <math.h>
// following functions are void as no returns are required. They print the information required by the user having taken the inputs required for their relevant calculations.
void degenerate (int, int); // for when the situation is degenerate.
void real (int, int, int); // for when the value of 'b^2 - 4ac' is larger than 0. 
void complex (int, int, int); // for when the value of 'b^2 - 4ac' is smaller than 0. 
void multi_real (int, int, int); // for when the value of 'b^2 - 4ac' is equal to 0.

void main()
{
	int a, // variable representing the coefficient of x^2.
		b, // variable representing the coefficient of x.
		c; // variable representing the constant.

	printf("For the equation, ax^2 + bx + c = 0, please enter the values of a, b and c respectively...\n"); // request for the coefficients.
	scanf("%d %d %d", &a, &b, &c); // save the coefficients at their respective addresses.

	if ( (a == 0) && (b == 0) ) // Under circumstances where a and b equal 0, the equation is as stated.
         printf("Extremely degenerate\n");
	
    else if ( (a == 0) && (b != 0) ) // test for when circumstances are degenerate.
	     degenerate (b, c); // under these circumstances, the values for 'b' and 'c' are used so require input. 
			
	else if ( ( (b * b) - (4 * a * c) ) > 0 ) // test for when the situation will return 2 real numbers.
         real (a, b, c); // all three values will be used in the function.
					
	else if ( ( (b * b) - (4 * a * c) ) < 0 ) // test for when the situation will return 2 complex numbers.
         complex (a, b, c); // all three values will be used in the function.
												
	else if ( ( (b * b) - (4 * a * c) ) == 0 ) // test for when the situation will return multiple real solutions.
	     multi_real (a, b, c); // all three values will be used in the function.
    
    else // in the eventuality that I may have not allowed for every situation in my code, I have created a safety net in which the user will be informed that the program will not run as it was intended.
	printf("Program Error. Please report");
}

void degenerate (b, c)
{
	float x; // an appropriate type to return and this variable shall be returned.

	x = -c/b; // the calculation required to find the single solution.
	printf("Degenerate.\nx = %0.2f\n", x); // displaying the statement required associated with the equation and the solution to x.
}
void real (a, b, c)
{
	float x1, // 'x1' represents the first solution of the 2 possible solutions.
		  x2; // 'x2' represents the second solution of the 2 possible solutions.

	x1 = (-b + sqrt( (b * b) - (4 * a * c) ) ) / (2 * a); // the equation associated to 'b^2 + sqrt...'.
	x2 = (-b - sqrt( (b * b) - (4 * a * c) ) ) / (2 * a); // the equation associated to 'b^2 - sqrt...'.
	printf("Two real solutions.\nThe two roots are at x = %0.2f and x = %0.2f\n", x1, x2); // print the 2 solutions for the user to 2 decimal places.
}
void complex (a, b, c) // because my knowledge of using complex numbers in c is limited, I have arranged for the same answer to be displayed as it should, however it is not nessecarily achieved in the most efficient way, ie. use of operatives.
{
	float d, // represents the value of 'b^2 - 4ac', made positive.
		  r = (-b), // represents the first value required to calculate the real part to the solution and calculates it.
		  t = (2 * a), // represents the second value required to calculate the real part to the solution and calculates it.
          xr = r / t, // represents the real part of the complex number and is the same for both solutions of x and is thus used for both. The calculation is also made here.
		  xi; // the complex part of the solutions not taking into account the +/- operatives.
		  
	d = -( (b * b) - ( 4 * a * c ) ); // making 'd' the positive value of 'b^2 - 4ac'.

	xi = sqrt( d ) / (2 * a); // calculating the value to be used in the imaginary part of the complex number.
		
	printf("Two complex solutions.\nThe two roots are at x = %0.2f + %0.2fi and x = %0.2f - %0.2fi\n", xr, xi, xr, xi); // The 2 complex roots are written here but note that the char 'i' has been inserted at the appropriate points so that the display shows it corrctly even though the actual variable is not actually an imaginary number.
}

void multi_real (a, b, c)
{
	float x1, // even though the solutions will be identical, I have done the full calculations as though they may be different.
		  x2; // I could delete this variable and call it to print twice for the user.

	x1 = (-b + sqrt( (b * b) - (4 * a * c) ) ) / (2 * a); // finding the first solution and save it at the address x1..
	x2 = (-b - sqrt( (b * b) - (4 * a * c) ) ) / (2 * a); // finding the second solution and save it at the address x2
	printf("Multiple real solutions.\nThe two roots are at x = %0.2f and x = %0.2f\n", x1, x2); // display the 2 solutions to 2 decimal places.
}
