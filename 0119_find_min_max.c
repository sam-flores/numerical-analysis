#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double eval(double (*f)(double j), double x){
	return f(x);
}

double function(double x){
	return cbrt(x) - 30*x - 36;
}

// fixed point iteration 

int main(){

	double x = 2;
	double y;
	double delta = 1/10.0;
	// head towards a min
	for(int i = 1; i <= 30000; i++){
		if(3*x*x-30 > 0) x += delta;
		else x -= delta;
		printf("%20.16lf\n", x);
	}

	y = eval(function, x);
	printf("%lf\n", x);
}