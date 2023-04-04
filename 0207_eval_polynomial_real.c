#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// f(x) = 2xxx-9xx+32x+75, f'(x) = 6xx-18x+32

double coefficients[100], prime_coefficients[100];
int n;

double evaluate_polynomial(double x){
  double answer = 0;
  double p = 1;
  for(int i = 0; i <= n; i++){
    answer += coefficients[i]*p;
    p *= x;
  }
  return answer;
}

double evaluate_polynomial_derivative(double x){
  double answer = 0;
  double p = 1;
  for(int i = 0; i < n; i++){
    answer += prime_coefficients[i]*p;
    p *= x;
  }
  return answer;
}

void handle_user_input(){

  printf("enter polynomial up to 100\n");
  // scanning
  scanf("%d", &n);
  printf("\n");
  for (int i = n; i >= 0; i--){
    scanf("%lf", &coefficients[i]);
    if(i > 0) prime_coefficients[i - 1] = (i)*coefficients[i];
  }
  printf("\n f(x)  = ");
  // printing
  for (int i = n; i >= 0; i--){
    // p = n - 1;
    printf("%lf*", coefficients[i]); printf("x^"); printf("(%d)", i);
    if(i != 0 && coefficients[i - 1] > 0) printf("+");
  }
  printf("\n f'(x) = ");
    for (int i = n; i >= 0; i--){
      // p = n - i - 1;
    printf("%lf*", prime_coefficients[i]); printf("x^"); printf("%d", i);
    if(i != 0 && prime_coefficients[i - 1] > 0) printf("+");
  }
  printf("\n");
}

int main()
{
  double cr, ci;
  double c;

  handle_user_input();
  scanf("%lf", &c);
  printf("  x   = %lf", c);   printf("\n");
  printf("f(x)  = %lf", evaluate_polynomial(c));   printf("\n");
  printf("f'(x) = %lf", evaluate_polynomial_derivative(c));   printf("\n");

}
