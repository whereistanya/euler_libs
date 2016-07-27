// a eratosthenes sieve method of generating primes. It takes four seconds
// to check the first ten million ints for primeness, and less than a second for the
// first two million.
#include <bitset>
#include <iostream>

#include "primechecker.h"

using namespace std;

PrimeChecker::PrimeChecker() {
  // 0 and 1 are not prime
  a.set(0, 1);
  a.set(1, 1);

  prime_index = 0;
  long primer = 2;

  while (primer < (max / 2)) {
    for (long i = 2; (primer * i) < max; i++) {
      long product = primer * i;
      // 1 means not a prime
      a.set(product, 1);
    }
    primer++;
  }
  cout << "Finished generating primes." << endl;
}

bool PrimeChecker::IsPrime(long i) {
  if (i > max) {
    cout << "Out of bounds " << i << endl;
    return false;
  }
  // 1 means not a prime
  if (a[i] == 1)
    return false;
  return true;
}

void PrimeChecker::CountPrimes() {
  cout << "Number of primes below " << max << " is "
       << (max - a.count()) << endl;
}

long PrimeChecker::SumPrimes() {
  long sum = 0;
  for (int i = 0; i < max; i++) {
    if (a[i] == 0) {
      sum += i;
    }
  }
  cout << "The sum of primes below " << max << " is: " << sum << endl;
  return sum;
}

long PrimeChecker::GetNthPrime(int n) {
  int count = 0;
  for (int i = 0; i < max; i++) {
    if (a[i] == 0) {
      count++;
    }
    if (count == n) {
      cout << "The " << n << "th prime is " << i << endl;
      return i;
    }
  }
  return -1;
}

long PrimeChecker::GetNextPrime() {
  for (int i = prime_index + 1; i < max; i++) {
    if (a[i] == 0) {
      prime_index = i;
      return i;
    }
  }
  // hit the max without finding a prime
  cout << "Not checking primes bigger than " << max << ": nothing to"
       << " return. Returning -1." << endl;
  return -1;
}

void PrimeChecker::ResetIndex() {
  prime_index = 0;
}
