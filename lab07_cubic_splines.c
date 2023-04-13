#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FPToolkit.c"
#define max_n 100

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

int find_max_row_on_diagonal(double u[max_n][max_n], double v[max_n], int n, int i)
{

  int maxfabs = fabs(u[i][i]);
  int besth = i;

  for (int h = i; h < n; h++)
  {
    if (fabs(u[h][i]) > maxfabs)
    {
      maxfabs = fabs(u[h][i]);
      besth = h;
    }
  }
  if (maxfabs == 0)
  {
    return -1;
  }
  return besth;
}

void swap_row(int row, int index, double u[max_n][max_n], double v[max_n], int n)
{
  double temp[max_n][max_n];
  double t;
  for (int i = 0; i < n; i++)
  {
    t = u[index][i];
    u[index][i] = u[row][i];
    u[row][i] = t;
  }
  t = v[index];
  v[index] = v[row];
  v[row] = t;
}

int solve(double u[max_n][max_n], double v[max_n], int n)
{

  for (int i = 0; i < n; i++)
  {
    for (int k = i + 1; k < n; k++)
    {

      int besth = find_max_row_on_diagonal(u, v, n, i);
      if (besth == -1)
        return -1;
      swap_row(i, besth, u, v, n);

      double q = -u[k][i] / u[i][i];
      for (int j = 0; j < n; j++)
      { // move along the row
        u[k][j] += q * u[i][j];
      }
      v[k] += q * v[i];
    }
  }
  // end of loop, in row echelon form
  // assume no row or column is full of zeroes
  v[n - 1] /= u[n - 1][n - 1];
  u[n - 1][n - 1] /= u[n - 1][n - 1];

  // get zeroes along top-right
  for (int i = n - 1; i >= 0; i--)
  { // move along diagonal
    for (int k = i - 1; k >= 0; k--)
    { // move up rows
      double q = -u[k][i] / u[i][i];
      for (int j = n - 1; j >= i; j--)
      { // move along the row from right
        u[k][j] += q * u[i][j];
      }
      v[k] += q * v[i];
    }
  } // end of loop, // zeroes everywhere except diagonal

  for (int i = 0; i < n; i++)
  { // get 1's along diagonal
    v[i] /= u[i][i];
    u[i][i] /= u[i][i];
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (isnan(u[i][j]))
        return -1;
    }
  }

  return 1;
}

void print_system(double u[100][100], double v[100], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("row %2.1d :", i);
    for (int j = 0; j < n; j++)
    {
      printf("%2.0lf", u[i][j]);
    }
    printf(" | %12.8lf", v[i]);
    printf("\n");
  }
}

void create_system(double u[100][100], double v[100], int n)
{
  // init all zeroes
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      u[i][j] = 0;
    }
    v[i] = 0;
  }

  // zeroth deriv equations
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      u[i][(i * 4 + j) % 16] = 1;
    }
    if ((i + 1) % 4 != 0)
      u[i + 1][(i * 4) % 16] = -1;
  }

  u[4][n - 1 - 3] = 1;

  for (int i = 5; i < 9; i++)
  {
    u[i][1 + (i - 5) * 4] = 1;
    u[i][2 + (i - 5) * 4] = 2;
    u[i][3 + (i - 5) * 4] = 3;
    u[i + 1][((i - 5) * 4) % 16 + 1] = -1;
  }
  u[9][n - 1 - 2] = 1;

  for (int i = 10; i < 14; i++)
  {
    u[i][(((i - 10) * 4) + 2) % 16] = 2;
    u[i][(((i - 10) * 4) + 3) % 16] = 6;
    u[i + 1][((i - 10) * 4) % 16 + 2] = -2;
  }
  u[14][n - 1 - 1] = 2;

  // load in last row's 1
  for (int i = 0; i < 4; i++)
  {
    u[n - 1][i * 4] = 1;
  }
  v[n - 1] = 1;
}

double evaluate_polynomial(double coefficients[], int degree, double x)
{
  double answer = 0;
  double p = 1;
  for (int i = 0; i <= degree; i++)
  {
    answer += coefficients[i] * p;
    p *= x;
  }
  return answer;
}

void get_point_from_cubic_spline(double p[2], double input_points[4][2],
                                 double v[4][4], double t)
{

  p[0] = 0;
  p[1] = 0;
    for (int i = 0; i < 4; i++)
    {
      p[0] += evaluate_polynomial(v[i], 3, t)*input_points[i][0];
      p[1] += evaluate_polynomial(v[i], 3, t)*input_points[i][1];
    }
}
void get_group_of_four_points(double input_points[4][2], double x[max_n], double y[max_n], int i, int n){
  for(int j = 0; j < 4; j++){
    input_points[j][0] = x[(i + j) % n];
    input_points[j][1] = y[(i + j) % n];
  }
}

void draw_cubic_spline(double v[4][4], double x[max_n], double y[max_n], int n)
{

  double p[2], input_points[4][2];
  double delta = .001;
  for (int i = 0; i < n; i++)
  {
    get_group_of_four_points(input_points, x, y, i, n);
    for (double t = 0; t < 1; t += delta)
    {
      get_point_from_cubic_spline(p, input_points, v, t);
      G_rgb(0, 1, 0);
      G_point(p[0], p[1]);
    }
  }
}

void convert_v_to_2D_array(double cubic_coeffs[4][4], double v[max_n]){
  for(int i = 0; i < 16; i++){
    cubic_coeffs[i / 4][i % 4] = v[i];
  }
}

int main()
{

  int n = 16;
  double u[max_n][max_n], v[max_n];
  create_system(u, v, n);
  print_system(u, v, n);
  printf("----------------solve-----------------\n");
  printf("\n%d\n", solve(u, v, n));
  print_system(u, v, n);

  double cubic_coeffs[4][4];
  convert_v_to_2D_array(cubic_coeffs, v);

  double x[max_n], y[max_n];
  G_init_graphics(600, 600);
  G_rgb(0, 0, 0);
  G_clear();
  n = clickandsave(x, y);
  draw_cubic_spline(cubic_coeffs, x, y, n);
  G_wait_key();
}