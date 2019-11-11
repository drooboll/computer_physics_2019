#include <iostream>
#include <limits>
#include <fstream>
#include <cmath>
#include <float.h>

typedef std::numeric_limits<double> dbl;

double funcA(double x){
    return 1 / (1 + x * x);
}

double funcB(double x){
    return pow(x, 1. / 3) * pow(M_E, sin(x));
}

double calcLeft(double a, double b, int count, double(*funcPtr)(double)){
    if (a > b){
        double c = a;
        a = b;
        b = c;
    }
    double intervalLen = (b - a) / count;
    double result = 0;
    for (int i = 0; i < count; i++){
        result += (*funcPtr)(a) * intervalLen;
        a += intervalLen;
    }
    return result;
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

double funcA4(double x){
    if (x < DBL_EPSILON){
        return M_PI;
    }
    if (fabs(x - 1) < DBL_EPSILON){
        return 5. * M_PI;
    }
    return sin(M_PI * pow(x, 5)) / (pow(x, 5) * (1 - x));
}

double funcB4(double t){
    if (t == 1)
        return 0;
    return pow(M_E, -sqrt(t / (1 - t)) + sin(t / (10 * (1 - t)))) / pow(1 - t, 2);
}

double tanhF(double a, double b, double x){
    return 0.5 * (a + b) + 0.5 * (b - a) * tanh(x);
}

double funAppend(double a, double b, double x){
    return (b - a) / 2. * pow(cosh(x), -2);
}

double calcStrange(double a, double b, int count, double(*funcPtr)(double)){
    if (a > b){
        double c = a;
        a = b;
        b = c;
    }
    double intervalLen = M_PI / sqrt(2 * count);
    double result = 0;
    double aRem = a;
    double bRem = b;
    a = -intervalLen * count / 2;
    double last = (*funcPtr)(tanhF(aRem, bRem, a)) * funAppend(aRem, bRem, a);
    b = a + intervalLen;
    for (int i = 0; i < count; i++){
        double temp = (*funcPtr)(tanhF(aRem, bRem, b)) * funAppend(aRem, bRem, b);
        double mid = (*funcPtr)(tanhF(aRem, bRem, (a + b) / 2)) * funAppend(aRem, bRem, (a + b) / 2);
        result += intervalLen / 6 * (last + 4 * mid + temp);
        last = temp;
        a += intervalLen;
        b += intervalLen;
    }
    return result;
}


int main(int argc, char** argv){
    /*std::ofstream fileOutA("trA.txt", std::ofstream::out);
    std::ofstream fileOutAS("sA.txt", std::ofstream::out);
    std::ofstream fileOutAleft("leftA.txt", std::ofstream::out);
    fileOutA.precision(15);
    fileOutAS.precision(15);
    fileOutAleft.precision(15);
    for (int i = 2; i < 20; i++){
        double res = calcTr(-1, 1, 1 << i, &funcA);
        double res2 = calcS(-1, 1, 1 << i, &funcA);
        double res3 = calcLeft(-1, 1, 1 << i, &funcA);
        std::cout.precision(15);
        std::cout << "Trapezoid " << res << "\n";
        std::cout << "Simpson " << res2 << "\n";
        std::cout << "Left " << res3 << "\n";
        fileOutA << res << "\n";
        fileOutAS << res2 << "\n";
        fileOutAleft << res3 << "\n";
    }
    fileOutA.close();
    fileOutAS.close();
    fileOutAleft.close();

    std::ofstream fileOutB("trB.txt", std::ofstream::out);
    std::ofstream fileOutBS("sB.txt", std::ofstream::out);
    fileOutB.precision(15);
    fileOutBS.precision(15);
    for (int i = 2; i < 15; i++){
        double res = calcTr(0, 1, 1 << i, &funcB);
        double res2 = calcS(0, 1, 1 << i, &funcB);
        std::cout.precision(15);
        std::cout << "Trapezoid " << res << "\n";
        std::cout << "Simpson " << res2 << "\n";
        fileOutB << res << "\n";
        fileOutBS << res2 << "\n";
    }
    fileOutB.close();
    fileOutBS.close();*/
    std::ofstream fileOutA("sA4.txt", std::ofstream::out);
    std::ofstream fileOutB("sB4.txt", std::ofstream::out);
    std::ofstream fileOutBmod("sModB4.txt", std::ofstream::out);
    fileOutA.precision(15);
    fileOutB.precision(15);
    fileOutBmod.precision(15);
    for (int i = 5; i < 18; i++){
        double res = calcS(0, 1, 1 << i, &funcA4);
        double res1 = calcS(0, 1, 1 << i, &funcB4);
        double res2 = calcStrange(0, 1, 1 << i, &funcB4);
        std::cout.precision(15);
        std::cout << "Simpson A " << res << "\n";
        std::cout << "Simpson B " << res1 << "\n";
        std::cout << "Simpson B mod " << res2 << "\n";
        fileOutA << res << "\n";
        fileOutB << res1 << "\n";
        fileOutBmod << res2 << "\n";
    }
    fileOutA.close();
    fileOutB.close();
    fileOutBmod.close();
}