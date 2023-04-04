#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>

// f(x) = 2xxx-9xx+32x+75, f'(x) = 6xx-18x+32

double coefficients[100], prime_coefficients[100];
int n;

void prcmx (char *control, complex c){
  double a,b ;
  a = creal(c) ;
  b = cimag(c) ;

  printf(control,a) ;
  if (b >= 0) {
    printf("+") ;
  } else {
    printf("-") ;
  }
  printf(control,fabs(b)) ;  
  printf("I") ;
}


complex f(complex x){
  return (2*x*x*x-9*x*x+32*x+75);
}

complex fprime(complex x){
  return (6*x*x-18*x+32);
}

complex poly(complex x){
  complex answer = 0;
  complex p = 1;
  for(int i = 0; i <= n; i++){
    answer += coefficients[i]*p;
    p *= x;
  }
  return answer;
}

complex polyprime(complex x){
  complex answer = 0;
  complex p = 1;
  for(int i = 0; i < n; i++){
    answer += prime_coefficients[i]*p;
    p *= x;
  }
  return answer;
}

void handle_user_input(){

  printf("enter polynomial up to 100\n");
  scanf("%d", &n);
  printf("\n");
  for (int i = n; i >= 0; i--){
    scanf("%lf", &coefficients[i]);
    if(i > 0) prime_coefficients[i - 1] = (i)*coefficients[i];
  }
}

int main()
{
  double cr, ci;
  complex c;

  handle_user_input();
  scanf("%lf %lf", &cr, &ci);
  printf("initial guess: ");
  c = cr + ci*I;
  printf("%lf + %lfI\n", creal(c), cimag(c));
  for(int i = 1; i<=15; i++){
    c = c - poly(c)/polyprime(c);
    printf("%20.16lf + %20.16lfI\n", creal(c), cimag(c));
  }
  printf("-------------------------------\n");
  prcmx("%lf", c);   printf("\n");
  prcmx("%lf", f(c));   printf("\n");

}
