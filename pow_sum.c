#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define max_n 100


int find_max_row_on_diagonal(double u[max_n][max_n], double v[max_n], int n, int i){
      
      int maxfabs = fabs(u[i][i]); 
      int besth = i ;
      
      for (int h = i ; h < n ; h++) {
        if (fabs(u[h][i]) > maxfabs) {
         maxfabs = fabs(u[h][i]); 
         besth = h; 
       }
      }
      if (maxfabs == 0) {
        return -1;
      }
      return besth;
}

void swap_row(int row, int index, double u[max_n][max_n], double v[max_n], int n){
  double temp[max_n][max_n];
  double t;
  for(int i = 0; i < n; i++){
    t = u[index][i];
    u[index][i] = u[row][i];
    u[row][i] = t;
  }
      t = v[index];
      v[index] = v[row];
      v[row] = t;
}

int solve(double u[max_n][max_n], double v[max_n], int n){

    
    for(int i = 0; i < n; i++){
      for(int k = i + 1; k < n; k++){

      int besth = find_max_row_on_diagonal(u, v, n, i);
      if(besth == -1) return -1;
      swap_row(i, besth, u, v, n);

        double q = -u[k][i]/u[i][i];
        for(int j = 0; j < n; j++){ // move along the row
          u[k][j] += q*u[i][j];
        }
        v[k] += q*v[i];
      }
    }
    // end of loop, in row echelon form
    // assume no row or column is full of zeroes
    v[n-1] /= u[n-1][n-1];
    u[n-1][n-1] /= u[n-1][n-1];

    // get zeroes along top-right
    for(int i = n - 1; i >= 0; i--){ // move along diagonal
      for(int k = i - 1; k >= 0; k--){ // move up rows
        double q = -u[k][i]/u[i][i];
        for(int j = n - 1; j >= i; j--){ // move along the row from right
          u[k][j] += q*u[i][j];
        }
        v[k] += q*v[i];
      }
    }// end of loop, // zeroes everywhere except diagonal

    for(int i = 0; i < n; i++){ // get 1's along diagonal
      v[i] /= u[i][i];
      u[i][i] /= u[i][i];
    }

    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        if(isnan(u[i][j])) return -1;
      }
    }

    return 1;

}

double lpow(double sol, int n){
    double base = sol;
    for(int i = 1; i < n; i++){
        sol *= base;
    }
    return sol;
}

void gen_pow_sum_vector(double v[max_n], int n)
{
    v[0] = 1.0;
    for (int i = 1; i <= n; i++)
    {
        v[i] = v[i - 1] + lpow(i + 1, n);
    }
}

void gen_pow_sum_matrix(double M[max_n][max_n], int n)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            M[i][j] = lpow(i + 1, j + 1);
        }
    }
}

void print_mat(double M[max_n][max_n], double v[max_n], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%12lf", M[i][j]);
        }
        printf(" | %12lf", v[i]);
        printf("\n");
    }
}

double add_v(double v[max_n], int n){
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += v[i];
    }
    return sum;
}

int main()
{
    int n = 2;
    double v[max_n], M[max_n][max_n];

    gen_pow_sum_vector(v, n);
    gen_pow_sum_matrix(M, n);
    n += 1;
    print_mat(M, v, n);
    printf("--------------------------\n");
    solve(M, v, n);
    print_mat(M, v, n);
    printf("--------------------------\n");


}