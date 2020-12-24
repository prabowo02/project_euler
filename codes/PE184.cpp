/**
 * It will be much easier to consider the number of triangles which does not contain origin.
 * For simplicity, we will ignore the origin.
 *
 * Consider all the vectors from origin to lattice points. 
 * We group all the vectors that have the same direction.
 * Let the size of each group be b_1, b_2, ..., b_k, where k is the number of distinct vector direction.
 * Assume we have found these values of b, we can easily find the number of triangles that does not contain origin.
 *
 * To find the value of b, we can find the number of x and y, without loss of generality, x, y > 0 
 * such that gcd(x, y) = 1, 2, ..., r-1.
 * To find gcd(x, y) > 1, we can simply modify our equation (dx)^2 + (dy)^2 < r^2 to x^2 + y^2 < (r/d)^2 where d is the gcd(x, y) > 1.
 * Our task is now to find the number of (x, y) such that the gcd(x, y) = 1 when x^2 + y^2 < r_i^2 where r_i = r / i.
 * This can be done using Sieve of Eratosthenes + Inclusion-Exclusion.
 */

#include <bits/stdc++.h>
using namespace std;

#define double long double

const int N = 1000001;
const int MOD = 1000000007;

vector<int> primes[N];
long long c[N];

int main() {
  clock_t t = clock();
  for (int i=2; i<N; i++) if (primes[i].size() == 0) {
    for (int j=i; j<N; j+=i) primes[j].push_back(i);
  }
  
  int r;
  scanf("%d", &r);
    
  for (int d=1; d<r; d++) {
    long long r2 = 1LL * r * r / d / d;
    double dr2 = (double) r / d * r / d;
    // cerr << "r2: " << r2 << endl;
    
    for (long long i=1; i*i<r2; i++) {
      int len = int(sqrt(dr2 - i*i) - 1e-9);
      int cnt = len;
      // cerr << "len: " << len << endl;
      for (int j=1; j<1<<primes[i].size(); j++) {
        long long prod = 1;
        for (int k=0; k<primes[i].size(); k++) {
          if (j >> k & 1) prod *= primes[i][k];
        }
        if (__builtin_popcount(j) & 1) cnt -= len / prod;
        else cnt += len / prod;
      }
      // cerr << "cnt: " << cnt << endl;
      c[d] += cnt;
    }
  }
  
  for (int i=1; i<r; i++) {
    c[i] *= 4;
  }
  
  for (int i=2; i<r; i++) c[i-1] -= c[i];
  c[r-1] += 4;
  
  // for (int i=1; i<r; i++) cerr << c[i] << endl;
  
  long long sum = 0, sum2 = 0, sum3 = 0;  
  for (int i=1; i<r; i++) {
    sum += 1LL * i * c[i] % MOD;
    sum2 += 1LL * i * i % MOD * c[i] % MOD;
    sum3 += 1LL * i * i * i % MOD * c[i] % MOD;
  }
  sum %= MOD; sum2 %= MOD; sum3 %= MOD;
  
  long long ans = (sum-2) * sum % MOD * (sum-1) % MOD * 166666668 % MOD; 
  
  long long a = sum * 500000004 % MOD;
  ans -= ((3LL*a*a % MOD - 6LL*a + 2LL) % MOD * sum % MOD + 3LL*a*sum2 % MOD - 2LL*sum3) % MOD * 166666668LL % MOD;
  ans %= MOD;
  
  if (ans < 0) ans += MOD;
  printf("%lld\n", ans);
  
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
