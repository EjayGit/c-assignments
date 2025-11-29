# Problem Statement
## Tasks:
    • Prompt user to enter value of resistor by use of while loop until ‘0’ is entered,
    • Store values in an array,
    • Calculate equivalent resistance,
    • Count number of resistors,
    • Test program with R1 = 1kΩ, R2 = 2kΩ, R3 = 4kΩ, R4 = 8kΩ,
    • Use separate loop to print resistances and equivalent resistance.
# Analysis
## Inputs:
    • Scan values of resistance into an array until the user enters ‘0’.
## Outputs:
    • Display the resistances entered by the user,
    • Display the equivalent resistance.
## Other tasks:
    • Calculate the equivalent resistance,
    • Count number of resistors,
    • Test program with given figures.

# Design
## General Algorithm:
    • Store values of resistances into an array and count all within a while loop until ‘0’,
    • Within another while loop repeatedly calculate the ‘1/resistance’ in order to find the equivalent resistance,
    • Calculate the equivalent resistance,
    • Display the number of resistances, the values of the resistances and the equivalent resistance.
# Implementation
## Functions:
    • main,
    • input,
    • calculate,
    • output.



### main:
    • Create required variables,
    • Call each function.
### input (int* i, float* pArray) (with reference to the values pointing to i and pArray):
    • Inform user how many resistors they can input and then request input,
    • Scan for input and save it under pArray (pointing to first value of array R,
    • Enter loop which increases where pArray points to, request and then scan for next value,
    • End loop and function ends when user enters ‘0’.
### calculate (int* i, float R) (with reference to the value pointing to i and the array R):
    • Create required variables,
    • Within a while loop, count through the memory locations and work through the initial calculation to find the equivalent resistance (ie. (1/R1) + (1/R2) + … etc),
    • During this process, display each resistance,
    • Once loop has reached the max counter value (found in input), exit loop,
    • Calculate equivalent by making making a variable = 1/(sum of inverse resistances).
### output (int i, float TRes) (with reference to the values of i and TRes):
    • Display the counter value (ie. the number of resistors entered by the user),
    • Display the equivalent resistance.
# Testing
Testing for this program has been set as to use the values of 1kΩ, 2kΩ, 4kΩ and 8kΩ. Using a calculator, the value of this resistors in parallel is, 533.33Ω.
The program returns,

The test gives the same answer and so we can take it as accurate for when more than one valid value for resistance is entered by the user.
If a negative value is entered, then the program does not perform the calculation correctly, but will list the resistors and show that a negative resistance has been entered.
If 0 is entered as the first value, then the output is not of value to the user.
