// a eratosthenes sieve method of generating primes. It takes four seconds
// to check the first ten million ints for primeness, and less than a second for the
// first two million.
#include <bitset>
#include <iostream>

using namespace std;

class PrimeChecker {
 public:
  PrimeChecker();

  bool IsPrime(long i);

  void CountPrimes();

  long SumPrimes();

  long GetNthPrime(int n);

  long GetNextPrime();

  void ResetIndex();
 private:
  static const long max = 1000000;
  bitset<max> a;
  int prime_index;
};

//int main(int argc, char* argv[]) {
//  PrimeChecker* pc = new PrimeChecker();
//
//  return 0;
//}
