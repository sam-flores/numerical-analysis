#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FPToolkit.c"

// e_n+1 ~ Q*e_n^2, Q =f''(R)/2*f'(R)
int screen_size = 600;
#define max_n 10000

typedef struct{
	double a;
	double b;
}domain;

domain dom;
domain ran;

double f(double x){
	return x*x*x*x - 1;
	return sin(x);
	return x*x*x - 30*x - 36;
}

double fprime(double x){
	return 4*x*x*x;
	return cos(x);
	return 3*x*x - 30;
}

void draw_axes(domain dom, domain ran)
{
	G_rgb(0, 0, 1);
	double normalize = screen_size / (dom.b - dom.a);
	double middle = normalize * (dom.a + dom.b) / 2;
	double middle_y = normalize * (ran.a + ran.b) / 2;
	double half_screen_size = screen_size/2;
	G_line(0, half_screen_size - middle_y, screen_size, half_screen_size - middle_y);
	G_line(half_screen_size - middle, screen_size, half_screen_size - middle, 0);
}

double fit_x(double x, domain dom){
	double normalize = screen_size / (dom.b - dom.a);
	double middle_x = normalize * (dom.b + dom.a) / 2;
	return x * normalize + screen_size / 2 - middle_x;
}

double fit_y(double y, domain ran){
	double normalize = screen_size / (ran.b - ran.a);
	double middle_y = normalize * (ran.b + ran.a) / 2;
	return y * normalize + screen_size / 2 - middle_y;
}

void graph(double (*f)(double x),
		   domain dom, domain ran, int n)
{
	double x = dom.a;
	double delta = (dom.b - dom.a) / (double)n;
	G_rgb(0, 1, 0);
	for (int i = 1; i <= n + 1; i++)
	{
		G_point(fit_x(x, dom), fit_y(f(x), ran));
		x += delta;
	}
}

void color_roots(double (*f)(double x), 
				double (*fprime)(double x),
				domain dom, domain ran){

	double guess = dom.a;
	int n = 100;
	double delta = (dom.b - dom.a) / (double)n;
	double x = guess;
	for (int i = 1; i <= n + 1; i++)
	{	
		int iterations = 100;
		double g = x;
		// main loop
		for(int j = 0; j < iterations; j++){
			x = x - (f(x)/fprime(x));	
		}
		G_rgb(x/1, .4, .4/x);
		G_circle(fit_x(g, dom), fit_y(0, ran), 2);
		G_display_image();
		x = guess + i*delta;
	}	
	
}

int main(){

	G_init_graphics(screen_size, screen_size);
	G_rgb(0, 0, 0);
	G_clear();

	dom.a = -4*M_PI/3;
	dom.b = 4*M_PI/3;
	ran.a = -4*M_PI/3;
	ran.b = 4*M_PI/3;

	double x = 5; // initial guess

	double a = -4*M_PI/3, b = 4*M_PI/3;
	double c = -1, d = 1;
	int q = 0;
	double t = 0;
	int n = 1000;
	draw_axes(dom, ran);
	graph(f, dom, ran, n - 1);
	color_roots(f, fprime, dom, ran);
	G_display_image();

	G_wait_key();
}