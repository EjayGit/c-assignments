# Problem Statement

Write a program that requests the number of hours worked in a week and return to the user, the gross pay, tax to be paid and net pay for that period.

## Key information to take into account:
    • Overtime (in excess of 38 hours) = time and a half (ie. time x 1.5),
    • Tax rates;
                • 15% of first $300,
                • 20% of the next $200,
                • 25% of the next $150,
                • 30% of the rest.
## Tasks:
    • Create menu for user to select a salary and store that information,
    • Calculate gross pay (taking into account any overtime earned),
    • Calculate the tax to be deducted,
    • Calculate the net pay,
    • Print the value of these for the user.

# Analysis
## Inputs:
    • Salary,
    • Hours worked.
## Outputs:
    • Gross pay,
    • Tax paid,
    • Net pay.
## Other tasks:
    • Change menu option input from user into the value representing the salary selected,
    • Create algorithm to take into account overtime for gross pay,
    • Create algorithm to calculate tax regardless to which bracket the gross pay falls under.

# Design
## General Algorithm:
    • Create menu for user,
    • Store salary information:
                • Take only value from menu (ie. 1, 2, 3, 4),
                • If value not from menu, loop to request value again.
    • Change value into salary value according to menu option selected,
    • Calculate the total hours to be paid (ie. taking into account overtime),
    • Calculate the gross pay,
    • Calculate the tax to be paid,
    • Calculate the net pay,
    • Print the values for the user.
# Implementation
## Functions:
    • Main,
    • Gross,
    • Tax,
    • Net.
### Main:
    • Creates a while loop with the menu for the user in it. If the value of option is not 1, 2, 3 or 4, then the loop repeats and requests the value again. If the value meets the requirements, then the loop exits,
    • switch is used to store the user’s selection (ie. the required salary) into the variable, scale,
    • main uses 3 variables, a, b and c to save the return values from the functions, gross, tax and net respectively, then uses them to print the information to the user.
### Gross:
    • Takes the inputs, scale and hours, so that it may multiply these appropriately to find gross pay,
    • Creates a working variable to be returned,
    • OT_START is the value defined and means the number of hours to which the overtime multiplier will take effect,
    • OVERTIME is a defined value and is the overtime multiplier. Ie. the value to which every hour worked past OT_START will be multiplied by. Eg. 1.5 means every hour will count for 1.5 hours,
    • Tests to see if the hours worked are equal to or below the overtime value. If the test is true, a simple sum calculates and returns the gross pay,
    • If the hours worked are above the overtime value then the number of extra worked hours is multiplied by the overtime multiplier and then by the salary. This value is then added to the money earned up to the overtime value to make a total for gross income and returned by the function.
### Tax:
    • Takes the input, a, which is the return value of gross pay, 
    • Creates a working variable to be returned,
    • There are 4 tax multipliers, all defined and called T1, T2, T3 and T4. Ie. a value of 0.2 means 20% tax,
    • There are 3 levels to separate the 4 tax multipliers and are called TL1, TL2 and TL3. Ie. a value of 300 will mean that the value 300 is the top of one tax bracket, and the bottom of the next,
    • There are 4 if statements, one for each tax multiplier. They each test to see where the gross pay lies and execute a calculation upon a true test.
    • Each if statement multiplies its tax multiplier by the value earned subtracted by the previous tax level. This is then added against the previous tax brackets multiplied by their respective tax multiplier. The sum of any if statement will save as the working variable and returned by the function.
    • Eg. If the gross pay lies in the 2nd tax bracket, the gross pay minus the 1st tax level will leave the remainder amount to be taxed by the 2nd tax multiplier. This is added to, the 1st tax level multiplied by the 1st tax multiplier. This returns a value which has been taxed correctly through each tax bracket and therefore the total tax to be paid.
### Net:
    • The function has 2 inputs, a and b. These have previously been saved as the return values for the functions gross and tax.
    • Creates a working variable to be returned,
    • A simple calculation of gross subtract tax is made returning the value and saving it as c.
### Testing
There are different parts to this program that needed testing individually and are as follows;
    • while loop test,
    • Salary selection and assign value to scale through switch,
    • gross function;
        ◦ Overtime test,
    • tax function;
        ◦ Each tax bracket works,
    • net function;
        ◦ Simple calculation.
while Loop Test:
This while loop tests to see if the value of option, selected by the user is either, 1, 2, 3 or 4. This enables the rest of the program to work. If the value is not one of these the loop resets and requests the user to select again.
To test this, I run the program and input integers into the program. I expect the loop to request again for each value other than 1, 2, 3 or 4. When I am satisfied that it does not take other values, I select 1. I expect the next stage of the program to run by asking me to input the number of hours.
I repeat this test for 2, 3 and 4, ensuring that is accepts the appropriate values.
Salary Selection and Assign Value to scale through switch:
To ensure that the user input 1, 2, 3 and 4 are then taken by the program and the respective salary saved by the switch command, during coding, I entered an extra printf command which would illustrate the values of option, scale and hours (I added this after the hours request to test that all variables were saved correctly). After the user had entered the hours worked, the program would show values saved under these variables. They showed as expected. option = the user input, scale = the salary saved by switch and hours = the hours worked that the user had input into the program.
gross Function – Overtime Test:
This test was done by noting the fact that the value of OT_START was 38 (hours) and then entering a value of 38 hours for hours worked into the program. The value was recorded for a particular salary. The program was run again and using the same salary, 39 hours were said to have been worked. The gross pay should have been 1.5 time the salary per hour more than the previous value.
For a salary of $30 per hour, when 38 hours are worked, the gross pay is $1140.00.
For a salary of $30 per hour, when 39 hours are worked, the gross pay should read $1140.00 + $45 which is $1140.00 + ($30 x 1.5). This is $1185.00. The value returned by the program is $1185.00.
tax Function - Each Tax Bracket Works:
There are 3 tax levels available in the program and the weakness in the code is likely to be at the if tests area. We can check for calculation errors as we check the if tests too.
The 3 tax levels are defined as $300, $500 and $650. The if tests are testing for the gross pay to be above the lower level value and at or below the higher level value, this means I will test values for gross pay levels that are just above each tax level and compare them to externally calculated values.
The tax values for the test for each bracket are as follows,
0 – 300……………	15%
>300 – 500……..	20%
>500 – 650……..	25%
>650……………….	30%
Table 1 illustrates the test carried out,
Salary per hour	Hours worked	Gross pay	Tax paid (program)	Tax paid (check value)
$30	1	$30	$4.50	$4.50
$30	11	£330	$51.00	$51.00
$30	17	$510	$87.50	$87.50
$30	22	$660	$125.50	$125.5
Table 1
All check values match the program values.
net Function - Simple Calculation:
This test only requires one simple check sum. So using $30 per hour as a salary and 40 hours as a hours worked value. The values for gross pay is $1230.00 and for tax to be paid is $296.50. Gross subtract tax equals net. 1230.0 – 296.5 = 933.5. The program calculates $933.50 and therefore the testing is complete.
