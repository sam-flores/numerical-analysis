#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define newtons_method_iterations 15

void print_polynomial(double coefficients[], int degree){
    for (int i = degree; i >= 0; i--){
        printf("%lf*", coefficients[i]); printf("x^"); printf("(%d)", i);
        if(i != 0 && coefficients[i - 1] > 0) printf("+");
    }
}

int get_polynomial_derivative(double coefficients[], double prime_coefficients[], int degree){
    for (int i = degree; i >= 1; i--){
        prime_coefficients[i - 1] = (i)*coefficients[i];
    }
    return degree - 1;
}

int get_polynomial_coefficients(double coefficients[]){
  int degree;
  scanf("%d", &degree);
  for (int i = degree; i >= 0; i--){
    scanf("%lf", &coefficients[i]);
  }
  return degree;
}

double evaluate_polynomial(double coefficients[], int degree, double x){
  double answer = 0;
  double p = 1;
  for(int i = 0; i <= degree; i++){
    answer += coefficients[i]*p;
    p *= x;
  }
  return answer;
}

double synth_evaluate_polynomial(double res[2], double coefficients[], int degree, double root){
    // synthetic division
    for(int i = degree - 1; i >= 0; i--){
        coefficients[i] += coefficients[i + 1]*(root);
    }
    res[0] = coefficients[0];
    for(int i = degree - 1; i >= 0; i--){
        coefficients[i] += coefficients[i + 1]*(root);
    }
    res[1] = coefficients[1];
    // append zero after shift
}

void reduce_polynomial_by_root(double coefficients[], int degree, double root){

    // synthetic division
    for(int i = degree - 1; i >= 0; i--){
        coefficients[i] += coefficients[i + 1]*(root);
    }
    // shift into correct place
    for(int i = 0; i < degree; i++){
        coefficients[i] = coefficients[i+1];
    }
    // append zero after shift
    coefficients[degree] = 0;

}


int main(){

    double coefficients[100], prime_coefficients[100];
    int degree, prime_degree;
    degree = get_polynomial_coefficients(coefficients);
    prime_degree = get_polynomial_derivative(coefficients, prime_coefficients, degree);
    printf("\n f(x)  = "); print_polynomial(coefficients, degree); printf("\n");
    printf("\n f'(x) = "); print_polynomial(prime_coefficients, prime_degree); printf("\n");
    printf("\n");
    double x = -2;
    printf("\n f(%lf)  = ", x); printf("%lf", evaluate_polynomial(coefficients, degree, x)); printf("\n");
    double res[2];
    synth_evaluate_polynomial(res, coefficients, degree, x);

    printf("\n f(%lf)  = ", x); printf("%lf", res[0]); printf("\n");
    printf("\n f'(%lf)  = ", x); printf("%lf", res[1]); printf("\n");
    printf("\n");

}
