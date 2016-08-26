#include <iostream>
#include <vector>
#include "primefactor.h"

#include "coprime.h"

using namespace std;

long GCD(long smaller, long remainder) {
  if ((smaller <= 0) || (remainder <= 0)) {
    return 1;
  }

  while (true) {
    if (remainder == 0) {
      return smaller;
    }

    if (smaller > remainder) {
      // swap
      long tmp = smaller;
      smaller = remainder;
      remainder = tmp;
    }
    remainder = remainder % smaller;
  }
}

double CoprimeCount(long n) {
  // euler's totient
  double phi = n;
  vector<long> v;
  PrimeFactorer pf;
  pf.GetPrimeFactors(n, v);
  for (vector<long>::const_iterator it = v.begin(); it != v.end(); ++it) {
    double factor = 1.0 / *it;
    phi *= ( 1 - factor);
  }
  return phi;

}

/*
int main(){
  cout << "21 and 35: " << GCD(21, 35) << endl;
  cout << "35 and 21: " << GCD(35, 21) << endl;
  cout << "0 and 6: " << GCD(0, 6) << endl;
  cout << "1989 and 867: " << GCD(1989, 867) << endl;
  cout << "7 and 6: " << GCD(7, 6) << endl;
  cout << "Coprime count for 8: " << CoprimeCount(8) << endl;
  cout << "Coprime count for 9: " << CoprimeCount(9) << endl;
  cout << "Coprime count for 10:" << CoprimeCount(10) << endl;
  return 0;
}
*/
