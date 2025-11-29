# Problem Statement
Write a program that will calculate and print bills for the city power company depending on whether the use it residential, commercial or industrial. Code ‘R’ means residential, ‘C’ means commercial and ‘I’ means industrial. Any other code should be treated as an error.
The calculations are given on the worksheet.
## Tasks:
    • Prompt user and save an integer account number,
    • Request the user to enter the type of usage and their consumption figures in whole kWh,
    • Calculate the amount due by use of one of 3 functions,
    • All functions are to return a ‘double’, the residential and commercial are to take one ‘int’ and the industrial function should take 2 ‘int’, in the form of ‘peak’ and ‘off_peak’.

# Analysis
## Inputs:
    • Account number,
    • Code for usage type,
    • Consumption figure.
## Outputs:
    • Display the account number entered and the total cost to be charged to that account number based on the user inputs.
## Other tasks:
    • Test user code input to decide whether the program requires one further input for kWh, or whether it requires both peak kWh and off-peak kWh,
    • Calculate the total cost depending on which code was entered.

# Design
## General Algorithm:
    • Request and save account number,
    • Request code for usage type,
    • Test code and if it does not match the required codes, then send error message and re-request code,
    • Request kWh and call appropriate function dependant on code,
    • Print the cost associated to the account number after calculation within each function.



# Implementation
## Functions:
    • main,
    • residential,
    • commercial,
    • industrial.
### main:
    • Request and save account number,
    • Request code for usage type,
    • Test code and if it does not match the required codes, then send error message and re-request code,
    • Request kWh and call appropriate function dependant on code.
### residential (int) (hours used by user):
    • Print account number,
    • Calculate and print cost to user.
### commercial (int) (hours used by user):
    • Print account number,
    • Calculate and print cost to user.
### industrial (int, int) (hours used by user, peak and off-peak):
    • Print account number,
    • Calculate cost of peak usage,
    • Calculate cost of off-peak usage,
    • Sum peak and off-peak then print cost to user.
# Testing
There are different parts of the program that could not run as intended, specifically they are,
    • The while loop allowing the program to enter a code other than what has been requested,
    • Residential:
        ◦ Cost calculation.
    • Commercial:
        ◦ Cost before threshold,
        ◦ Cost after threshold.
    • Industrial:
        ◦ Peak use/ off-peak use, cost before threshold,
        ◦ Peak use, cost after threshold,
        ◦ Off-Peak use, cost after threshold.
# While loop
I tried all the requested codes and the while loop continued with the program. Whilst writing it I also placed ‘printf’ directly after the loop to confirm that the code had been saved correctly under the required address. It had. I also tried to enter several ‘incorrect’ characters and the while loop would continue to re-request until a requested character was entered.

# Residential function
To test this function I entered under the code ‘R’ 10kWh. The calculation is £4.00 + £0.03 per kWh. 
The answer should be £4.00 + £0.30 = £4.30


# Commercial function
    • Cost before threshold.
The threshold is set at 1500 kWh, so to test, I shall enter 1000 kWh. For under the threshold, £40.00 should be applied.

    • Cost after threshold.
The threshold is set at 1500 kWh, so to test, I shall enter 2000 kWh. For every kWh above the threshold, £0.02 should be added to the initial cost of £40.00. 
The answer should be £40.00 + (500 * £0.02) = £50.00

# Industrial function
    • Peak use/ off-peak use, cost before threshold.
The initial cost for peak use under the threshold is £53.00, and the cost for off-peak use under that threshold is £32.00. This means that as long as the use for peak and off-peak remain under their thresholds (both 1600 kWh) then the cost should always equal to £85.00.
I place 1000 hours use for both of them.

    • Peak use, cost after threshold.
For every kWh after 1600 for peak use, the rate is £0.07 per kWh. So I enter 2000 kWh and the answer I should get is £53.00 + £28 = £81.00. Taking into account the £32.00 compulsory initial cost for off-peak use, the total charged should be £113.00.






    • Off-Peak use, cost after threshold.
For every kWh after 1600 for peak use, the rate is £0.04 per kWh. So I enter 2000 kWh and the answer I should get is £32.00 + £16.00 = £48.00. Taking into account the £53.00 compulsory initial cost for peak use, the total charged should be £101.00.
