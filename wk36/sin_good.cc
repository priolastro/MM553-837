//
// Created by salvatore prioli on 29/12/2019.
// MM553/837 - Computational Physics Tutorial Exercise - Week 36
// Implementation of the series evaluation of the sin function
//

#include <cmath>
#include <iostream>
#include <sstream>
#include <math.h>
#include <chrono>
#define _USE_MATH_DEFINES
using namespace std;
using namespace std::chrono;

double factorial(double n){
    if (n==0){
        return 1;
    }
    return (n*factorial(n-1));
}

double good_way(const double& x, double term, double sum, double n, const double& error){
    do{
        term=(-(pow(x,2)))/((2*n-1)*(2*n-2))*term;
        sum=sum+term;
        n=n+1;
    }
    while (abs(term/sum)>error);
    return sum;
}

double bad_way(const double& x, double term, double sum, double n, const double& error){
    do{
        double denominator=factorial(2*n-1);
        double numerator=pow(-1,(n-1))*(pow(x,2*n-1));
        term=numerator/denominator;
        sum=sum+term;
        n=n+1;
    }
    while (abs(term/sum)>error);
    return sum;
}

double relation_way(double x, double term, double sum, double n, const double& error) {
    double new_x;
    double new_term;
    double new_sum;
    if (x <= 2 * M_PI) {
        do {
            term = (-(pow(x, 2))) / ((2 * n - 1) * (2 * n - 2)) * term;
            sum = sum + term;
            n = n + 1;
        } while (abs(term / sum) > error);
        return sum;
    }
    else if (x >= 2 * M_PI) {
        double cnt=1;
        do {
            new_x = x - cnt* 2 * M_PI;
            cnt+=1;
        }while (new_x>=2*M_PI);
        new_term = new_x;
        new_sum = new_x;
        do {
            new_term = (-(pow(new_x, 2))) / ((2 * n - 1) * (2 * n - 2)) * new_term;
            new_sum = new_sum + new_term;
            n = n + 1;
        } while (abs(new_term / new_sum) > error);
        return new_sum;
    }
    return 1;
}

int main(int argc, char** argv) {
    double x;
    stringstream(argv[1]) >> x;
    double error=10e-8;
    double term=x;
    double sum=x;
    double n=2;

    auto start_bad=high_resolution_clock::now();
    double sum_bad=bad_way(x, term, sum, n , error);
    auto stop_bad=high_resolution_clock::now();

    auto start_good=high_resolution_clock::now();
    double sum_good=good_way(x, term, sum, n, error);
    auto stop_good=high_resolution_clock::now();

    auto start_rel=high_resolution_clock::now();
    double sum_rel=relation_way(x, term, sum, n, error);
    auto stop_rel=high_resolution_clock::now();

    printf("%-65s %-.5e\n","calculated with implemented bad function:",sum_bad);
    printf("%-65s %-.5e\n", "calculate with implemented good function: ",sum_good);
    printf("%-65s %-.5e\n","calculate with implemented good function using 2npi relation:",sum_rel);
    printf("%-65s %-.5e\n", "calculated with built-in function:", sin(x));

    auto duration_bad = duration_cast<nanoseconds>(stop_bad - start_bad);
    auto duration_good = duration_cast<nanoseconds>(stop_good-start_good);
    auto duration_rel = duration_cast<nanoseconds>(stop_rel-start_rel);
    printf("The good algorithm took %lld ns , the bad took %lld ns and the algorithm with relation took %lld ns \n", duration_good.count(), duration_bad.count(), duration_rel.count());
}
