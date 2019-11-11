#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

auto calcStationary(std::vector<double>& vec){
    auto out = new std::vector<double>;
    out->push_back(vec[3] / vec[2]);
    out->push_back(vec[0] / vec[2]);
    return out;
}

double calcFirstPart(double a, double b, double x, double y){
    return a * x - b * x * y;
}

double calcSecondPart(double c, double d, double x, double y){
    return c * x * y - d * y;
}

auto calcX(double time, double step, std::vector<double>& vec, int type){
    auto out = new std::vector<std::pair<double, double>>;
    double x, y;
    std::vector<double>* point = calcStationary(vec);
    //x = point->at(0);
    //y = point->at(1);
    x = 1.;
    y = 1.;
    double t = 0;

    for (int i = 0; i <= (int)(time / step); i++){
        if (!type){
            double k1 = step * calcFirstPart(vec[0], vec[1], x, y);
            double q1 = step * calcSecondPart(vec[2], vec[3], x, y);

            double k2 = step * calcFirstPart(vec[0], vec[1], x + k1 / 2, y + q1 / 2);
            double q2 = step * calcSecondPart(vec[2], vec[3], x + k1 / 2, y + q1 / 2);

            double k3 = step * calcFirstPart(vec[0], vec[1], x + k2 / 2, y + q2 / 2);
            double q3 = step * calcSecondPart(vec[2], vec[3], x + k2 / 2, y + q2 / 2);

            double k4 = step * calcFirstPart(vec[0], vec[1], x + k3, y + q3);
            double q4 = step * calcSecondPart(vec[2], vec[3], x + k3, y + q3);

            out->push_back(std::make_pair(x, y));
            x += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            y += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
        } else {
            double k1 = step * calcFirstPart(vec[0], vec[1], x, y);
            double q1 = step * calcSecondPart(vec[2], vec[3], x, y);

            double k2 = step * calcFirstPart(vec[0], vec[1], x + k1 / (2 * 0.75), y + q1 / (2 * 0.75));
            double q2 = step * calcSecondPart(vec[2], vec[3], x + k1 / (2 * 0.75), y + q1 / (2 * 0.75));



            out->push_back(std::make_pair(x, y));
            x += (0.25 * k1 + 0.75 * k2);
            y += (0.25 * q1 + 0.75 * q2);
        }


        t += step;
    }
    return out;
}

int main() {
    std::ofstream a("out.txt", std::ofstream::out);
    std::ofstream b("outA.txt", std::ofstream::out);
    auto param = new std::vector<double>;
    param->push_back(-0.1);
    param->push_back(2);
    param->push_back(2);
    param->push_back(1);
    auto vecOut = calcX(10, 0.001, *param, 0);
    for (int i = 0; i < vecOut->size(); i++){
        std::cout << vecOut->at(i).first << " " << vecOut->at(i).second << "\n";
        a << vecOut->at(i).first << " " << vecOut->at(i).second << "\n";
    }
    auto vecOut2 = calcX(10, 0.001, *param, 1);
    for (int i = 0; i < vecOut2->size(); i++){
        std::cout << vecOut2->at(i).first << " " << vecOut2->at(i).second << "\n";
        b << vecOut2->at(i).first << " " << vecOut2->at(i).second << "\n";
    }

    a.close();
    b.close();
    return 0;
}