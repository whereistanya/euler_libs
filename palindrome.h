using namespace std;

bool IsPalindrome(string s) {
  if (s.length() == 1) {
    return true;
  }
  int p1 = 0;
  int p2 = s.length() - 1;
  while ((s[p1] == s[p2]) && (p2 > p1)) {
    p1++;
    p2--;
    if (p2 <= p1) {
      return true;
    }
  }
  return false;
}

