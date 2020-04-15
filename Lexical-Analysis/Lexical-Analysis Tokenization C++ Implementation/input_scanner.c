//-----------------------------------------------LAB-04-------------------------------------//
//AHmad Amjad Mughal and Abdul Ghafaar Kalhoro----------------------------------------------//
//------------------------------------Group Lab Submission of 03 and 04---------------------//
#include "input_scanner.h"

/* This program does some arbitrary calculations
 * including area, volume and floating point ratios etc.
 */

int main(){
	float area, volume;     /* Output Variables */
	int radius = 5;         // Radius of Circle & Sphere
    int num;

	float X = -44.15;
	float Y = 416.0e+1;
	float Z = X / Y;        /* Just to get a ratio, for no obvious reasons :)*/

	for (num = 0; num < 10; num++){
		printf("The Number is: %d\n", num);     // Again a loop for the sake of being a loop ;)
	}

	area = PI * radius * radius;                // Lets see if your pre-processor works!
    volume = (4.0/3.0) * PI * radius * radius * radius;     /* Here again !! */

	printf("Area: %f, Volume: %f\n", area, volume);
    return 0;       /// We are done! Are we ?
}
