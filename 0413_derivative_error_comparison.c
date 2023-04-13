#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x){
	return x*sin(x);
}

double calc_standard_derivative(double x, double h, double (*f)(double a)){
	return (f(x + h) - f(x))/(h);
}

double calc_plus_minus_derivative(double x, double h, double (*f)(double a)){
	return (f(x + h) - f(x - h))/(2.0*h);
}


int main(){

	int n = 20;
	double h = .1;
	double x = 2.5;
	for(int i = 1; i <= n; i++){
		printf("standard: %20.16lf", calc_standard_derivative(x, h, f));
		printf(" | plus_minus: %20.16lf\n", calc_plus_minus_derivative(x, h, f));
		h /= 10;
	}
	printf("actual: %20.16lf\n", 2.5*cos(x) + 1*sin(x));


}