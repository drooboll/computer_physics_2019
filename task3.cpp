#include <iostream>
#include <limits>

typedef std::numeric_limits<double> dbl;

double funcA(double x){
	return 1 / (1 + x * x);
}

double calcTr(double a, double b, int count, double(*funcPtr)(double)){
	if (a > b){
		double c = a;
		a = b;
		b = c;
	}
	double intervalLen = (b - a) / count;
	double last = (*funcPtr)(a);
	double result = 0;
	for (int i = 1; i <= count; i++){
		double temp = (*funcPtr)(a + i * intervalLen);
		result += (last + temp) * intervalLen / 2;
		last = temp;
	}
	return result;
}


int main(int argc, char** argv){
	std::ofstream
	for (int i = 0; i < 12; i++){
		std::cout.precision(15);
		std::cout <<  calcTr(-1, 1, 1 << i, &funcA) << "\n";
	}
}
