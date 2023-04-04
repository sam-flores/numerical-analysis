#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
  double ff;

  printf("enter guess: ");
  scanf("%lf", &x);

  // main loop
  for(int i = 1; i <= n; i++){
    ff = cbrt(30*ff + 36);
    x = x - (f(x)/fprime(x));
    printf("FPI: %20.16lf NM:%20.16lf\n", ff, x);

  }

  printf("newton's method: x: %lf f(x):%lf\n", x, f(x));
}