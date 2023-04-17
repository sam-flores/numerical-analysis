#define max_n 100

void load_nx3_diagonal(double u[max_n], double x[max_n], int n){
  u[0] = 1;
  for(int i = 1; i < n; i++){
    u[2*i] = -(x[i + 1] - x[i - 1]);
    u[2*i - 1] = (x[i] - x[i - 1])*(x[i] - x[i - 1]);
  }
    u[n - 1] = 2*(x[(n + 2) / 2 - 1] - x[(n + 2)/2 - 2]);
}

void create_nx3_system(double lower[max_n],
                        double middle[max_n],
                        double upper[max_n], 
                        double v[max_n], 
                        double x[max_n], double y[max_n], int n){
    load_nx3_diagonal(middle, x, n);
}

void load_upper_diagonal(double u[max_n], double x[8], int n){
  u[0][1] = -(x[1] - x[0]);
  for(int i = 1; i < n; i++){
    u[2*i - 1] = (x[i + 1] - x[i]);
    u[2*i] = (x[i] - x[i - 1])*(x[i + 1] - x[i]);
  }
}


// void load_zeroes(double u[max_n][max_n], double v[max_n], int n){
//   for(int i = 0; i < n; i++){
//     for(int j = 0; j < n; j++){
//       u[i][j] = 0;
//     }
//     v[i] = 0;
//   }
// }

// void load_upper_diagonal(double u[max_n][max_n], double x[8], int n){
//   u[0][1] = -(x[1] - x[0]);
//   for(int i = 1; i < n; i++){
//     u[2*i - 1][2*i - 1 + 1] = (x[i + 1] - x[i]);
//     u[2*i][2*i + 1] = (x[i] - x[i - 1])*(x[i + 1] - x[i]);
//   }
// }

// void load_lower_diagonal(double u[max_n][max_n], double x[8], int n){
//   u[1][0] = (x[1] - x[0]);
//   for(int i = 1; i < n; i++){
//     u[2*i - 1 + 1 - 1][2*i - 1 - 1] = (x[i] - x[i - 1]);
//     u[2*i + 1 - 1][2*i - 1] = (x[i] - x[i - 1])*(x[i] - x[i - 1]);
//   }
//     u[n - 1][n - 1 - 1] = 1;
// }

// void load_v(double v[max_n], double x[8], double y[8], int n){
//   v[0] = 0;
//   for(int i = 1; i < n - 1; i++){
//     v[2*i - 1] = (y[i + 1] - y[i])/(x[i + 1] - x[i]) - (y[i] - y[i - 1])/(x[i] - x[i - 1]);
//     v[2*i] = -(y[i + 1] - y[i])/(x[i + 1] - x[i]) + (y[i] - y[i - 1])/(x[i] - x[i - 1]);
//   }
//   v[n - 1] = 0;
// }


void print_nx3_system(double lower[max_n],
                        double middle[max_n],
                        double upper[max_n],  
                        double v[max_n], int n){
    for(int i = 0; i < n; i++){
        printf("%lf\n",middle[i]);
    }
}