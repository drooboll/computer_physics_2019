#include <stdio.h>
#include <math.h>
#include <float.h>

double a = 2E-10;
double m = 4E-27;
double u0 = 1E50;
double h = 1.054E-27;

double f(double x){
	x = -x / u0;
	double s = sqrt(2 * m * a * a * u0 / (h * h) * (1 - x));
	printf("%E %E\n", s, 1/x - 1);
	return 1 / tan(s) - sqrt(1 / x - 1);
}

double find_root_d(double a, double b){
	while (b - a > DBL_MIN){
		double mid = f((a + b) / 2);
		if (f(a) * mid <= 0){
			b = (a + b) / 2;
		} else {
			a = (a + b) / 2;
		}
		printf("%E %E %E\n", mid, a, b);
	}
	return a;
}

int main (void){
	printf("%E\n", find_root_d(-1, 0));
}
