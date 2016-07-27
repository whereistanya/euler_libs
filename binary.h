#include <iostream>

using namespace std;

string IntegerToBinaryString(int decimal) {
  int pow2 = 1;
  int digits = 1;
  string binary;
  while (true) {
    if (pow2 <= decimal) {
      pow2 *= 2;
      digits++;
      continue;
    }
    // go one too far and back up to drop leading zeroes
    pow2 /= 2;
    while (pow2 >= 1) {
      if (pow2 <= decimal) {
        binary += "1";
        decimal = decimal - pow2;
      } else {
        binary += "0";
      }
      pow2 /= 2;
    }
    return binary;
  }
}
