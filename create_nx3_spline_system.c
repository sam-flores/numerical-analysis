#define max_n 100

void load_nx3_diagonal(double u[max_n], double x[max_n], int n)
{
  u[0] = 1;
  for (int i = 1; i < n; i++)
  {
    u[2 * i] = -(x[i + 1] - x[i - 1]);
    u[2 * i - 1] = (x[i] - x[i - 1]) * (x[i] - x[i - 1]);
  }
  u[n - 1] = 2 * (x[(n + 2) / 2 - 1] - x[(n + 2) / 2 - 2]);
}

void load_nx3_lower_diagonal(double u[max_n], double x[8], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    u[2 * i - 1 - 1] = (x[i] - x[i - 1]);
    u[2 * i - 1] = (x[i] - x[i - 1]) * (x[i] - x[i - 1]);
  }
  u[n - 2] = 1;
}

void load_nx3_upper_diagonal(double u[max_n], double x[8], int n)
{
  u[1] = -(x[1] - x[0]);
  for (int i = 1; i < n; i++)
  {
    u[2 * i - 1 + 1] = (x[i + 1] - x[i]);
    u[2 * i + 1] = (x[i] - x[i - 1]) * (x[i + 1] - x[i]);
  }
}

void load_nx3_v(double v[max_n], double x[8], double y[8], int n){
  v[0] = 0;
  for(int i = 1; i < n - 1; i++){
    v[2*i - 1] = (y[i + 1] - y[i])/(x[i + 1] - x[i]) - (y[i] - y[i - 1])/(x[i] - x[i - 1]);
    v[2*i] = -(y[i + 1] - y[i])/(x[i + 1] - x[i]) + (y[i] - y[i - 1])/(x[i] - x[i - 1]);
  }
  v[n - 1] = 0;
}

void create_nx3_system(double lower[max_n],
                       double middle[max_n],
                       double upper[max_n],
                       double v[max_n],
                       double x[max_n], double y[max_n], int n)
{
  load_nx3_diagonal(middle, x, n);
  load_nx3_lower_diagonal(lower, x, n);
  load_nx3_upper_diagonal(upper, x, n);
  load_nx3_v(v, x, y, n);
}

void print_nx3_system(double lower[max_n],
                      double middle[max_n],
                      double upper[max_n],
                      double v[max_n], int n)
{
  int zero = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (j == i - 1)
        printf("%10.2lf", lower[j]);
      else if (j == i)
        printf("%10.2lf", middle[j]);
      else if (j == i + 1)
        printf("%10.2lf", upper[j]);
      else
        printf("%10.2d", zero);
    }
    printf(" | %20.16lf", v[i]);
    printf("\n");
  }
}