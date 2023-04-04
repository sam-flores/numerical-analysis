#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
// f(x) = 2xxx-9xx+32x+75, f'(x) = 6xx-18x+32

#include <string.h>


void prcmx (char *control, complex c)
{
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


int main()
{
  double cr, ci;
  complex c;

  scanf("%lf %lf", &cr, &ci);
  c = cr + ci*I;
  printf("%lf + %lfI\n", creal(c), cimag(c));
  for(int i = 1; i<=15; i++){
    c = c - f(c)/fprime(c);
    printf("%20.16lf + %20.16lfI\n", creal(c), cimag(c));
  }
  printf("-------------------------------\n");
  prcmx("%lf", c);   printf("\n");
  prcmx("%lf", f(c));   printf("\n");

}
