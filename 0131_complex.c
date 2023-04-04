#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

int main()
{
  complex a,b,c,d,e,f;
  a = 3 + 4*I;
  b = 2 + 3*I;
  c = a + b;
  d = a - b;
  e = a * b;
  f = a / b;
  printf("%lf + %lfI\n", creal(a),cimag(a));
  printf("%lf + %lfI\n", creal(b),cimag(b));
  printf("%lf + %lfI\n", creal(c),cimag(c));
  printf("%lf + %lfI\n", creal(d),cimag(d));
  printf("%lf + %lfI\n", creal(e),cimag(e));
  printf("%lf + %lfI\n", creal(f),cimag(f));
  printf("%lf\n", cabs(a));
}