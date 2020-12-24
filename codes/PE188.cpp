#include <bits/stdc++.h>
using namespace std;

const int P = 1000001;
bool prime[P];
vector<int> primes;

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
  if (n <= 3 || n == 5) return true;
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

long long phi(long long n) {
    long long res = n;
    for (int p: primes) {
        if (n % p == 0) {
            res /= p;
            res *= p-1;
            
            do {
                n /= p;
            } while (n % p == 0);
            
            if (n == 1) break;
        }
    }
    
    if (n == 1) return res;
    
    if (isPrime(n)) return res / n * (n-1); 
    long long p = pollardRho(n); 
    long long q = n / p;
    assert(p * q == n);
    
    if (p == q) return res / p * (p-1);
    
    return res / p * (p-1) / q * (q-1);
}

long long tetration(long long a, long long b, long long m) {
    if (m == 1) return 0;
    if (b == 1) return a;

    long long euler = phi(m);
    long long e = tetration(a, b-1, euler);
    if (e < 64 && (a >= 64 || a > 3 && b > 2 || a == 3 && b > 3 || a == 2 && b > 4)) {
        do {
            e += euler;
        } while (e < 64);
    }
        
    return power(a, e, m);
}

int main() {
    for (int i=2; i<P; ++i) prime[i] = 1;
    for (int i=2; i<P; ++i) if (prime[i]) {
        primes.push_back(i);
        for (int j=i*2; j<P; j+=i) prime[j] = 0;
    }
    
    int q;
    scanf("%d", &q);
    while (q--) {
        long long a, b, m;
        scanf("%lld %lld %lld", &a, &b, &m);
        printf("%lld\n", tetration(a, b, m));
    }
    return 0;
}
