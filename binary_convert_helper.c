#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(){


	// x = 0110110110....
	//      -2,-3,-5,-6,-8,-9
	double x = 0;
	x += pow(2, -2);
	x += pow(2, -3);
	x += pow(2, -5);
	x += pow(2, -6);
	x += pow(2, -8);
	x += pow(2, -9);
	x += 1;
	// x *= pow(2, -10); // since x, y have same exponent
	// we can do algebra without worrying about it... for now.
	printf("x = %20.52lf\n", x);

	// y = 1000010.....
	//      -1,-6
	double y = 0;
	y += pow(2, -1);
	y += pow(2, -6);
	y += 1;
	// y *= pow(2, -10);
	printf("y = %20.52lf\n", y);

	double z = 4*x - y;
	// no change of first bit
	if(z > 0) printf("positive result\n");

	printf("z = %20.52lf\n", z);


	// 2 ^ +2 put z in form 1.xxxxxxx
	// add two to exponent
	printf("%20.52lf\n", z/4.0);

	// fract is the after decimal
	// fract = 048828125
	int fract = 48828125;

	printf("0"); // extra zero because c thought fract was in hex
	while(fract >= 1){
		printf("%0.0lf", fmod(fract, 2));
		fract /= 2;
	}
	printf("\n");
}