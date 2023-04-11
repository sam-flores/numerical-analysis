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

void print_system(double u[100][100], double v[100], int n){
  for(int i = 0; i < n; i++){
  	printf("row %2.1d :", i);
    for(int j = 0; j < n; j++){
      printf("%2.0lf", u[i][j]);
    }
    printf(" | %12.8lf", v[i]);
    printf("\n");
  }
}

void create_system(double u[100][100], double v[100], int n){
	// init all zeroes
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			u[i][j] = 0;
		}
		v[i] = 0;
	}

	// zeroth deriv equations
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			u[i][(i*4 + j) % 16] = 1;
		}
		if((i+1) % 4 != 0) u[i + 1][(i*4) % 16] = -1;
	}

	u[4][n - 1 - 3] = 1;

	for(int i = 5; i < 9; i++){
		u[i][1 + (i-5)*4] = 1;
		u[i][2 + (i-5)*4] = 2;
		u[i][3 + (i-5)*4] = 3;
		u[i + 1][((i-5)*4) % 16  + 1] = -1;
	}
	u[9][n - 1 - 2] = 1;


	for(int i = 10; i < 14; i++){
		u[i][(((i-10)*4) + 2) % 16] = 2;
		u[i][(((i-10)*4) + 3) % 16] = 6;
		u[i + 1][((i-10)*4) % 16  + 2] = -2;
	}
	u[14][n - 1 - 1] = 2;


	// load in last row's 1
	for(int i = 0; i < 4; i++){
		u[n-1][i*4] = 1;
	}
	v[n - 1] = 1;
}



int main(){

	int n = 16;
	double u[max_n][max_n], v[max_n];
	create_system(u, v, n);
	print_system(u, v, n);
	printf("----------------solve-----------------\n");
	printf("\n%d\n", solve(u, v, n));
	print_system(u, v, n);
	// stored into v is the coeffs for a system of
	// a(t), b(t), c(t), d(t);
}