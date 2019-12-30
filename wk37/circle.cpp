//
// Created by salvatore prioli on 29/12/2019.
// MM553/837 - Computational Physics Tutorial Exercise - Week 36
// Particle mooving on a circle

#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <string>
#define _USE_MATH_DEFINES
using namespace std;
using namespace std::chrono;
string buf , buf1 , buf2 ;

double x_zero;
double y_zero;
double R;
double theta;
double t, t0, tf, dt;
double x, y;
double vx, vy;
double omega;

int main(int argc, char** argv) {
    cout << "# Enter the angle omega:\n";
    cin >> omega;
    getline(cin, buf);
    cout << "# Enter center of circle (x0,y0) and radius R:\n";
    cin >> x_zero >> y_zero >> R; getline(cin, buf);
    cout << "# Enter t0, tf, dt:\n";
    cin >> t0 >> tf >> dt;
    getline(cin, buf);
    cout << " # omega = " << omega << endl;
    cout << " # x0 = " << x_zero << " y0 = " << y_zero << " R = " << R << endl;
    cout << " # t0 = " << t0 << " tf = " << tf << " dt = " << dt << endl;

    if (R <= 0.0){
        cerr << "illegal value of R\n";
        exit(1);
    }
    if (omega <=0.0){
        cerr << "illegal value of omega\n";
    }
    cout << "# period value T= " << 2.0*M_PI/omega << endl;
    ofstream myfile("circle.dat");
    myfile.precision(17);

    t=t0;
    while (t <= tf ){
        theta = omega * (t-t0);
        x = x_zero + R * cos(theta);
        y = y_zero + R * sin(theta);
        vx = -omega * R * sin(theta);
        vy = omega * R * cos(theta);
        myfile << t << " " << x << " " << y << " " << vx << " " << vy << endl;
        t = t + dt;
    }
    return 1;
}