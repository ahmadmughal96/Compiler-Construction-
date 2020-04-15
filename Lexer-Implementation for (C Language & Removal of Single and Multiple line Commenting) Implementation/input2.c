#include <stdio.h>
#include <conio.h>

#define PI 3.14159

void main(){
	float area;
	int radius;
	int num;
	int test = 1;
	float X1 = -44.15;
	float Y1 = 416.0e+1;
	float Z1 = X1 / Y1;

	for (num=0; num<10; num++){
		printf("Number: %d\n", num);
	}

	printf("Enter Radius: ");
	scanf("%d", &radius);

	area = PI * radius * radius;

	area = area > 100 ? 100 : area;

	if((test & area) || (radius && area))
	printf("Area: %f\n", area);

	return;
}
