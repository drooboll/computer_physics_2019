#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>

std::vector<double> pointsX;
std::vector<double> pointsX1;
std::vector<double> pointsY;
std::vector<double> pointsY1;

double calcW(unsigned int k, unsigned int i){
    double w = 1;
    for (unsigned int j = 0; j <= i; j++){
        if(j != k)
            w *= (pointsX1.at(k) - pointsX1.at(j));
    }
    //std::cout << "W for " << k << " " << i << " is " << w << "\n";
    return w;
}

double intFun(int m, double t, double x){
    return 1 / M_PI * cos(m * t - x * sin(t));
}

double diffFun(int m, double t, double x){
    return 1 / M_PI * sin(t) * sin(m * t - x * sin(t));
}

int count = 2000;

double leibnitz(int m, double x){
    double a = 0;
    double b;
    double intervalLen = M_PI / count;
    double result = 0;
    double last = diffFun(m, a, x);
    b = a + intervalLen;
    for (int i = 0; i < count; i++){
        double temp = diffFun(m, b, x);
        double mid = diffFun(m, (a + b) / 2, x);
        result += intervalLen / 6 * (last + 4 * mid + temp);
        last = temp;
        a += intervalLen;
        b += intervalLen;
    }
    return result;
}

double fun(unsigned int m, double x){
    double a = 0;
    double b;
    double intervalLen = M_PI / count;
    double result = 0;
    double last = intFun(m, a, x);
    b = a + intervalLen;
    for (int i = 0; i < count; i++){
        double temp = intFun(m, b, x);
        double mid = intFun(m, (a + b) / 2, x);
        result += intervalLen / 6 * (last + 4 * mid + temp);
        last = temp;
        a += intervalLen;
        b += intervalLen;
    }
    return result;
}

double calcCoefficient(unsigned int i){
    double a = 0;
    if (!i)
        return pointsY.at(0);
    for (unsigned int k = 0; k <= i; k++){
        double sum = pointsY.at(k) / calcW(k, i);
        a += sum;
        //std::cout << "Value for " << k << " " << i << " is " << sum << "\n";
    }
    return a;
}

int main() {
    std::ofstream a("out.txt", std::ofstream::out);
    std::ofstream b("outL.txt", std::ofstream::out);
    for (int i = 0; i < 100; i++){
        pointsX.push_back(2 * i * M_PI / 100);
    }

    for (int i = 0; i < 1000; i++){
        pointsX1.push_back(2 * i * M_PI / 1000);
        pointsY.push_back(fun(0, 2 * i * M_PI / 1000));
    }
    double h = 2.5e-5;
    for (unsigned int i = 0; i < 100; i++){
        double derivative = (fun(0, pointsX.at(i) + h) - fun(0, pointsX.at(i) - h)) / (2 * h);
        std::cout << i << " " << (fun(1, pointsX.at(i)) + derivative) << "\n";
        a << (fun(1, pointsX.at(i)) + derivative) << "\n";
    }

    for (unsigned int i = 0; i < 100; i++){
        double derivative = leibnitz(0, pointsX[i]);
        std::cout << i << " " << (fun(1, pointsX.at(i)) + derivative) << "\n";
        b << (fun(1, pointsX.at(i)) + derivative) << "\n";
    }

    a.close();
    b.close();


    return 0;
}