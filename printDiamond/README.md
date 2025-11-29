#Problem Statement
##Tasks:
    • Write program that reads 2 ‘user chosen’ characters and print them in a diamond shape,
    • Write a function “info” that displays the instructions and reads the characters,
    • Write a function “diamond” that prints a diamond using the two characters.

#Analysis
##Inputs:
    • Scan 2 characters
##Outputs:
    • Print instructions,
    • Print diamond.
##Other tasks:
    • Create algorithm to draw diamond.

#Design
##General Algorithm:
    • main creates 2 variables to be used for the 2 char that will be used in the diamond,
    • main calls info,
    • info prints instructions,
    • info scans 2 characters,
    • info saves the 2 characters into the 2 variables.
    • main calls diamond,
    • diamond reads values of x and y,
    • diamond prints diamond shape.

#Implementation
##Functions:
    • main
    • info
    • diamond


###main:
    • Create 2 char variables (x, y). These will be used to save the characters by info and printed by diamond,
    • Call info with inputs to the addresses of x and y “(&x, &y)”,
    • Call diamond with inputs to the addresses of x and y “(&x, &y)”.
###info (with reference to the values pointing to u and v “(char *u, char *v)”):
    • Print instructions to enter one character that will be used as the outline for the diamond.
    • Scan the char and save it as the value pointing to u,
    • Repeat this for the second character and save it as the value pointing to v.
###diamond (with reference to the values pointing to u and v “(char *u, char *v)”):
    • Printf white space until char is required (ie. 3 spaces then %c) then newline,
    • Repeat this process until a diamond of %c has been drawn,
    • Select the appropriate char to call for each %c so that the diamond is outlined by one char and filled by the other.

#Testing
I tested this program by trial and error. I compiled it and modified it according to the given error messages. There were 2 types of error that I encountered. One was based on the pointers and the use and associated placement of the & and * symbols. The other type of error I encountered was where upon the scan for the second char, the program did not give the user the opportunity to write the second char. Instead it printed without it. The reason for this was that when return is pressed to save the first char, it requires 2 memory slots on the keyboard cache and with the second scan asking to occur immediately, the second scan request occurred during the return function. This was solved by adding a space after the quotation mark and before the scan request, ie. “ %c” as opposed to “%c”.
