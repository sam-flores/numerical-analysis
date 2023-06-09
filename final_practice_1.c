#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x){
	double fx = 17  +  (14 - 8*cos(x) + cos(2*x)) * cos(2*x)   - 24*cos(x);
	fx /= (x*exp(x) - x) * (1 + 2*x*x - cos(2*x) - 4*x*sin(x));
	return fx;
}

double lim(double (*f)(double x), double a, int n){
	double delta = 10;
	for(int i = 1; i <= n; i++){
		printf("f(%lf + %lf) = %lf\n", a, delta, f(a + delta));
		delta /= 2;
	}
	return f(a + delta);
}

int main(){

	int n = 25;
	double a = 0;
	printf("\nthe lim of f as x -> %lf is %lf\n\n", a, lim(f, a, n));
	printf("\nactual f(%lf) = %lf\n\n", a, f(a));

}