#include <stdio.h>
#include <math.h>
#include <stdlib.h>



double test_function(double x){
	return 6*x*x + 4*x;
}

double left_riemann(double (*f)(double x), double a, double b, int n){

	double sum = 0;
	double delta = fabs(b - a) / n;
	double x = a;
	for(int i = 0; i < n; i ++){
		sum += f(x)*delta;
		x += delta;
	}
	return sum;
}

double trapezoid(double a, double b, double h){
	return (a + b)*h/2;
}

double left_trapezoidal_sum(double (*f)(double x), double a, double b, int n){

	double sum = 0;
	double delta = fabs(b - a) / n;

	// TODO: account for different signs on a, b
	// TODO: reduce calc of f efficiency
	double x = a;

	for(int i = 0; i < n; i++){
		sum += trapezoid(f(x), f(x + delta), delta);
		x += delta;
	}

	return sum;
}

double simpson(double x, double delta, double (*f)(double x)){
	double a = 1.0/3.0, b = 4.0/3.0, c = 1.0/3.0;
	return delta*(a*f(x - delta) + b*f(x)+ c*f(x + delta));
}

double simpson_efficent(double (*f)(double x), double a, double b, int n){

	double sum = 0;
	if(n % 2 != 0) n++;
	double delta = fabs(b - a) / n;

	// TODO: account for different signs on a, b
	// TODO: reduce calc of f efficiency
	double x = a;
	sum = f(a) + f(b);
	x = a + delta;
	for(int i = 1; i < n; i++){
		if(i % 2 == 0) sum += 2*f(x);
		else sum += 4*f(x);
		x += delta;
	}
	sum *= delta/3.0;

	return sum;
}

double simpson_sum(double (*f)(double x), double a, double b, int n){

	double sum = 0;
	if(n % 2 != 0) n++;
	double delta = fabs(b - a) / n;

	// TODO: account for different signs on a, b
	// TODO: reduce calc of f efficiency
	double x = a + delta;

	for(int i = 0; i < n; i += 2){
		sum += simpson(x, delta, f);
		x += 2*delta;
	}

	return sum;
}

int main(){

	// trapezoid: ((a + b)/2)*h

	double a = 2, b = 5;
	int n = 8; // must be even for simpson sum
	printf("left_riemann sum: %20.16lf\n", left_riemann(test_function, a, b, n));
	printf("trapezoid sum: %20.16lf\n", left_trapezoidal_sum(test_function, a, b, n));
	printf("simpson sum: %20.16lf\n", simpson_efficent(test_function, a, b, n));

}