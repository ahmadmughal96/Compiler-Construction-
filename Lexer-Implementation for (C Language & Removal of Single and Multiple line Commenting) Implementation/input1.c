/* Source Code to calculate the power of a number
* using a recursive function */

#include <stdio.h>
int power(int n1, int n2); // Function Prototype

int main()
{
	int base = 3, exp = 4;	/** Lets hard-code the args */	
	printf("%d^%d = %d", base, exp, power(base, exp));
	return 0;
}

// Lets use recursion!!
int power(int base, int exp)
{
	if ( exp!=1 ){
		return (base * power(base, exp-1)); /* Easy! Isn’t it! */
	}
}
