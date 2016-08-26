#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

template <class Type>
class TriangleGenerator {
public:
  TriangleGenerator() {
    triangles = new vector<Type>;
    count = 0;
    lastadded = 0;
    lasttriangle = 0;
  }

  Type GetNext() {
    lastadded++;
    lasttriangle += lastadded;
    count++;
    return lasttriangle;
  }

  Type GetNth(Type n) {
    return (n * (n + 1) / 2);
  }

  void Reset() {
    lastadded = 0;
    lasttriangle = 0;
  }

  bool IsTriangle(Type t) {
    Type guess = floor(sqrt(t * 2));
    if (GetNth(guess) == t) {
      return true;
    } else {
      return false;
    }
  }

 private:
  vector<Type>* triangles;
  Type lastadded;
  Type lasttriangle;
  int count;
};

