#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// error: x = g(x) -> e_n+1 ~ g'(R)*e_n

double eval(double (*f)(double j), double x){
	return f(x);
}

double function(double x){
	return pow(x, 3) - 30*x - 36;
}

// fixed point iteration 

int main(){

	double x = 5.9;
	double y;

	for(int i = 1; i <= 30; i++){
		x = (pow(x, 3) - 36.0) / 30.0;
		printf("%20.16lf\n", x);
	}

	y = eval(function, x);
	printf("%lf\n", x);
}