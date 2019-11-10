#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

int find_epsilon_f (float* f){
	int p = 0;
	float epsilon_f = 1.f;
	while (1.f + epsilon_f / 2.f > 1.f){
		epsilon_f /= 2.f;
		p++;
	}
	*f = epsilon_f;
	return p;
}

int find_epsilon_d (double* d){
	int p = 0;
	double epsilon_d = 1.;
	while (1. + epsilon_d / 2. > 1.){
		epsilon_d /= 2.;
		p++;
	}
	*d = epsilon_d;
	return p;
}

void find_min_max (){
	int p = 1;
	float max_f = 1.f;
	while (isnormal(max_f * 2.f)){
		max_f *= 2.f;
		p++;
	}
	printf("Float max: %d %E\n", p, max_f);

	float min_f = 1.f;
	p = 1;
	while (isnormal(min_f / 2.f)){
		min_f /= 2.f;
		p++;
	}
	printf("Float min: %d %E\n", p, min_f);

	double max_d = 1.;
	p = 1;
	while (isnormal(max_d * 2.)){
		max_d *= 2.;
		p++;
	}
	printf("Double max: %d %E\n", p, max_d);

	double min_d = 1.;
	p = 1;
	while (isnormal(min_d / 2.)){
		min_d /= 2.;
		p++;
	}
	printf("Double min: %d %E\n", p, min_d);
}

void check_eps(){
	float x0 = FLT_MIN;
	float x1 = x0 / 2;
	float x2 = x1 * 2;
	printf("x2-x1 = %e\n", x2-x0);
}

void compare_four (float epsilon){
	float num[] = {1.f, 1.f + epsilon / 2, 1.f + epsilon, 1.f + epsilon + epsilon / 2};
	char* desc[4] = {"1", "1 + e/2\0", "1 + e\0", "1 + e + e/2\0"};
	for (int i = 0; i < 4; i++){
		for (int j = i; j < 4; j++){
			if (i != j)
				printf("%8s == %8s\t is %s\n", desc[i], desc[j],  num[i] == num[j] ? "true" : "false");
		}
	}
}

void compare_two (float e){
	float low = 1.f + e / 2;
	float high = 1.f + e;
	
	printf("1 + e/2 + e == 1 + e + e/2 is %s\n", (1.f + e / 2 + e == 1.f + e + e / 2) ? "true" : "false");
	int* int_ptr = (int*) &low;
	printf("%X goes to ", *int_ptr);
	low += e;
	printf("%X\n", *int_ptr);
	int_ptr = (int*) &high;
	printf("%X goes to ", *int_ptr);
	high += e / 2;
	printf("%X\n", *int_ptr);
}

int main (void){
	printf("++++Task 1++++\n");
	float f;
	double d;
	int p_f = find_epsilon_f(&f);
	printf("Significand: %d, float ULP: %E\n", p_f, f);
	int p_d = find_epsilon_d(&d);
	printf("Significand: %d, double ULP: %E\n", p_d, d);
	find_min_max();
	printf("++++Task 2++++\n");
	compare_four(f);
	printf("++++Task 3++++\n");
	compare_two(f);
	check_eps();
	return 0;
}
