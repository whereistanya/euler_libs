//#include <set>

using namespace std;

bool IsPandigital(string& s) {
  // doesn't check for size; if this isn't a 9-character string, will be wrong
  int digits[] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < 9; i++) { // traverse s
    int d = s[i] - '0';
    if (digits[d] != 0) {
      return false;
    }
    digits[d] = 1;
  }
  return true;
}
