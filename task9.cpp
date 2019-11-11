#include <iostream>
#include <fstream>
#include <vector>

double calcFirstPart(double u, double v){
    return 998 * u + 1998 * v;
}

double calcSecondPart(double u, double v){
    return -999 * u - 1999 * v;
}

#define RK4 0
#define RK2 1

std::vector<std::pair<double, double>> out[10000];

auto calcX(double time, double step, std::vector<double>& vec, int type){
    out->clear();
    double x, y;
    x = vec[0];
    y = vec[1];
    double t = 0;

    for (int i = 0; i <= (int)(time / step); i++){
        if (!type){
            double k1 = step * calcFirstPart(x, y);
            double q1 = step * calcSecondPart(x, y);

            double k2 = step * calcFirstPart(x + k1 / 2, y + q1 / 2);
            double q2 = step * calcSecondPart(x + k1 / 2, y + q1 / 2);

            double k3 = step * calcFirstPart(x + k2 / 2, y + q2 / 2);
            double q3 = step * calcSecondPart(x + k2 / 2, y + q2 / 2);

            double k4 = step * calcFirstPart(x + k3, y + q3);
            double q4 = step * calcSecondPart(x + k3, y + q3);
            std::cout << i << " " << x << " " << y << std::endl;
            out->push_back(std::make_pair(x, y));
            x += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            y += (q1 + 2 * q2 + 2 * q3 + q4) / 6;
        } else {
            double k1 = step * calcFirstPart(x, y);
            double q1 = step * calcSecondPart(x, y);

            double k2 = step * calcFirstPart(x + k1 / (2 * 0.75), y + q1 / (2 * 0.75));
            double q2 = step * calcSecondPart(x + k1 / (2 * 0.75), y + q1 / (2 * 0.75));
            std::cout << i << " " << x << " " << y << std::endl;
            out->push_back(std::make_pair(x, y));
            x += (0.25 * k1 + 0.75 * k2);
            y += (0.25 * q1 + 0.75 * q2);
        }


        t += step;
    }
    return out;
}

void invert2x2(double* m){
    double det = m[0] * m[3] - m[1] * m[2];
    m[1] = -m[1];
    m[2] = -m[2];
    double c = m[0];
    m[0] = m[3];
    m[3] = c;
    for(int i = 0; i < 4; i++){
        m[i] /= det;
    }
}

void mulMatrixRow(double* m, double* r){
    double c = r[0];
    r[0] = m[0] * r[0] + m[1] * r[1];
    r[1] = m[2] * c + m[3] * r[1];
}

std::vector<std::pair<double, double>>* calcInverse(double time, double step, double* m, std::vector<double>& vec){
    out->clear();
    double x, y;
    x = vec[0];
    y = vec[1];

    auto r = new double(2);
    r[0] = x;
    r[1] = y;
    m[0] = 1 - step * m[0];
    m[1] = - step * m[1];
    m[2] = - step * m[2];
    m[3] = 1 - step * m[3];

    invert2x2(m);
    for (int i = 0; i <= (int)(time / step); ++i){
        std::cout << x << " " << x << std::endl;
        out->emplace_back(std::make_pair(x, y));
        mulMatrixRow(m, r);
        x = r[0];
        y = r[1];
    }
    //delete(r);
    return out;
}

int main() {
    double timeMax = 10;
    double step = 0.005;
    auto vec = new std::vector<double>;
    std::ofstream a("outRK4.txt", std::ofstream::out);
    std::ofstream b("outE.txt", std::ofstream::out);
    vec->push_back(1.5);
    vec->push_back(-1.);
    //auto out = calcX(timeMax, step, *vec, RK4);
    for (int i = 0; i < (int)(timeMax / step); i++){
        //a << out->at(i).first << " " << out->at(i).second << std::endl;
    }
    auto m = new double[4];
    m[0] = 998;
    m[1] = 1998;
    m[2] = -999;
    m[3] = -1999;
    //auto out1 = calcInverse(timeMax, step, m, *vec);
    for (int i = 0; i < (int)(timeMax / step); i++){
        //b << out1->at(i).first << " " << out1->at(i).second << std::endl;
    }
    a.close();
    //delete(m);
    b.close();
    //delete(out);
}