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

void print_system(double u[max_n][max_n], double v[max_n], int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%12.8lf", u[i][j]);
    }
    printf(" | %12.8lf", v[i]);
    printf("\n");
  }
}

void create_system(double u[][], double v[], double x[], double y[], int n){

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      
    }
  }

}

int main()
{

  int n = 8;
  // double x[max_n], y[max_n];

  double x[8] = {86, 177, 249, 311, 381, 416, 455, 551};
  double y[8] = {181, 211, 315, 460, 459, 311, 195, 155};
  double u[max_n][max_n], v[max_n];
  create_system(u, v, x, y, n);
  print_system(u, v, n);

  G_init_graphics(600, 600);
  G_rgb(0, 0, 0);
  G_clear();
  n = clickandsave(x, y);
  G_wait_key();
}