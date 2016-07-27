#ifndef EULER_CONVERT_H_
#define EULER_CONVERT_H_

#include <iostream>
#include <math.h>

// These are called IntToX, but accept longs too.

using namespace std;

int CountDigits(int n);

// Generates a 10 element array containing a count of how often each of the
// digits from 0 to 9 appeared
void IntToDigitRange(unsigned long n, int count, int* range);

// Generates an array containing the digits from the int in the order they
// appear.
void IntToDigits(unsigned long n, int count, int* digits);

int IntToDigitSum(unsigned long n, int count);

void _IntToDigits(unsigned long n, int count, int* digits);

#endif // EULER_CONVERT_H_
