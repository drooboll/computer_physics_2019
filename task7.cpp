#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

double f(double t, double x){
    return -x;
}
double zeroValue = 1;
auto calcX(double a, double b, double (*fun)(double, double), double alpha){
    auto out = new std::vector<std::pair<double, double>>;
    int count = 1000;
    double step = (b - a) / count;
    double x = zeroValue;
    double t = 0;
    for (int i = 0; i <= count; i++){
        std::cout << x - exp(-t) << "\n";
        //a << fabs(x - exp(-t)) << "\n";
        out->push_back(std::make_pair(t, x));
        if (alpha != 0){
            x = x + step * ((1 - alpha) * fun(i * step, x) + alpha * fun(i * step + step / (2 * alpha), x + step / (2 * alpha) * fun(step * i, x)));
        } else {
            x = x + step * f(i * step, x);
        }
        t += step;
    }
    return out;
}

auto calcX4(double a, double b, double (*fun)(double, double)){
    auto out = new std::vector<std::pair<double, double>>;
    int count = 1000;
    double step = (b - a) / count;
    double x = zeroValue;
    double t = 0;
    for (int i = 0; i <= count; i++){
        std::cout << x - exp(-t) << "\n";
        //a << fabs(x - exp(-t)) << "\n";
        out->push_back(std::make_pair(t, x));
        double k1 = fun(t, x);
        double k2 = fun(t + step / 2, x + step / 2 * k1);
        double k3 = fun(t + step / 2, x + step / 2 * k2);
        double k4 = fun(t + step, x + step * k3);
        x = x + step / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        t += step;
    }
    return out;
}

int main() {
    std::ofstream euler("e.txt", std::ofstream::out);
    std::ofstream r("r.txt", std::ofstream::out);
    std::ofstream r4("r4.txt", std::ofstream::out);
    auto v = calcX(0, 3, &f, 0);
    for (int i = 0; i < v->size(); i++){
        euler << fabs(v->at(i).second - exp(-(v->at(i).first))) << "\n";
    }
    auto v2 = calcX(0, 3, &f, 0.75);
    for (int i = 0; i < v2->size(); i++){
        r << fabs(v2->at(i).second - exp(-(v2->at(i).first))) << "\n";
    }
    auto v3 = calcX4(0, 3, &f);
    for (int i = 0; i < v3->size(); i++){
        r4 << fabs(v3->at(i).second - exp(-(v3->at(i).first))) << "\n";
    }
    r4.close();
    euler.close();
    r.close();
    return 0;
}
