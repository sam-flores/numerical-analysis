#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FPToolkit.c"
#include <unistd.h>
#include "create_nx3_spline_system.c"
#include "solve_nx3_spline_system.c"

#define max_n 100

void solve_nx3_system(double v[], double x[], double y[], int n)
{
  double lower[2*max_n], middle[2*max_n], upper[2*max_n];
  n -= 1;
  n *= 2;
  create_nx3_system(lower, middle, upper, v, x, y, n);
  normalize_matrix(lower, middle, upper, v, n);
  nx3_eliminate_lower_diagonal(lower, middle, upper, v, n);
  nx3_eliminate_upper_diagonal(lower, middle, upper, v, n);
  nx3_eliminate_middle_diagonal(lower, middle, upper, v, n);
  printf("----------------------------solved-------------\n");
  print_nx3_system(lower, middle, upper, v, n);
}

double get_y(double x0, double x1, double y0, double y1, double A, double B, double t)
{
  return y0 + ((y1 - y0) / (x1 - x0)) * (t - x0) + A * (t - x0) * (t - x1) + B * (t - x0) * (t - x0) * (t - x1);
}

void draw_spline(double x[], double y[], double v[], int n)
{

  double delta = .001;
  for (int i = 0; i < n - 1; i++)
  {
    for (double t = x[i]; t < x[i + 1]; t += delta)
    {
      G_point(t, get_y(x[i], x[i + 1], y[i], y[i + 1], v[2*i], v[2*i + 1], t));
    }
  }
}

double f(double x, double t){
	double fx = 17  +  (14 - 8*cos(t) + cos(2*x)) * cos(2*x)   - 24*cos(x);
	fx /= (x*exp(x) - x) * (1 + 2*x*x - cos(2*t) - 4*x*sin(x));
	return fx;
}


void draw_axes(double width, double height, double a, double b){
	G_rgb(0, 0, 1);
	double normalize = width/(b - a);
	double middle = normalize*(a + b)/2;
	G_line(0, height/2, width, height/2);
	G_line(width/2 - middle, height, width/2 - middle, 0);
}

int graph(double (*f)(double x, double t), double a, double b, 
	double width, double height, double t,
	double xp[], double yp[], int n){
	double x = a;
	double delta = (b - a) / (double)n;
	double normalize = width/(b - a);
	double middle = normalize*(a + b)/2;
	G_rgb(0, 1, 0);
	for(int i = 1; i <= n; i++){
		xp[i - 1] = x*normalize + width/2 - middle;
		yp[i - 1] = f(x, t)*normalize + height/2;
		G_point(xp[i - 1], yp[i - 1]);
		x += delta;
	}
	return n;
}

int main(){

	double width = 600, height = 600;
	G_init_graphics(width, height);
	G_rgb(0, 0, 0);
	G_clear();

	double a = -10, b = 10;
	int q = 0;
	double t = 0;
	double x[max_n], y[max_n], v[2*max_n];
	int n = 11;
	while(q != 'q'){	
		draw_axes(width, height, a, b);
		graph(f, a, b, width, height, t, x, y, n);
		solve_nx3_system(v, x, y, n);
  	G_rgb(0, 1, 1);
  	draw_spline(x, y, v, n);
		G_display_image();
		q = G_no_wait_key();
		usleep(10000);
		if(q == 65362){
			a /= 2;
			b /= 2;
		}else if(q == 65364){
			a *= 2;
			b *= 2;
		}else if(q == 65363){
			a += 1;
			b += 1;
		}else if(q == 65361){
			a -= 1;
			b -= 1;
		}
		G_rgb(0, 0, 0);
		G_clear();
		t+=.1;

	}

}