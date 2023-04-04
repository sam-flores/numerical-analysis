#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// e_n+1 ~ Q*e_n^2, Q =f''(R)/2*f'(R)

double f(double x){
	return x*x*x - 30*x - 36;
}

double fprime(double x){
	return 3*x*x - 30;
}

// newton's method

int main(){

	double x = 5; // initial guess
	int n = 100;

	printf("enter guess: ");
	scanf("%lf", &x);

	// main loop
	for(int i = 0; i < n; i++){
		x = x - (f(x)/fprime(x));	
	}
	
	printf("x: %lf f(x):%lf\n", x, f(x));
}