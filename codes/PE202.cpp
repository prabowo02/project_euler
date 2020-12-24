#include <bits/stdc++.h>
using namespace std;

long long multiply(long long a, long long b, long long m) {
  long long y = (long long) ((long double) a * (long double) b / m + 0.5);
  y = y * m;
  long long x = a * b;
  long long ret = x - y;
  if (ret < 0) ret += m;
  return ret;
}

long long gcd(long long x, long long y) {
  return y ? gcd(y, x % y) : x;
}

long long power(long long x, long long y, long long mod) {
  long long result = 1;
  long long multiplicator = x % mod;
  for (; y; y >>= 1) {
    if (y & 1) result = multiply(result, multiplicator, mod);
    multiplicator = multiply(multiplicator, multiplicator, mod);
  }

  return result;
}

bool isPrime(long long n) {
  if (!(n & 1)) return false;

  long long d = n-1, s = 0;
  while (!(d & 1)) s++, d >>= 1;
  
  srand(time(NULL));
  
  for (long long i = 0; i < 32; i++) {
    long long a = rand();
    a <<= 32;
    a += rand();
    a = a % (n - 1) + 2;
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) continue;
    for (long long j = 1; j < s; j++) {
      x = multiply(x, x, n);
      if (x == 1) return false;
      if (x == n - 1) break;
    }
    if (x != n - 1) return false;
  }
  return true;
}

long long pollardRho(long long n) {
  if (n == 1) return n;
  if (n & 1) {
    if (isPrime(n)) return n;
    srand(time(NULL));
    long long x = (rand() % (n-2)) + 2;
    long long y = x;
    long long c = (rand() % (n-1)) + 1;
    long long d = 1;
    while (d == 1) {
      x = (multiply(x, x, n) + c + n) % n;
      y = (multiply(y, y, n) + c + n) % n;
      y = (multiply(y, y, n) + c + n) % n;
      d = gcd(abs(x - y), n);
      if (d == n) return pollardRho(n);
    }
    return d;
  } else return 2;
}

long long squareRoot(long long n) {
  long long l = 1, r = 1000000000;
  
  while (l <= r) {
    long long mid = l + r >> 1;
    if (mid * mid < n) l = mid + 1;
    else if (mid * mid > n) r = mid - 1;
    else return mid;
  }
  
  return -1;
}

vector<long long> primeFactors(long long n) {
  vector<long long> ret;
  for (int i=2; i<=1000000; i++) {
    if (n % i == 0) {
      ret.push_back(1LL * i);
      do {
        n /= i;
      } while (n % i == 0);
      
      if (n == 1) break;
    }
  }
  
  if (n == 1) return ret;
  long long s = squareRoot(n);
  if (s != -1) {
    ret.push_back(s);
    return ret;
  }
  
  if (isPrime(n)) {
    ret.push_back(n);
    return ret;
  }
  
  ret.push_back(pollardRho(n));
  ret.push_back(n / ret.back());
  return ret;
}

// The number of integer y = 1..n that is coprime to n, and x = y (mod 3)
// Assumption: x != n (mod 3) and n != 0 (mod 3) and x != 0 (mod 3)
long long countCoprime3(long long n, long long x) {
  long long ret = 0;
  vector<long long> ps = primeFactors(n);
  // for (long long p: ps) cerr << p << endl;
  
  for (int i=0; i<1<<ps.size(); i++) {
    long long mul = 1;
    for (int j=0; j<ps.size(); j++) {
      if (i >> j & 1) mul *= ps[j];
    }
    
    long long term = n / (mul * 3);
    if (mul % 3 != x) term += (n % (mul * 3) >= mul * 2);
    else term += (n % (mul * 3) >= mul);
    
    // cerr << mul << " " << term << endl;
    
    if (__builtin_popcount(i) & 1) ret -= term;
    else ret += term;
  }
  
  return ret;
}

int main() {
  int q;
  scanf("%d", &q);
  
  while (q--) {
    long long n;
    scanf("%lld", &n);
    if (n & 1); else {
      printf("0\n");
      continue;
    }
    
    long long N = n + 3 >> 1;
    if (N % 3 == 0) {
      printf("0\n");
      continue;
    }
    
    printf("%lld\n", countCoprime3(N, 3 - N % 3));
  }
  return 0;
}
