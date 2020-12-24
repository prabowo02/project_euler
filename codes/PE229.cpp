/**
From the proof of Fermat's sum of two squares theorem, we can find that for a prime p:
p = a^2 + k*b^2 if and only if (-k / p) = 1, where (a / p) is legendre symbol.

Find the criterion using Law of Quadratic Reciprocity, turns out that:
p = 1 mod 4 for p = a^2 + b^2
p = 1, 3 mod 8 for p = a^2 + 2b^2
p = 1 mod 3 for p = a^2 + 3b^2
p = 1, 2, 4 mod 7 for p = a^2 + 7b^2

Using CRT, merge the equivalences into:
p = 1, 25, 121 mod 168

Therefore, n is very special if and only if the prime decomposition of p that has odd power is either p = 1, 2 or 121 mod 168. In other word, write n = a^2 * b where b is square free, then the prime factorization of b contains only p = 1, 2, or 121 mod 168.

To find such primes, use sieve of eratosthenes by noticing that n = m (mod p) if and only if p | 168n + k and p | 168m + k. To further improve the time, sieve it segment by segment so that it is cache friendly.

Because a_k and b_k cannot be 0, we have to handle the case where n is a square separately.
This can be done by a method similarly to generating pythagorean triples: Look for z where z^2 = a_k^2 + k * b_k^2 has positive integers solution.
*/

#include <bits/stdc++.h>
using namespace std;

const long long N = 5000000000LL;
const long long NN = N / 168 + 5;
const int SN = sqrt(N) + 2;

vector<int> primes;
bool isPrime[SN];
void initPrimes() {
  memset(isPrime, true, sizeof isPrime);
  for (int i=2; i<SN; i++) if (isPrime[i]) {
    primes.push_back(i);
    for (int j=i*2; j<SN; j+=i) isPrime[j] = false;
  }
}

long long gcd(long long x, long long y) {
  return y ? gcd(y, x % y) : x;
}

char mask[SN];
vector<long long> invalidSquares;
void initInvalidSquares(int k, int bit) {
  for (int m=2; m*m<SN*k; m++) {
    for (int n=1; n<m; n++) {
      if (gcd(n, m) != 1) continue;
      
      long long a = 1LL*m*m - 1LL*k*n*n;
      long long b = 2LL*m*n;
      long long c = 1LL*m*m + 1LL*k*n*n;
      
      if (a <= 0) break;
      
      long long d = gcd(a, gcd(b, c));
      c /= d;
      
      for (long long i=c; i<SN; i+=c) mask[i] |= 1 << bit;
    }
  }
}

int power(int x, int y, int m) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % m;
    x = 1LL * x * x % m;
  }
  
  return ret;
}

bool prime168[NN];
void generatePrimes(int k, int &sz, long long a[]) {  
  memset(prime168, true, sizeof prime168);
  
  vector<pair<int, int>> v;
  for (int p: primes) {
    if (168 % p == 0) continue;
    
    int x = 1LL * (p - k%p) * power(168, p-2, p) % p;
    if (168LL * x + k != p) prime168[x] = false;
    
    v.push_back({x, p});
    // for (int j=x+p; j<NN; j+=p) prime168[j] = false;
  }
  
  const int L = 200000;
  
  sz = 0;
  for (int l = 1; l < NN; l+=L) {
    int r = min(1LL * l + L, NN);
    
    for (pair<int, int> pp: v) {
      int x = pp.first;
      int p = pp.second;
      int k = (l - x + p-1) / p;
      k += (k == 0);
      
      for (int j=x + k*p; j<r; j+=p) prime168[j] = false;
    }
    
    for (int j=l; j<r; j++) if (prime168[j]) {
      a[sz++] = 168LL*j + k;
    }
  }
  
  cerr << sz << endl;
}

int sz[3];
long long p168[3][5000000];

void init() {
  initPrimes();
  
  generatePrimes(1, sz[0], p168[0]);
  generatePrimes(25, sz[1], p168[1]);
  generatePrimes(121, sz[2], p168[2]);
  
  initInvalidSquares(1, 0);
  initInvalidSquares(2, 1);
  initInvalidSquares(3, 2);
  initInvalidSquares(7, 3);
  
  for (int i=1; i<SN; i++) {
    if (mask[i] != 15) invalidSquares.push_back(1LL*i*i);
  }
}

long long f(int k, int x, long long n) {
  if (k == 3) return (long long) floor(sqrt(n));
  if (x == sz[k] || n < p168[k][x]) return f(k+1, 0, n);
  
  return f(k, x+1, n / p168[k][x]) + f(k, x+1, n);
}

void solve() {
  long long n;
  scanf("%lld", &n);
  
  printf("%lld\n",
    f(0, 0, n) - 
    (upper_bound(invalidSquares.begin(), invalidSquares.end(), n) - invalidSquares.begin())
  );
}

int main() {
  clock_t t = clock();
  
  init();
  int q;
  scanf("%d", &q);
  while (q--) solve();
  
  fprintf(stderr, "%.6lf\n", (double) (clock() - t) / CLOCKS_PER_SEC);
  return 0;
}
