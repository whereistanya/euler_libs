// should be using pascal's triangle here
#include <iostream>
#include <openssl/bn.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class CombinationGenerator {
public:
// All combinations using elements between 0 and n
  CombinationGenerator(int n_);

// All combinations using elements between m and n
  CombinationGenerator(int m_, int n_);

// All combinations using items from elements
  CombinationGenerator(const vector<int>* elements_);
  
  ~CombinationGenerator();
 
// record all subsets of size subset_size using possible numbers from start to n, or from 'elements'
  void RecordCombinations(int v[], int start, int population_size, int items_in_subset, int subset_size);
 
// append all combinations of this size to the combinations list
  void GenerateCombinationsOfSize(int size);
 
  void GenerateAllCombinations();
  
  void PrintCombinations();
 
  vector<vector<int>* >* GetCombinations();

private:
  const vector<int>* elements; // possible elements for subset; incompatible with n
  vector<vector<int>* >* combinations;
  int smallest;
  int n; // elements in subset are smaller than this; incompatible with elements vector

  long Factorial(int n);

  // How many ways to take r from n
  long CombinationCount(int r, int n);
};

#ifdef CRYPTO_BIGNUM

void BigFactorial(int n, BN_CTX* context, BIGNUM* factorial) {
  BN_init(factorial);
  BN_set_word(factorial, 1);
  BIGNUM big_n;
  BN_init(&big_n);

  for (int i = n; i > 0; i--) {
    BN_set_word(&big_n, i);
    BN_mul(factorial, factorial, &big_n, context);
  }
}

long BigCombinationCount(int r, int n, BN_CTX* context) {
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


