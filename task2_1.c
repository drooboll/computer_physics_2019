#include <stdio.h> 
#include <math.h> 
double m = 2; 
double a = 2; 
double u = 2; 
double h = 1.054; 
double f(double e){ 
	double xi = sqrt(m * a * a * (u - fabs(e)) / (2 * h * h)); 
	double xi_0 = sqrt(m * a * a * u / (2 * h * h)); 
	double s = sqrt(pow(xi_0 / xi, 2) - 1); 
	return tan(xi) - s; 
} 
void dih(double a, double b){ 
	int cnt = 0; 
// printf("%E %E\n", f(a), f(b));
	while (b - a > 1E-15){ 
		cnt++; 
		if(f(a) * f((a + b) / 2) <= 0){ 
			b = (a + b) / 2; 
		} else { 
			a = (a + b) / 2; 
		}
		printf("%.15lf\n", a);
	} 
	printf("Dih %.15E: %d, %lf\n", a, cnt, log2(0.7 / 1E-15)); 
}

void simple(double start){ 
	int cnt = 0; 
	double phi = -0.1 * f(start) + start; 

	cnt = 0; 
	while (fabs(phi - start) > 1E-15){ 
		start = phi; 
		phi = -0.1 * f(start) + start;  
		cnt++;
		printf("%.15lf\n", start);
	} 
	printf("Iter %.15E: %d, %lf\n", start, cnt, -log(1.9 / 1E-15) / log(0.24)); 
} 

void newton(double start){ 
	int cnt = 0; 
	while(fabs(f(start) * 1E-15 / (f(start) - f(start - 1E-15))) > 1E-15){ 
		start -= f(start) * 1E-15 / (f(start) - f(start - 1E-15)); 
		cnt++;
		printf("%.15lf\n", start);
	} 
	printf("Newton %.15E: %d\n", start, cnt); 
} 
int main() { 
	double a = -1.9; 
	double b = -1.1; 
	dih(a, b); 
	simple(a); 
	newton(a); 

return 0; 
}
