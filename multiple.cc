#include <iostream>
#include <cmath>
#include <math.h>

#include "multiple.h"

using namespace std;

bool IsMultiple(int dividend, int divisor) {
  double quotient = dividend/divisor;
  if (floor(quotient) == quotient) {
    return true;
  } else {
    return false;
  }
}

bool IsMultiple(double dividend, int divisor) {
  double quotient = dividend/divisor;
  if (floor(quotient) == quotient) {
    return true;
  } else {
    return false;
  }
}

bool IsMultiple(double dividend, double divisor) {
  //cout << "Checking whether " << dividend << " is a multiple of " << divisor << "..";
  double quotient = dividend/divisor;
  if (floor(quotient) == quotient) {
    cout << dividend << " is a multiple of " << divisor << endl;
    return true;
  } else {
    //cout << "No" << endl;
    return false;
  }
}

bool IsPrime(int number) {
  int test = number/2;
  while (test > 1) {
    if (IsMultiple(number, test))
      return false;
    test--;
  }
  return true;
}

bool IsPrime(double number) {
  int i = 2;
  while (i < number/2) {
    double test = floor(number/i);
    //cout << "Prime check: ";
    if (IsMultiple(number, test)) {
      return false;
    }
    i++;
  }
  cout << number << " is prime" << endl;
  return true;
}

