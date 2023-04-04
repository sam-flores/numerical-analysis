#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>

#define newtons_method_iterations 100

void print_polynomial(complex coefficients[], int degree){
    for (int i = degree; i >= 0; i--){
        printf("%lf*", (double)coefficients[i]); printf("x^"); printf("(%d)", i);
        if(i != 0 && (double)coefficients[i - 1] > 0) printf("+");
    }
}

int get_polynomial_derivative(complex coefficients[], complex prime_coefficients[], int degree){
    for (int i = degree; i >= 1; i--){
        prime_coefficients[i - 1] = (i)*coefficients[i];
    }
    return degree - 1;
}

int get_polynomial_coefficients(complex coefficients[]){
  int degree;
  scanf("%d", &degree);
  for (int i = degree; i >= 0; i--){
    scanf("%lf", &coefficients[i]);
  }
  return degree;
}

complex evaluate_polynomial(complex coefficients[], int degree, complex x){
  complex answer = 0;
  complex p = 1;
  for(int i = 0; i <= degree; i++){
    answer += coefficients[i]*p;
    p *= x;
  }
  return answer;
}

complex newtons_method(complex coefficients[], complex prime_coefficients[], int degree, complex c){
  for(int i = 1; i<=newtons_method_iterations; i++){
    c = c - evaluate_polynomial(coefficients, degree, c)/evaluate_polynomial(prime_coefficients, degree - 1, c);
  }
  return c;
}

void poly_poly_prime_eval_using_synthetic_division(complex res[2], complex coefficients[], int degree, complex root){

    complex temp[2*degree];
    for(int i = 0; i <= degree; i++)
        temp[i] = coefficients[i];

    for(int i = degree - 1; i >= 0; i--){
        temp[i] += temp[i + 1]*(root);
    }
    res[0] = temp[0];
    for(int i = degree - 1; i >= 0; i--){
        temp[i] += temp[i + 1]*(root);
    }
    res[1] = temp[1];
}

void reduce_polynomial_by_root(complex coefficients[], int degree, complex root){

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

void find_roots(complex coefficients[], complex prime_coefficients[], int degree){

    int i = 0;
    complex guess = drand48() + drand48()*I;
    complex root = newtons_method(coefficients, prime_coefficients, degree, guess);
    int num_roots = degree;
    while(i < num_roots){
        printf("%20.16lf + %20.16lfI\n", creal(root), cimag(root));
        reduce_polynomial_by_root(coefficients, degree, root);
        get_polynomial_derivative(coefficients, prime_coefficients, degree);
        degree--;
        guess = drand48() + drand48()*I;        
        root = newtons_method(coefficients, prime_coefficients, degree, guess);        
        i++;
    }    
}

int main(){

    complex coefficients[100], prime_coefficients[100];
    int degree, prime_degree;
    degree = get_polynomial_coefficients(coefficients);
    prime_degree = get_polynomial_derivative(coefficients, prime_coefficients, degree);
    printf("\n f(x)  = "); print_polynomial(coefficients, degree); printf("\n");
    printf("\n f'(x) = "); print_polynomial(prime_coefficients, prime_degree); printf("\n");
    printf("\n");
    find_roots(coefficients, prime_coefficients, degree);
    printf("\n");

}
