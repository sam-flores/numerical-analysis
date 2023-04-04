#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void adding(){

	printf("adding oddity\n");
	printf("-------------------------\n");

	double x,y;
	x = .1;
	y = x+x+x+x+x+x+x+x+x+x;
	printf("%lf\n",y);
	if(y == 1) printf("one\n");
	else printf("not one\n");

	printf("-------------------------\n");
}

void delta_loop(){
	
	printf("delta loop oddity\n");
	printf("-------------------------\n");

	double x;
	double delta = .1;
	for(x = 0.0; x < 1.0; x += delta){
		printf("%lf\n",x);
	}

	printf("-------------------------\n");
}

void large_number(){

	printf("large number oddity\n");
	int x, y, z;

	x = 2000000000;
	y = 2000000000;
	z = x + y;
	printf("x = %d y = %d z = %d\n", x, y, z);
	printf("-------------------------\n");
}

int main(){

	adding();
	delta_loop();
	large_number();

}