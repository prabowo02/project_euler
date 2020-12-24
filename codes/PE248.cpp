#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>

using std::pair;
using std::sort;
using std::vector;

long long multiply(long long a, long long b, long long m) {
  long long y = (long long) ((long double) a * (long double) b / m + 0.5);
  y = y * m;
  long long x = a * b;
  long long ret = x - y;
  if (ret < 0) ret += m;
  return ret;
}

// x and y are non-negative
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

vector<long long> A_Miller_Rabin = {2, 3, 5, 7, 11}; // N <= 2 * 10^12
bool isPrime(long long n) {
  if (n <= 3 || n == 5 || n == 7 || n == 11) return true;
  if (!(n & 1)) return false;

  long long s = __builtin_ctzll(n-1), d = n-1 >> s;
  
  for (long long a: A_Miller_Rabin) {
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

// Assume n is not prime
long long pollardRho(long long n) {
  if (n == 1) return n;
  if (n & 1) {
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

// Returns list of p_k, e_k, where prod(p_k^e_k) = n. p_k is NOT sorted
vector<pair<long long, int>> primeFactorization(long long n) {
  vector<pair<long long, int>> ret;
  
  for (long long p = 2; p*p*p <= n; ++p) {
    if (n % p > 0) continue;
    
    int e = 0;
    do {
      ++e;
      n /= p;
    } while (n % p == 0);
    
    ret.push_back({p, e});
    
    if (n == 1) return ret;
  }

  long long sqrtn = (long long) round(sqrt(n));
  if (sqrtn * sqrtn == n) {
    ret.push_back({sqrtn, 2});
    return ret;
  }
  
  if (isPrime(n)) {
    ret.push_back({n, 1});
    return ret;
  }
  
  long long p = pollardRho(n);
  long long q = n/p;
  
  ret.push_back({p, 1});
  ret.push_back({q, 1});
  return ret;
}

// Return divisors of n = prod(p_k^e_k). Returned list is NOT sorted
vector<long long> divisors(vector<pair<long long, int>> v) {
  vector<long long> ret;
  ret.push_back(1LL);
  
  for (pair<long long, int> pe: v) {
    long long p = pe.first;
    int e = pe.second;
    int sz = ret.size();
    
    for (int i=0; i<sz; i++) {
      long long num = 1;
      for (int j=0; j<e; j++) {
        num *= p;
        ret.push_back(ret[i] * num);
      }
    }
  }
  
  return ret;
}

// Return divisors of n. Returned list is NOT sorted
vector<long long> divisors(long long n) {
  return divisors(primeFactorization(n));
}

long long euler_phi(long long n) {
  for (pair<long long, int> pe: primeFactorization(n)) {
    long long p = pe.first;
    
    n /= p; n *= p-1;
  }
  
  return n;
}

namespace PE248 {

vector<long long> nums;
vector<long long> nearPrimeDivisors;
void dfs(long long m, int idx, long long num) {
  if (m == 1) return nums.push_back(num);
  if (idx == nearPrimeDivisors.size()) return;

  long long d = nearPrimeDivisors[idx];
  if (d <= m/d) {
    dfs(m, idx+1, num);
    for (long long factorM = d, factorNum = d+1;;) {
      if (m % factorM != 0) break;

      dfs(m/factorM, idx+1, num * factorNum);

      if (factorM <= m / (d+1)) {
        factorM *= (d+1);
        factorNum *= (d+1);
      } else {
        break;
      }
    }
  } else if (d <= m && binary_search(nearPrimeDivisors.begin(), nearPrimeDivisors.end(), m)) {
    nums.push_back(num * (m+1));
  }
}

// Returns a list of n where phi(n) = m
vector<long long> phidentity(long long m) {
  // List of d where d | m and d+1 is   prime
  nearPrimeDivisors.clear();
  for (long long d: divisors(m)) {
    if (isPrime(d+1)) {
      nearPrimeDivisors.push_back(d);
    }
  }

  sort(nearPrimeDivisors.begin(), nearPrimeDivisors.end());
  nums.clear();

  dfs(m, 0, 1);
  return nums;
}

}

int main() {
  long long m; int q;
  scanf("%lld %d", &m, &q);

  vector<long long> ans = PE248::phidentity(m);
  fprintf(stderr, "%lu\n", ans.size());
  sort(ans.begin(), ans.end());

  if (m == 1) ans = {1, 2};
  while (q--) {
    int k;
    scanf("%d", &k);
    printf("%lld\n", ans[--k]);
  }
  return 0;
}
