# Problem Statement
## Tasks:
    • Write a program that read values for a, b and c,
    • When a = b = 0, Print ‘Extremely degenerate’,
    • When a = 0, print ‘Degenerate’ and the solution found by the given equation,
    • When a ≠ 0, print both solutions found by the given equation,
        ◦ When ‘b2 – 4ac’ is positive, print ‘Two real solutions’,
        ◦ When ‘b2 – 4ac’ is negative, print ‘Two complex solution’,
        ◦ When ‘b2 – 4ac’ = 0, print ‘Multiple solutions’.
# Analysis
## Inputs:
    • Request value for a, b and c and save them.
## Outputs:
    • Print the relevant message and the solutions.
## Other tasks:
    • Test to find which message should be written and carry out the relevant calculation to find the solution(s).

# Design
## General Algorithm:
    • Request and save the values of a, b and c,
    • Test to see which message should be printed and thus which calculation should be used to find the solutions,
    • Call that function,
    • Print appropriate message and calculate and print solution(s).
# Implementation
## Functions:
    • main,
    • degenerate,
    • real,
    • complex,
    • multi_real.



### main:
    • Request and save the values of a, b and c,
    • Test to see which message should be printed and thus which calculation should be used to find the solutions,
    • If a = b = 0, then just state that the expression is ‘Extremely degenerate’ and leave it as that,
    • When testing between each one of the 5 possible outcomes, due to one or more of the if statements potentially being true (eg. if(a = 0), and if(b2 – 4ac >0)) then the else if becomes very important to ensure that 2 functions are not called,
    • Call appropriate function.
### degenerate (int, int) (with reference to the values of b and c):
    • Create variable to save solution to,
    • Calculate solution,
    • Print solution and message.
### real (int, int, int) (with reference to the values of a, b and c):
    • Create variables to save solutions to,
    • Calculate first solution for the ‘+sqrt’ aspect of the quadratic equation,
    • Calculate second solution for the ‘-sqrt’ aspect of the quadratic equation.
### complex (int, int, int) (with reference to the values of a, b and c):
    • Create variables:
        ◦ d = the modulus of b2 -4ac, as it will be < 0 in this situation,
        ◦ r = -b, to simplify later calculations,
        ◦ t = to simplify later calculations,
        ◦ xr = will represent the real part of the complex number,
        ◦ xi = will represent the imaginary part of the complex number,
        ◦ Calculate the real part of the complex number,
        ◦ Calculate the imaginary part of the complex number,
        ◦ Print the complex numbers with the addition within the print to change the operator sign so that both ‘+’ and ‘–‘ solutions are printed with ‘i’ printed immediately after the imaginary part.
### multi_real (int, int, int) (with reference to the values of a, b and c):
    • Create variables to save the solutions,
    • Calculate the 2 solutions,
    • Print the 2 solutions.
# Testing
I will test for each of the 5 types of equation/ message:
    • Extremely degenerate,
    • Degenerate,
    • Two real solutions,
    • Two complex numbers,
    • Multiple real solutions.


## Extremely degenerate
To test for this we have to enter any number as c, but make a and b equal to 0.

## Degenerate
To test for this we have to enter a = 0, with any other numbers to equal b and c.
I enter b = 5 and c = 10. The answer should be ‘-2’.

## Two real solutions
To test for this I have to make ‘b2 – 4ac’ > 0. To do this I select a = 1, b = 5, c = 1. These values equal ‘b2 – 4ac’ to +21. The 2 solutions should equal to:
    • x = -0.21
    • x = -4.79

## Two complex solutions
To test for this we have to make ‘b2 – 4ac’ < 0. To make this I select a = 5, b = 1, c = 5. These values equal ‘b2 – 4ac’ to ‘-99’. The 2 solutions should equal to:
    • x = -0.10 + 0.99i
    • x = -0.10 – 0.99i
