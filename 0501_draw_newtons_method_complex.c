#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
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

complex f(complex x){
	return x*x*x*x - 1;
	// return cos(x);
	return x*x*x - 30*x - 36;
}

complex fprime(complex x){
	return 4*x*x*x;
	// return cos(x);
	// return 3*x*x - 30;
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

void graph(complex (*f)(complex x),
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

void color_roots(complex (*f)(complex x), 
				complex (*fprime)(complex x),
				domain dom, domain ran){

	double guess_real = dom.a;
	double guess_complex = ran.a;
	int n = 1000;
	double delta_real = (dom.b - dom.a) / (double)n;
	double delta_complex = (ran.b - ran.a) / (double)n;
	complex x = guess_real + guess_complex*I;

	for (int h = 1; h <= n + 1; h++)
	{
		guess_real = dom.a;
		for (int i = 1; i <= n + 1; i++)
		{
			int iterations = 50;
			for(int j = 1; j <= iterations; j++){
				x = x - (f(x)/fprime(x));	
			}
			G_rgb((creal(x) + (dom.b - dom.a) / 2) / (dom.b - dom.a),
				  0,
				  (cimag(x) + (ran.b - ran.a) / 2) / (ran.b - ran.a));
			G_circle(fit_x(guess_real, dom), fit_y(guess_complex, ran), 2);
			// G_display_image();
			guess_real += delta_real;
			x = guess_real + guess_complex*I;
		}
		guess_complex += delta_complex;
	}	
}

double fit_inv_y(double y, domain ran){
	double normalize = (ran.b - ran.a) / screen_size;
	double middle_y = normalize * (ran.b + ran.a) / 2;
	return y * normalize - (ran.b + ran.a) / 2 - middle_y;
}

double fit_inv_x(double x, domain dom){
	double normalize = screen_size / (dom.b - dom.a);
	double middle_x = normalize * (dom.b + dom.a) / 2;
	return x / normalize - screen_size / 2 + middle_x;
}

void get_dom_range(domain dom, domain ran, double p[2], double q[2]){
	p[0] = fit_inv_x(p[0], dom);
	p[1] = fit_inv_y(p[1], ran);

	printf("%lf %lf \n", p[0], p[1]);
}

int main(){

	G_init_graphics(screen_size, screen_size);
	G_rgb(0, 0, 0);
	G_clear();
	int q = '0';
	int n = 1000;
	double center_p[2], rad[2];
	while(q != 'q'){
		dom.a = -1;
		dom.b = 1;
		ran.a = -1;
		ran.b = 1;
		draw_axes(dom, ran);
		graph(f, dom, ran, n - 1);
		// color_roots(f, fprime, dom, ran);
		G_display_image();
		// G_wait_click(center_p);
		// G_wait_click(rad);
		center_p[0] = screen_size*.75;
		center_p[1] = screen_size*.5;

		get_dom_range(dom, ran, center_p, rad);

		q = G_wait_key();
	}
}