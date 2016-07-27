#include <iostream>
#include <math.h>
#include <vector>

#include "triangle.h"

using namespace std;

template <class Type>
TriangleGenerator<Type>::TriangleGenerator() {
  triangles = new vector<Type>;
  count = 0;
  lastadded = 0;
  lasttriangle = 0;
}

template <class Type>
Type TriangleGenerator<Type>::GetNext() {
  lastadded++;
  lasttriangle += lastadded;
  count++;
  return lasttriangle;
}

template <class Type>
Type TriangleGenerator<Type>::GetNth(Type n) {
  return (n * (n + 1) / 2);
}

template <class Type>
void TriangleGenerator<Type>::Reset() {
  lastadded = 0;
  lasttriangle = 0;
}

template <class Type>
bool TriangleGenerator<Type>::IsTriangle(Type t) {
  Type guess = floor(sqrt(t * 2));
  if (GetNth(guess) == t) {
    return true;
  } else {
    return false;
  }
}

