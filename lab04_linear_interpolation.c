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

void generate_newton_coeffs(double a[], double x[], double y[], int n){
  a[0] = y[0];
  double fake_y[n];
  for(int i = 0; i < n; i++){
    fake_y[i] = y[i];
  }
  double slopes[n];
  for(int i = 1; i < n; i++){
    for(int j = 0; j < n - i; j++){
      slopes[j] = ((fake_y[j + 1] - fake_y[j]) / (x[j + i] - x[j]));
    }
    for(int j = 0; j < n - i; j++){
      fake_y[j] = slopes[j];
    }
    a[i] = slopes[0];
  }
}

double evaluate_newton_poly(double x[], double a[], int n, double t){
  double res = a[0];
  double coeff = (t - x[0]);
  for(int i = 1; i < n; i++){
    res += a[i]*coeff;
    coeff *= (t - x[i]);
  }
  return res;
}

double evaluate_lagrange_poly(double x[], double y[], int n, double t){

  double res = 0;
  double frac;
  double num, den;
  for(int i = 0; i < n; i++){
    frac = y[i];
    num = 1;
    for(int j = 0; j < n; j++){
      if(j != i) num *= t - x[j];
    }
    frac *= num;
    den = 1;
    for(int j = 0; j < n; j++){
      if(j != i) den *= x[i] - x[j];
    }
    frac /= den;
    res += frac;
  }
  return res;
}

void draw_lagrange_lerp(double x[], double y[], int n){
  double delta = 0.01;

  for(double t = x[0]; t < x[n - 1]; t += delta){
      G_point(t, evaluate_lagrange_poly(x, y, n, t));
  }
}

void draw_newton_lerp(double x[], double y[], int n){

  double delta = 0.01;
  double v;
  double a[n];
  generate_newton_coeffs(a, x, y, n);

  for(double t = x[0]; t < x[n - 1]; t += delta){
      G_point(t, evaluate_newton_poly(x, a, n, t));
  }
}

int main()
{

  int n;
  double x[max_n], y[max_n];
  
  G_init_graphics(600, 600);
  G_rgb(0, 0, 0);
  G_clear();
  n = clickandsave(x, y);

  G_rgb(0, 1, 0);
  draw_newton_lerp(x, y, n);
  G_wait_key();
  G_rgb(1, 0, 1);
  draw_lagrange_lerp(x, y, n);

  G_wait_key();
}