#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>

std::vector<double> pointsX;
std::vector<double> a;

double fun(double x){
    return log(x);
}

double calcW(unsigned int k, unsigned int i){
    double w = 1;
    for (unsigned int j = 0; j <= i; j++){
        if(j != k)
            w *= (pointsX.at(k) - pointsX.at(j));
    }
    //std::cout << "W for " << k << " " << i << " is " << w << "\n";
    return w;
}

double calcCoefficient(unsigned int i){
    double a = 0;
    if (!i)
        return fun(pointsX.at(0));
    for (unsigned int k = 0; k <= i; k++){
        double sum = fun(pointsX.at(k)) / calcW(k, i);
        a += sum;
        //std::cout << "Value for " << k << " " << i << " is " << sum << "\n";
    }
    return a;
}

double calcMul(double x, unsigned int num){
    double mul = 1;
    for (unsigned int i = 0; i < num; i++){
        mul *= (x - pointsX.at(i));
    }
    return mul;
}

double funPoly(double x){
    double res = 0;
    for (int i = 0; i < a.size(); i++){
        res += a[i] * calcMul(x, i);
    }
    return fabs(res - log(x));
}


double calcS(double a, double b, int count, double(*funcPtr)(double)){
    if (a > b){
        double c = a;
        a = b;
        b = c;
    }
    double intervalLen = (b - a) / count;
    double result = 0;
    double last = (*funcPtr)(a);
    b = a + intervalLen;
    for (int i = 0; i < count; i++){
        double temp = (*funcPtr)(b);
        double mid = (*funcPtr)((a + b) / 2);
        result += intervalLen / 6 * (last + 4 * mid + temp);
        last = temp;
        a += intervalLen;
        b += intervalLen;
    }
    return result;
}

int main() {
    std::ofstream eOut("e.txt", std::ofstream::out);
    for (int j = 4; j <= 18; j++){
        pointsX.clear();
        for (int i = 0; i <= j; i++) {
            pointsX.push_back(1 + i / (double)j);
        }
        a.clear();
        for (unsigned int i = 0; i <= j; i++){
            a.push_back(calcCoefficient(i));
        }
        eOut << calcS(1, 2, 2000, &funPoly) << "\n";
    }

    eOut.close();

    return 0;
}
