#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "frac.c"
#define max_n 100

lint lpow(int sol, int n)
{
  lint base = sol;
  for (int i = 1; i < n; i++)
  {
    sol *= base;
  }
  return sol;
}

void gen_pow_sum_vector(lint v[max_n], int n)
{
  v[0] = 1.0;
  for (int i = 1; i <= n; i++)
  {
    v[i] = v[i - 1] + lpow(i + 1, n);
  }
}

void gen_pow_sum_matrix(lint M[max_n][max_n], int n)
{
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j <= n; j++)
    {
      M[i][j] = lpow(i + 1, j + 1);
    }
  }
}

void print_mat(lint M[max_n][max_n], lint v[max_n], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%12ld", M[i][j]);
    }
    printf(" | %12ld", v[i]);
    printf("\n");
  }
}

typedef struct
{
  fraction fm[max_n][max_n];
} fraction_matrix;

void matrix_terms_to_fractions(fraction fm[max_n][max_n],
                               lint M[max_n][max_n], int n)
{
  // fraction_matrix fm;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      fm[i][j] = make_fraction(M[i][j], 1);
    }
  }
}

void vector_terms_to_fractions(fraction fv[max_n], lint v[max_n], int n)
{
  for (int i = 0; i < n; i++)
  {
    fv[i] = make_fraction(v[i], 1);
  }
}

void print_fract_mat(fraction fm[max_n][max_n], fraction fv[max_n], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      print_fraction(" ", fm[i][j], " ");
    }
    print_fraction(" | ", fv[i], "");
    printf("\n");
  }
}

int find_max_row_on_diagonal(fraction u[max_n][max_n], fraction v[max_n], int n, int i)
{

  // int maxfabs = fabs(u[i][i]);
  fraction maxabs = abs_frac(u[i][i]);
  int besth = i;

  for (int h = i; h < n; h++)
  {
    // if (fabs(u[h][i]) > maxfabs) {
    if (first_comp_second(abs_frac(u[h][i]), maxabs) == '>')
    {
      maxabs = abs_frac(u[h][i]);
      besth = h;
    }
  }
  // if (maxabs == 0) {
  if (iszero(maxabs) == 1)
  {
    return -1;
  }
  return besth;
}

void swap_row(int row, int index, fraction u[max_n][max_n], fraction v[max_n], int n)
{
  fraction temp[max_n][max_n];
  fraction t;
  for (int i = 0; i < n; i++)
  {
    t = make_fraction(u[index][i].n, u[index][i].d);
    u[index][i] = make_fraction(u[row][i].n, u[row][i].d);
    u[row][i] = make_fraction(t.n, t.d);
  }
  t = make_fraction(v[index].n, v[index].d);
  v[index] = make_fraction(v[row].n, v[row].d);
  v[row] = make_fraction(t.n, t.d);
  // t = v[index];
  // v[index] = v[row];
  // v[row] = t;
}

int solve(fraction u[max_n][max_n], fraction v[max_n], int n)
{

  for (int i = 0; i < n; i++)
  {
    for (int k = i + 1; k < n; k++)
    {

      int besth = find_max_row_on_diagonal(u, v, n, i);
      if (besth == -1)
        return -1;
      swap_row(i, besth, u, v, n);
      fraction q = frdivide(u[k][i], u[i][i]);
      q.n = -q.n;
      // double q = -u[k][i] / u[i][i];
      for (int j = 0; j < n; j++)
      { // move along the row
        u[k][j] = add_frac(u[k][j], frmul(q, u[i][j]));
        // u[k][j] += q * u[i][j];
      }
      v[k] = add_frac(v[k], frmul(q, v[i]));
      // v[k] += q * v[i];
    }
  }
  // end of loop, in row echelon form
  // assume no row or column is full of zeroes
  v[n - 1] = frdivide(v[n - 1], u[n - 1][n - 1]);
  u[n - 1][n - 1] = frdivide(u[n - 1][n - 1], u[n - 1][n - 1]);
  // v[n - 1] /= u[n - 1][n - 1];
  // u[n - 1][n - 1] /= u[n - 1][n - 1];

  // get zeroes along top-right
  for (int i = n - 1; i >= 0; i--)
  { // move along diagonal
    for (int k = i - 1; k >= 0; k--)
    { // move up rows
      // double q = -u[k][i] / u[i][i];
      fraction q = frdivide(u[k][i], u[i][i]);
      q.n = -q.n;
      for (int j = n - 1; j >= i; j--)
      { // move along the row from right
        // u[k][j] += q * u[i][j];
        u[k][j] = add_frac(u[k][j], frmul(q, u[i][j]));
      }
      // v[k] += q * v[i];
      v[k] = add_frac(v[k], frmul(q, v[i]));
    }
  } // end of loop, // zeroes everywhere except diagonal

  for (int i = 0; i < n; i++)
  { // get 1's along diagonal
    v[i] = frdivide(v[i], u[i][i]);
    u[i][i] = frdivide(u[i][i], u[i][i]);
    // v[i] /= u[i][i];
    // u[i][i] /= u[i][i];
  }

  // for (int i = 0; i < n; i++)
  // {
  //   for (int j = 0; j < n; j++)
  //   {
  //     if (isnan(u[i][j]))
  //       return -1;
  //   }
  // }

  return 1;
}

void print_poly_fract(fraction fv[max_n], int n)
{
  for (int i = n - 1; i >= 0; i--)
  {
    print_fraction("", fv[i], "");
    if(i != 0) printf("n^%d + ", i + 1);
    else printf("n^%d\n", i + 1);
  }
}

int main()
{
  int n = 2;
  lint v[max_n], M[max_n][max_n];

  gen_pow_sum_vector(v, n);
  gen_pow_sum_matrix(M, n);
  n += 1;
  fraction fm[max_n][max_n];
  matrix_terms_to_fractions(fm, M, n);
  fraction fv[max_n];
  vector_terms_to_fractions(fv, v, n);
  print_fract_mat(fm, fv, n);

  printf("--------------------------\n");
  solve(fm, fv, n);
  print_fract_mat(fm, fv, n);
  printf("--------------------------\n");
  print_poly_fract(fv, n);
}