#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "FPToolkit.c"

// e_n+1 ~ Q*e_n^2, Q =f''(R)/2*f'(R)
int screen_size = 600;

typedef struct
{
	double a;
	double b;
} domain;

typedef struct
{
	double x;
	double y;
} point;

complex double f(complex double x)
{
	// return x*x + 4;
	return x * x * x * x - 1;
	// return sin(x);
	// return x * x * x - 30 * x - 36;
}

complex double fprime(complex double x)
{
	// return 2*x;
	return 4 * x * x * x;
	// return cos(x);
	// return 3*x*x - 30;
}

double domain_to_screen(double p, domain dom)
{
	double normalize = screen_size / fabs(dom.b - dom.a);
	return (p - (dom.a + dom.b) / 2) * normalize + screen_size / 2;
}

double screen_to_domain(double p, domain dom)
{
	double normalize = fabs(dom.b - dom.a) / screen_size;
	return (p - screen_size / 2) * normalize + (dom.a + dom.b) / 2;
}

void draw_axes(domain dom, domain ran)
{
	G_rgb(0, 0, 1);
	double half_range = (ran.b + ran.a) / 2;
	double half_domain = (dom.b + dom.a) / 2;
	double x_axis = domain_to_screen(half_range, ran);
	double y_axis = domain_to_screen(half_domain, dom);

	G_line(0, x_axis, screen_size, x_axis);
	G_line(y_axis, 0, y_axis, screen_size);
}

void graph(complex double (*f)(complex double x),
		   domain dom, domain ran, int n,
		   point center)
{
	double x = dom.a;
	double delta = (dom.b - dom.a) / (double)n;
	G_rgb(0, 1, 0);
	for (int i = 1; i <= n + 1; i++)
	{
		G_point(domain_to_screen(x, dom),
				domain_to_screen(f(x), ran));
		x += delta;
	}
}

void color_roots(complex double (*f)(complex double x),
				 complex double (*fprime)(complex double x),
				 domain dom, domain ran)
{

	double guess_real = dom.a;
	double guess_complex = ran.a;
	int n = 300;
	double delta_real = (dom.b - dom.a) / (double)n;
	double delta_complex = (ran.b - ran.a) / (double)n;
	complex double x = guess_real + guess_complex * I;

	for (int h = 1; h <= n; h++)
	{
		guess_real = dom.a;
		for (int i = 1; i <= n; i++)
		{
			int iterations = 100;
			for (int j = 0; j <= iterations; j++)
			{
				x = x - (f(x) / fprime(x));
			}
			G_rgb((creal(x) + (dom.b - dom.a) / 2) / (dom.b - dom.a),
				  0,
				  (cimag(x) + (ran.b - ran.a) / 2) / (ran.b - ran.a));
			G_point(domain_to_screen(guess_real, dom),
					 domain_to_screen(guess_complex, ran));
			// G_display_image();
			guess_real += delta_real;
			x = guess_real + guess_complex * I;
		}
		guess_complex += delta_complex;
	}
}

void get_dom_range(double data[], domain dom, domain ran, point center,
				   double p[2], double factor)
{

	p[0] = screen_to_domain(p[0], dom);
	p[1] = screen_to_domain(p[1], ran);
	center.x = p[0];
	center.y = p[1];
	dom.a = center.x + (dom.a - center.x) * factor;
	dom.b = center.x + (dom.b - center.x) * factor;
	ran.a = center.y + (ran.a - center.y) * factor;
	ran.b = center.y + (ran.b - center.y) * factor;
	data[0] = dom.a;
	data[1] = dom.b;
	data[2] = ran.a;
	data[3] = ran.b;
}

int main()
{

	G_init_graphics(screen_size, screen_size);
	int q = '0';
	int n = 1000;
	double center_p[2], rad[2];
	point center;
	domain dom;
	domain ran;
	double data[4] = {-1, 1, -1, 1};
	dom.a = data[0];
	dom.b = data[1];
	ran.a = data[2];
	ran.b = data[3];
	center.x = (dom.a + dom.b) / 2;
	center.y = (ran.a + ran.b) / 2;

	while (q != 'q')
	{
		G_rgb(0, 0, 0);
		G_clear();
		// draw_axes(dom, ran);
		// graph(f, dom, ran, n - 1, center);
		color_roots(f, fprime, dom, ran);
		G_display_image();
		// G_wait_click(center_p);
		center_p[0] = screen_size * .75;
		center_p[1] = screen_size * .75;
		// G_rgb(0, 1, 1);
		// G_circle(center_p[0], center_p[1], 4);
		// q = G_wait_key();
		// if (q == 'w')
		get_dom_range(data, dom, ran, center, center_p, .8);
		// else if (q == 's')
			// get_dom_range(data, dom, ran, center, center_p, 2);
		dom.a = data[0];
		dom.b = data[1];
		ran.a = data[2];
		ran.b = data[3];
		center.x = (ran.a + ran.b) / 2;
		center.y = (dom.a + dom.b) / 2;
	}
}