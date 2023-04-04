#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	double i;
	double x;
	double n;

	while(i > 0){
		n = 10*(1 + 1*sin(i));
		for(int j = 0; j < n; j++){
			printf(" ");
		}
		usleep(10000);
		printf(" i am worm \n");
		i+=4*M_PI/180;
	}
}