#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// error: x = g(x) -> e_n+1 ~ g'(R)*e_n

double f(double x){
	return x*x;
}

// fixed point iteration 

int main(){

	double x = 5.9;
	double y;

	for(int i = 1; i <= 30; i++){
		x = f(x);
		// printf("%20.16lf\n", x);
	}

	// y = eval(function, x);
	printf("%lf\n", x);
}