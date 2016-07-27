#include <iostream>
#include <math.h>

#include "convert.h"

// These are called IntToX, but accept longs too.

using namespace std;

void _IntToDigits(unsigned long n, int count, int* digits);

int CountDigits(int n) {
  if (n == 0) {
    return 1;
  }
  return floor(log10(n)) + 1;
}

// Generates a 10 element array containing a count of how often each of the
// digits from 0 to 9 appeared
void IntToDigitRange(unsigned long n, int count, int* range) {
  int digits[count];
  _IntToDigits(n, count, digits);
  for (int i = 0; i < count; i++) {
    int digit = digits[i];
    range[digit]++;
  }
}

// Generates an array containing the digits from the int in the order they
// appear.
void IntToDigits(unsigned long n, int count, int* digits) {
  _IntToDigits(n, count, digits);
}

int IntToDigitSum(unsigned long n, int count) {
  int sum = 0;
  for (int i = 0; i < count; ++i) {
    int digit = n % 10;
    sum += digit;
    n /= 10;
  }
  return sum;
}

void _IntToDigits(unsigned long n, int count, int* digits) {
  for (int i = 0; i < count; i++) {
    int digit = n % 10;
    digits[count - (i + 1)] = digit;
    n /= 10;
  }
}
