#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define num_exponent 11
#define num_mantissa 53

void reverse_array(int arr[], int start, int end){
    int temp;
    while (start < end){
        temp = arr[start];  
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }  
}    

void print_array(int arr[], int size){
  int i;
  for (i=0; i < size; i++)
    printf("%d", arr[i]);
 }

void reset_arr(int arr[], int size){
	int i = 0;
	while(i < size){
		arr[i] = 0;
		i++;	
	} 
}

int get_exponent(int x, int b[]){
	reset_arr(b, 100);
	int i = 0;
	while(i < num_exponent - 1){
		b[i] = (int)fmod(x, 2);
		x /= 2;
		i++;
	}
	reverse_array(b, 0, i - 1);
	return i;
}

int left_side_to_binary(int x, int b[]){
	reset_arr(b, 100);
	int i = 0;
	while(x >= 1){
		b[i] = (int)fmod(x, 2);
		x /= 2;
		i++;
	}
	reverse_array(b, 0, i - 1);
	return i;
}

int right_side_to_binary(double x, int b[], int leftover){
	reset_arr(b, 100);
	int i = 0;
	while(i < num_mantissa - leftover - 1){
		x *= 2;
		b[i] = (int)floor(x);
		if(x >= 1) x -= 1;
		i++;
	}
	return i;
}

void chop_one_off(int b[], int length){
	int i = 0;
	while(i < length - 1){
		b[i] = b[i+1];
		i++;
	}
	b[i] = 0;


}	

int main(){

	double x = 73.5;
	// scanf("%lf", &x);
	double left_of_decimal = (int)fabs(x);
	double right_of_decimal = fabs(x) - (int)fabs(x);
	
	// is x positive
	if(fabs(x) <= 0) printf("1");
	else printf("0");
	printf(" ");

	// is less than 1
	if(fabs(x) >= 1) printf("1");
	else printf("0");

	int b[100];
	int length = left_side_to_binary(left_of_decimal, b);
	// print exponent
	length += pow(2, num_exponent) - 1;
	get_exponent(length - 1, b);
	print_array(b, num_exponent - 1);
	printf(" ");

	// print mantissa
	length = left_side_to_binary(left_of_decimal, b);
	chop_one_off(b, length);
	print_array(b, length-1);
	length = right_side_to_binary(right_of_decimal, b, length - 1);
	print_array(b, length);
	printf(" ");

	printf("\n");

	printf("0 10000000101 0010011000000000000000000000000000000000000000000000");
}