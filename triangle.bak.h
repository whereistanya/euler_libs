#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

template <class Type>
class TriangleGenerator {
 public:
  TriangleGenerator();
  ~TriangleGenerator() {}

  Type GetNext();
  Type GetNth(Type n);
  void Reset();
  bool IsTriangle(Type t);
 private:
  vector<Type>* triangles;
  Type lastadded;
  Type lasttriangle;
  int count;
};
