#include <iostream>
#include <complex>
#include <cmath>

using namespace std;
typedef complex<double> dcomp;

main() {
  dcomp i;
  dcomp a;
  double pi;
  dcomp b;
  pi = 2 * asin(1);
  i = -1;
  i = sqrt(i);
  a = exp(2*pi*i);
  for (int n=0; n<10; n++)
  	b += -i*(double)3;
 cout << b;
  cout << "i is " << i << "and Euler was right: e(i pi) = " << a << endl;
} 
