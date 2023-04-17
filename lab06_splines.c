#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FPToolkit.c"
#define max_n 100000

#include "create_nxn_spline_system.c"
#include "create_nx3_spline_system.c"
#include "solve_nx3_spline_system.c"

int clickandsave(double x[], double y[])
{
  double xp, yp, p[2];
  int numpoints;

  G_rgb(1, 0, 0); // red
  G_fill_rectangle(0, 0, 30, 30);

  G_rgb(0.5, 0.5, 0.5);
  numpoints = 0;
  while (0 == 0)
  {

    G_wait_click(p);
    xp = p[0];
    yp = p[1];

    if ((xp >= 0) && (xp <= 30) &&
        (yp >= 0) && (yp <= 30))
    {
      break;
    }

    G_fill_rectangle(xp - 2, yp - 2, 4, 4);

    x[numpoints] = xp;
    y[numpoints] = yp;
    numpoints++;
  }

  return numpoints;
}

int gen_points(double x[], double y[], int width, int height)
{
  int numpoints = 50;
  G_rgb(0.5, 0.5, 0.5);
  double max_delta = 2*width / numpoints;
  x[0] = 0;
  y[0] = height/2 + (drand48()-.5) * (height/2);
  for(int i = 1; i < numpoints; i++){
    x[i] = x[i - 1] +max_delta;
    y[i] = 100 + drand48()*(height - 100);
    G_fill_rectangle(x[i] - 2, y[i] - 2, 4, 4);
  }

  return numpoints;
}


void solve_nxn_system(double v[], double x[], double y[], int n)
{
  double u[max_n][max_n];
  n *= 2;
  n -= 2;
  create_system(u, v, x, y, n);
  print_system(u, v, n);
  solve(u, v, n);
  printf("----------------------------solved-------------\n");
  print_system(u, v, n);
}

void solve_nx3_system(double v[], double x[], double y[], int n)
{
  double lower[2*max_n], middle[2*max_n], upper[2*max_n];
  n -= 1;
  n *= 2;
  create_nx3_system(lower, middle, upper, v, x, y, n);
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

int main()
{

  int n;
  double x[max_n], y[max_n];
  double v[2*max_n];
  // double x[8] = {86, 87, 88, 90, 102, 110, 200, 551};
  // double y[8] = {181, 211, 315, 460, 459, 311, 195, 155};
  int width = 600, height = 600;
  G_init_graphics(width, height);
  G_rgb(0, 0, 0);
  G_clear();
  n = gen_points(x, y, width, height);
  // n = clickandsave(x, y);
  
  // solve_nxn_system(v, x, y, n);
  // G_rgb(0, 1, 0);
  // draw_spline(x, y, v, n);
  
  solve_nx3_system(v, x, y, n);
  G_rgb(0, 1, 1);
  draw_spline(x, y, v, n);

  G_wait_key();
}