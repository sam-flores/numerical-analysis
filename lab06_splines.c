#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FPToolkit.c"
#define max_n 100

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
  double lower[max_n], middle[max_n], upper[max_n];
  n *= 2;
  n -= 2;
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

  int n = 8;
  double x[max_n], y[max_n];
  double v[max_n];

  // double x[8] = {86, 177, 249, 311, 381, 416, 455, 551};
  // double y[8] = {181, 211, 315, 460, 459, 311, 195, 155};
  G_init_graphics(600, 600);
  G_rgb(0, 0, 0);
  G_clear();
  n = clickandsave(x, y);
  
  // solve_nxn_system(v, x, y, n);
  // G_rgb(0, 1, 0);
  // draw_spline(x, y, v, n);
  
  solve_nx3_system(v, x, y, n);
  G_rgb(0, 1, 1);
  draw_spline(x, y, v, n);

  G_wait_key();
}