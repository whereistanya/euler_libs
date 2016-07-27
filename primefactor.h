#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class PrimeFactorer {
 public:
  PrimeFactorer();
  ~PrimeFactorer() {}

  void SetDuplicates(bool dupes);

  int GetPrimeFactorCount(long composite);

  int GetFactorCount(long composite);

  // Return all the prime factors for this number
  // record_duplicates_ determines whether it'll record a full set of
  // factors, or just unique ones.
  void GetPrimeFactors(long composite, vector<long>& primes);
 
  // Pretty much a duplicate of GetPrimeFactors, but
  // separated to reduce reading-complexity.
  vector<long> GetPrimeFactorsWithExponents(long composite, vector<int>* return_exponents);

 private:
  bool record_duplicates_;
};
