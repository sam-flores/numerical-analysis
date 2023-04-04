#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 500

void swap_row(int row, int index, double u[2][2], double v[2], int n){
  double temp[2][2];
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
void find_rows_to_swap_forward(double u[2][2], double v[2], int n, int index){
      for(int i = index; i < n; i++){ // move along diagonal
        if(u[i][i] != 0){
          swap_row(i, index, u, v, n);
          return;
        } 
      }
}

int find_max_row_on_diagonal(double u[2][2], double v[2], int n, int i){
      
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


int solve(double u[2][2], double v[2], int n){

    
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

double sum(double s[N], int n){
	double sum = 0;
	for(int i = 0; i < n; i++){
		sum += s[i];
	}
	return sum;
}

double create_mixed_sum(double x[N], double y[N], int n){
	double sum = 0;
	for(int i = 0; i < n; i++){
		sum += x[i]*y[i];
	}
	return sum;
}

double create_square_sum(double s[N], int n){
	double sum = 0;
	for(int i = 0; i < n; i++){
		sum += s[i]*s[i];
	}
	return sum;
}

void load_points_into_array(double x[N], double y[N], int n){
	
	for(int i = 0; i < n; i++){
		scanf("%lf", &x[i]);
		scanf("%lf", &y[i]);
	}
}

void print_out_point_array(double x[N], double y[N], int n){
	for(int i = 0; i < n; i++){
		printf("(%lf, %lf)\n", x[i], y[i]);
	}
}

void print_system(double u[2][2], double v[2], int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%12.8lf", u[i][j]);
    }
    printf(" | %12.8lf", v[i]);
    printf("\n");
  }
}


void create_system(double x[N], double y[N],
					double u[2][2], double v[2], int n){
	double x_sum = sum(x, n);
	double y_sum = sum(y, n);
	double mixed_sum = create_mixed_sum(x, y, n);
	double square_sum_x = create_square_sum(x, n);
	u[0][0] = 3; u[0][1] = x_sum; v[0] = y_sum; 
	u[1][0] = x_sum; u[1][1] = square_sum_x; v[1] = mixed_sum;

}

int main(){


	double u[2][2], v[2];
	double x[N], y[N];
	int n;
	scanf("%d", &n);
	load_points_into_array(x, y, n);	
	print_out_point_array(x, y, n);
	create_system(x, y, u, v, n);
	print_system(u, v, 2);
	solve(u, v, 2);
	print_system(u, v, 2);


}