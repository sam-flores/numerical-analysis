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

void get_group_of_four_points(double input_points[4][2], double x[max_n], double y[max_n], int i, int n){
  for(int j = 0; j < 4; j++){
    input_points[j][0] = x[(i + j) % n];
    input_points[j][1] = y[(i + j) % n];
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
  G_wait_key();
}