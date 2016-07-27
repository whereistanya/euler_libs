#include <gmpxx.h>
#include <iostream>
#include <vector>
#include "convert.h"

#include "squareroot.h"

using namespace std;

vector<int> RootFinder::GetNDigitsOfSquareRoot(int n, int square) {
  vector<int> root;
  int count = CountDigits(square);
  if (count <= 0) {
    return root; // empty vector
  }
  int digits[count];
  for (int i = 0; i < count; i++) {
    digits[i] = 0;
  }
  IntToDigits(square, count, digits);

  int digitindex = 0;

  mpz_class p = 0;
  mpz_class tmp, y, c;
  int x;
  // first one or two digits: one if odd number of digits, two if even
  if (count % 2 == 0) {
    c = digits[digitindex] * 10 + digits[digitindex + 1];
    digitindex += 2;
  } else {
    c = digits[digitindex];
    digitindex++;
  }

  while (n > 0) {
    if ((c == 0) && (digitindex > count)) {
      cout << digitindex << "; " << count << endl;
      // rational number; skip out early
      return root;
    }
    n--;
    // make a guess at x, while avoiding dividing by zero
    if (p > 0) {
      tmp = c / (20 * p);
      x = tmp.get_si();
    } else {
      tmp = c / 20;
      x = tmp.get_si();
    }

    y = x * (20 * p + x);
    if (y > c) {
      while (y > c) {
        x--;
        y = x * (20 * p + x);
      }
    } else if (y < c) {
      int better_x = x + 1;
      while (better_x * (20 * p + better_x) <= c) {
        x = better_x;
        y = x * (20 * p + x);
        better_x++;
      }
    }
    y = x * (20 * p + x);

    root.push_back(x);
    p *= 10;
    p += x;

    c = (c - y) * 100;

    if (digitindex < count) {
      c += digits[digitindex] * 10;
    }
    digitindex++;
    if (digitindex < count) {
      c += digits[digitindex];
    }
    digitindex++;
  }
  return root;
}

//int main() {
//  RootFinder rf;
//  vector<int> root = rf.GetNDigitsOfSquareRoot(5, 2);
//  for (int i = 0; i < root.size(); i++) {
//    cout << root[i] << " ";
//  }
//  cout << endl;
//  return 0;
//}
