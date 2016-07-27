// should be using pascal's triangle here
#include <iostream>
#include <openssl/bn.h>
#include <stdlib.h>
#include <vector>

#include "combinations.h"

using namespace std;

// All combinations using elements between 0 and n
CombinationGenerator::CombinationGenerator(int n_) : n(n_) {
  combinations = new vector<vector<int>* >;
  smallest = 0;
  elements = NULL;
}

// All combinations using elements between m and n
CombinationGenerator::CombinationGenerator(int m_, int n_) : smallest(m_), n(n_) {
  combinations = new vector<vector<int>* >;
  elements = NULL;
}

// All combinations using items from elements
CombinationGenerator::CombinationGenerator(const vector<int>* elements_): elements(elements_) {
  combinations = new vector<vector<int>* >;
  smallest = 0; // first index here, not first element. Kind of hacky.
}

CombinationGenerator::~CombinationGenerator() {
  for (size_t i = 0; i < combinations->size(); ++i) {
    delete(combinations->at(i));
  }
  delete(combinations);
}

// record all subsets of size subset_size using possible numbers from start to n, or from 'elements'
void CombinationGenerator::RecordCombinations(int v[], int start, int population_size, int items_in_subset, int subset_size) {
  // v[]:added to the subset so far
  // start: the smallest possible number to add the subset, or the index in
  //   elements to start at
  // population_size: one more than the largest possible number to add to the subset, or
  //   the size of the elements vector
  // items_in_subset: how many items in the subset so far
  // subset_size: how many items the subset should contain

  // if the subset is full, record it
  if (items_in_subset == subset_size) {
    vector<int>* combination = new vector<int>;
    for (int i = 0; i < subset_size; ++i) {
      combination->push_back(v[i]);
      //cout << v[i] << " ";
    } //cout << endl;
    combinations->push_back(combination);
    return;
  }

  // otherwise add something to it
  for (int i = start; i < population_size; ++i) {
    // if we're selecting from a bunch of elements, add the next one...
    if (elements) {
      v[items_in_subset] = elements->at(i);
    }  else {
      // ...otherwise add the next integer
      v[items_in_subset] = i;
    }
    RecordCombinations(v, i+1, population_size, items_in_subset + 1, subset_size);
  }
}

// append all combinations of this size to the combinations list
void CombinationGenerator::GenerateCombinationsOfSize(int size) {
  int v[size]; // contains one combination
  for (int i = 0; i < size; ++i) {
    v[i] = 0;
  }

  int max;

  if (elements) {
    max = elements->size();
  } else {
    max = n;
  }

  if (size > max) {
    cout << "Can't generate subsets of size " << size << ": not enough elements" << endl;
    return;
  }

  RecordCombinations(v, smallest, max, 0, size);
}

void CombinationGenerator::GenerateAllCombinations() {
  int max;
  if (elements) {
    max = elements->size();
  } else {
    max = n;
  }
  for (int i = 1; i < max; ++i) {
    GenerateCombinationsOfSize(i);
  }
}

void CombinationGenerator::PrintCombinations() {
  for (size_t i = 0; i < combinations->size(); ++i) {
    const vector<int>* combination = combinations->at(i);
    for (size_t j = 0; j < combination->size(); ++j) {
      cout << combination->at(j) << " ";
    }
    cout << endl;
  }
}

vector<vector<int>* >* CombinationGenerator::GetCombinations() {
  return combinations;
}

long CombinationGenerator::Factorial(int n) {
  // 0! is 1.
  if (n == 0) {
    return 1;
  }
  long factorial = 1;
  for (int i = n; i > 0; i--) {
    factorial *= i;
  }
  return factorial;
}

// How many ways to take r from n
long CombinationGenerator::CombinationCount(int r, int n) {
  if (r > n) {
    cout << "ERROR: " << r << " > " << n << endl;
    return -1;
  }
  if (n >= 20) {
    cout << "ERROR: use BigCombinationCount." << endl;
    return -1;
  }
  return (Factorial(n) / (Factorial(r) * Factorial(n - r)));
}

#ifdef CRYPTO_BIGNUM

void CombinationGenerator::BigFactorial(int n, BN_CTX* context, BIGNUM* factorial) {
  BN_init(factorial);
  BN_set_word(factorial, 1);
  BIGNUM big_n;
  BN_init(&big_n);

  for (int i = n; i > 0; i--) {
    BN_set_word(&big_n, i);
    BN_mul(factorial, factorial, &big_n, context);
  }
}

long CombinationGenerator::BigCombinationCount(int r, int n, BN_CTX* context) {
  context = BN_CTX_new();

  BIGNUM factorial_n;
  BN_init(&factorial_n);
  BIGNUM factorial_r;
  BN_init(&factorial_r);
  BIGNUM factorial_n_r;
  BN_init(&factorial_n_r);

  BigFactorial(n, context, &factorial_n);
  BigFactorial(r, context, &factorial_r);
  BigFactorial(n - r, context, &factorial_n_r);
  BN_div(&factorial_n, NULL, &factorial_n, &factorial_r, context);
  BN_div(&factorial_n, NULL, &factorial_n, &factorial_n_r, context);

  return atol(BN_bn2dec(&factorial_n));
}
#endif  // CRYPTO_BIGNUM
