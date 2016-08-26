#include <iostream>
#include <vector>
#include <math.h>

#include "primefactor.h"

using namespace std;

PrimeFactorer::PrimeFactorer() {
  record_duplicates_ = false;
}

void PrimeFactorer::SetDuplicates(bool dupes) {
  record_duplicates_ = dupes;
}

int PrimeFactorer::GetPrimeFactorCount(long composite) {
  // uses the value of record_duplicates_; defaults to false
  vector<long> primes;
  GetPrimeFactors(composite, primes);
  return primes.size();
}

// I'm no longer clear on why this works... hurray!
int PrimeFactorer::GetFactorCount(long composite) {
  SetDuplicates(true);
  vector<int>* exponents = new vector<int>;
  GetPrimeFactorsWithExponents(composite, exponents);

  int factors = 1;
  for (vector<int>::const_iterator it = exponents->begin();
       it != exponents->end(); it++) {
    factors *= (*it + 1);
  }
  SetDuplicates(false);
  delete(exponents);
  return factors;
}

// Return all the prime factors for this number
// record_duplicates_ determines whether it'll record a full set of
// factors, or just unique ones.
void PrimeFactorer::GetPrimeFactors(long composite, vector<long>& primes) {
  if (composite == 0) {
    return;
  }
  int largestfactor = 1;
  if (composite % 2 == 0) {
    composite = composite / 2;
    primes.push_back(2);
    largestfactor = 2;
    while (composite % 2 == 0) {
      composite = composite / 2;
      if (record_duplicates_) {
        primes.push_back(2);
      }
    }
  }
  // every number n can at most have one prime factor greater than root n
  long factor = 3;
  long ceiling = sqrt(composite);
  while ((composite > 1) && (factor <= ceiling)) {
    if (composite % factor == 0) {
      primes.push_back(factor);
      largestfactor = factor;
      composite = composite / factor;
      while (composite % factor == 0) {
        composite = composite / factor;
        if (record_duplicates_) {
          primes.push_back(factor);
        }
      }
      ceiling = sqrt(composite);
    }
    factor += 2;
  }
  // if this doesn't get us the whole way to 1, the remaining number is prime
  if (composite != 1) {
    largestfactor = composite;
    primes.push_back(composite);
  }
  printf("Largest factor was %d\n", largestfactor);
  return;
}

// Pretty much a duplicate of GetPrimeFactors, but
// separated to reduce reading-complexity.
vector<long> PrimeFactorer::GetPrimeFactorsWithExponents(long composite, vector<int>* return_exponents) {
  vector<long> primes;
  if (composite == 0) {
    return primes;
  }
  int exponent = 0;
  int largestfactor = 1;
  if (composite % 2 == 0) {
    composite = composite / 2;
    primes.push_back(2);
    exponent++;
    largestfactor = 2;
    while (composite % 2 == 0) {
      composite = composite / 2;
      exponent++;
      if (record_duplicates_) {
        primes.push_back(2);
      }
    }
    return_exponents->push_back(exponent);
  }
  // every number n can at most have one prime factor greater than root n
  long factor = 3;
  long ceiling = sqrt(composite);
  while ((composite > 1) && (factor <= ceiling)) {
    if (composite % factor == 0) {
      exponent = 1;
      primes.push_back(factor);
      largestfactor = factor;
      composite = composite / factor;
      while (composite % factor == 0) {
        composite = composite / factor;
        exponent++;
        if (record_duplicates_) {
          primes.push_back(factor);
        }
      }
      ceiling = sqrt(composite);
      return_exponents->push_back(exponent);
    }
    factor += 2;
  }
  // if this doesn't get us the whole way to 1, the remaining number is prime
  if (composite != 1) {
    largestfactor = composite;
    primes.push_back(composite);
    return_exponents->push_back(1);
  }
  printf("Largest factor was %d\n", largestfactor);
  return primes;
}
