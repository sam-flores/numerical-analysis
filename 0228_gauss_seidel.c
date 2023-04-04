#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(){

	double x1, x2, x3, x4;

	x1 = x2 = x3 = x4 = 0;

	// converges to solution of system
	for(int i = 1; i <= 15; i++){
		x1 = (498 - 5*x2 - 8*x3 + 2*x4)/100;
		x2 = (834 - 4*x1 - 2*x3 - 6*x4)/200;
		x3 = (6 - 2*x1 - 1*x2 - 4*x4)/10;
		x4 = (255 - 5*x1 - 15*x2 + 10*x3)/50; 
		printf("%20.16lf %20.16lf %20.16lf %20.16lf \n", x1, x2, x3, x4);
	}


}

/*
when does this work. when the matrix is diagonally dominant.
diagonal dominance => max row sum < 1 => convergence of gauss-seidel


100x1 + 5x2 + 8x3 - 2x4 = 498 => solve for x1
4x1 + 200x2 + 2x3 + 6x4 = 834
2x1 + 1x2 + 10x3 + 4x4 = 6
5x1 + 15x2 - 10x3 + 50x4 = 255

x_new = constants - matrix*x_old

x[] = c[] - m[][]*x[]

x1 = (498/100) - [(0/100)*x1 + (5/100*x2)]






*/