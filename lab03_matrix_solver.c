#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#define max_n 100

void init_mat(double u[max_n][max_n], double v[max_n], int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf("%lf", &u[i][j]);
    }
    scanf("%lf", &v[i]);
  }
}

void print_mat(double u[max_n][max_n], double v[max_n], int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%12.8lf", u[i][j]);
    }
    printf(" | %12.8lf", v[i]);
    printf("\n");
  }
}

void copy(double u[max_n], double v[max_n], int n){
    for(int i = 0; i < n; i++){
      u[i] = v[i];
    }
}

void add_row(int row, int index, double u[max_n][max_n], double v[max_n], int n){
  for(int i = 0; i < n; i++){
    u[index][i] += u[row][i];
  }
      v[index] += v[row];
}


void add_all_rows(double u[max_n][max_n], double v[max_n], int n){

    // find non-zero row
    for(int j = 0; j < n; j++){
    for(int i = 0; i < n; i++){
        add_row(i, j, u, v, n);
    }
  }
}

void find_rows_to_swap_forward(double u[max_n][max_n], double v[max_n], int n, int index){
      for(int i = index; i < n; i++){ // move along diagonal
        if(u[i][i] != 0){
          swap_row(i, index, u, v, n);
          return;
        } 
      }
}

double evaluate_determinant3x3(double u[max_n][max_n], int n){

  double v[max_n][max_n*2];

  // create det matrix
  for(int i = 0; i < n; i++){
    printf("\n");
    for(int j = 0; j < 2*n; j++){
      v[i][j] = u[i][j%n];
      printf("%12.8lf ", u[i][j%n]);
    }
  }

  double sol = 0;
  double mult = 1;
  int j = 0;
  // left-right downward += mults
  for(int k = 0; k < n; k++){
    mult = 1;
    printf("\nsol += ");
    for(int i = 0; i < n; i++){
      mult *= v[i][k + i];
      printf("%lf * ", v[i][k + i]);
    }
    sol += mult;
  }

  // right-left downward -= mults
  for(int k = 0; k < n; k++){
    mult = 1;
    j = 0;
    printf("\nsol -= ");
    for(int i = 2*n - 1; i >= n ; i--){
      mult *= v[j][i - k];
      printf("%lf * ", v[j][i - k]);
      j++;
    }
    sol -= mult;
  }

  // printf("%20.16lf", sol);
  return sol;
}

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


int main(int argc, char const *argv[]) {

  int n = 0;
  double u[max_n][max_n];
  double v[max_n];
  scanf("%d", &n);
  printf("matrix-----------------------------------\n");
  init_mat(u, v, n);
  // print out values
  print_mat(u, v, n);

  // solve matrix
  if(solve(u, v, n) == 1){
      printf("solved------------------------------------\n");
      print_mat(u, v, n);
  }else{
      printf("------no unique solutions------------------------------------\n");
  }
}
