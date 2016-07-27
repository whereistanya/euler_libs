#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

template <class Type>
struct Fraction {
  Type n;  //numerator
  Type d;  //denominator

  Fraction(Type x, Type y) {
    n = x;
    d = y;
  }
  Fraction() {
    n = 0;
    d = 1;
  }


  void Invert() {
    Type tmp = n;
    n = d;
    d = tmp;
  }
};

template <class Type>
static std::ostream & operator<<(ostream &o, const Fraction<Type>& f) {
  cout << f.n << "/" << f.d;
}

template <class Type>
class ContinuedFraction {
// depth is how many convergents in.
public:
  ContinuedFraction() {
    next_convergent = 0;
  }

  ~ContinuedFraction() {}

  void SetQuotients(int to_push) {
    quotients.push_back(to_push);
  }

  void PrintQuotients() {
    for (int i = 0; i < quotients.size(); i++) {
      cout << quotients[i] << ",";
    }
    cout << endl << endl;
  }

  Fraction<Type> ConvergeFromQuotients(int max, int depth) {
    if (max == 0) {
      Fraction<Type> f(quotients[0], 1);
      return f;
    }
    if (depth == max) {
      Fraction<Type> f(quotients[depth], 1);
      return f;
    }
    Fraction<Type> f = ConvergeFromQuotients(max, depth + 1);

    f.Invert(); // 1/f
    f.n += (quotients[depth] * f.d); // e.g., 1 + 1/2 = 3 / 2
    return f;
  }

  // set quotients first with ExpansionFromRoot() or SetQuotients()
  // http://en.wikipedia.org/wiki/Continued_fraction#Infinite_continued_fractions
  Fraction<Type> GetNextConvergent() {
    Fraction<Type> convergent;
    if (next_convergent == 0) {
      f0 = Fraction<Type>(quotients[0], 1);
      convergent = f0;
    } else if (next_convergent == 1) {
      f1 = Fraction<Type>((quotients[0] * quotients[1]) + 1, quotients[1]);
      convergent = f1;
    } else {
      Type numerator = (quotients[next_convergent] * f1.n) + f0.n;
      Type denominator = (quotients[next_convergent] * f1.d) + f0.d;
      f0 = f1;
      f1 = Fraction<Type>(numerator, denominator);
      convergent = f1;
    }
    next_convergent++;
    return convergent;
  }

  void Reset() {
    next_convergent = 0;
    quotients.clear();
  }

  vector<int> ExpansionFromRoot(int S, int max) {
    // get the continued fraction expansion for the square root of S
    // algorithm from wolfram mathworld
    int m[max];
    int d[max];
    int n = 0;
    Reset();

    m[0] = 0;
    d[0] = 1;
    quotients.push_back(floor(sqrt(S)));

    while (n < max) {
      m[n+1] = d[n] * quotients[n] - m[n];
      d[n+1] = (S - (m[n+1] * m[n+1])) / d[n];
      if (d[n+1] == 0) {
        // not a recurring fraction
        quotients.clear();
        return quotients;
      }
      quotients.push_back(floor((quotients[0] + m[n+1]) / d[n+1]));
      n++;
    }
    return quotients;
  }

  vector<int> quotients;
  int next_convergent;
  Fraction<Type> f0;
  Fraction<Type> f1;
};

//int main(int argc, char* argv[]) {
//  int max = atoi(argv[1]);
//  ContinuedFraction<int> cf;
//  vector<int> v = cf.ExpansionFromRoot(4, 1000);
//  cf.PrintQuotients();
//  for (int i = 0; i < max; i++) {
//    cout << cf.GetNextConvergent() << endl;
//  }
//  return 0;
//}
