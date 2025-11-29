#include <stdio.h>

void info( char *, char *); // I am using pointers because I want to return 2 variables out of the function later.
void diamond( char *, char *); // I am using pointers here just because I can. I could have used the (what will be) defined variables x, y.

void main()
{
	char x, y; // The 2 variables which will be used by both functions.
	
	info(&x, &y); // The inputs for the function are not the variables themselves, but the address' of the variables.

	diamond(&x, &y);
}

void info( char *u, char *v) // I have named these pointers, u and v. They point to the addresses of x and y (&x, &y).
{
	printf("\n\n\nThis program is going to draw a diamond.\nIt will use one character to draw the outline and the other to fill it.\n\nPlease type the character that you wish to use as the outline...\n"); // user command - I have used \n three times to give the command some of its own space for user friendliness.
	scanf("%c", &*u); // saving the data to the address of the pointer, u, which is pointing to the address of x and therefore the data is saved at x.

	printf("Now enter the character that you wish to use to fill the diamond...\n");
	scanf(" %c", &*v);
}

void diamond( char *u, char *v)
{
	printf("   %c   \n", *u); // A carefully positioned diamond with the outside 'char's to be written taken from the char x by... reading from the u-termed pointer which is pointing at the address saved as x, therefore the value of x is written.
	printf("  %c%c%c   \n", *u, *v, *u);
	printf(" %c%c%c%c%c \n", *u, *v, *v, *v, *u);
	printf("%c%c%c%c%c%c%c\n", *u, *v, *v, *v, *v, *v, *u);
	printf(" %c%c%c%c%c \n", *u, *v, *v, *v, *u);
	printf("  %c%c%c   \n", *u, *v, *u);
	printf("   %c   \n", *u);
}
