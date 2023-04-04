#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "frac.c"

int main()
{

    fraction a, b;

    a = make_fraction(9, 6);
    b = make_fraction(2, 4);
    print_fraction("added", add_frac(a, b),"\n");
}