#include <bits/stdc++.h>
using namespace std;

const int N = 11181000;
bool prime[N];

vector<int> primes;
vector<long long> squbes;

long long multiply(long long a, long long b, long long m) {
  long long y = (long long) ((long double) a * (long double) b / m + 0.5);          
    long long ret = a * b - y * m;
  if (ret < 0) return ret + m;
  return ret;
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
  if (n < N) return prime[n];
  if (!(n & 1)) return false;

  long long d = n-1, s = 0;
    s = __builtin_ctzll(d), d >>= s;
  // while (!(d & 1)) s++, d >>= 1; 
  
  for (int i = 0; i < 1; i++) {
    long long a = rand();
    a = a % (n - 3) + 2;    
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1) continue;
    for (int j = 1; j < s; j++) {
      x = multiply(x, x, n);
      if (x == 1) return false;
      if (x == n - 1) break;
    }
    if (x != n - 1) return false;
  }
  return true;
}

int main() {
  clock_t t = clock();
  primes.reserve(740000);
  squbes.reserve(2000000);

  memset(prime, 1, sizeof prime);
  prime[0] = prime[1] = false;
  for (int i=2; i<N; i++) if (prime[i]) {
    for (int j=i*2; j<N; j+=i) prime[j] = false;
    primes.push_back(i);
  }
  
  for (int p: primes) {
    for (int q: primes) {
      if (p == q) continue;
      if (1LL * p*p * q*q*q >= 1000000000000000LL) break;
      squbes.push_back(1LL * p*p * q*q*q);
    }
  }  
  
  int s;
  scanf("%d", &s);
  
  vector<long long> ans;  
  
  for (long long sqube: squbes) {
    bool contain = false;
    int len = 2;
    long long tmp = sqube;
    while (tmp >= 100) {
      if (tmp % 1000 == s) contain = true;
      tmp /= 10; len++;
    }
    if (!contain) continue;
    
    bool primeproof = true;
    long long ten = 1;
    for (int i = len-1; i>=0; i--) {
      if ((sqube % 10 == 5 || sqube % 2 == 0) && ten == 10) break;
      for (int j=0; j<=9; j++) {
        int diff = j - (sqube / ten % 10);
        if (diff == 0) continue;
        
        if (isPrime(sqube + ten * diff)) {
          primeproof = false;
          break;
        }
        
      }
      
      if (!primeproof) break;
      ten *= 10;
    }
    
    if (primeproof) ans.push_back(sqube);
  }
  
  cerr << ans.size() << endl;
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  sort(ans.begin(), ans.end());
    
  int q, n;
  scanf("%d", &q);
  while (q--) {    
    scanf("%d", &n);
    printf("%lld\n", ans[n-1]);
  }
    
  return 0;
}
