/**
* The number of lattice points that pass through the circle x^2 + y^2 = n is:
*   Let n = 2^a0 * p1^a1 * p2^a2 * ... * pr^ar * q1^b1 * q2^b2 * ... * qs^bs
*   where pi is prime 3 mod 4 while qi is prime 1 mod 4
* 
*   If ai is not even for any i > 0, then the number of lattice points is 0
*   Otherwise, the number of lattice points is (b1 + 1) * (b2 + 2) + ... + (bs + 1)
*   Reference: http://mathworld.wolfram.com/SumofSquaresFunction.html
*
* Back to original problem:
* If n is even, the number of lattice points is actually the same as number of lattice points on x^2 + y^2 = n^2 / 2
*   Obtained by translating the equation such that the circle is at origin
* If n is odd, the number of lattice points is actually the same as number of lattice points on x^2 + y^2 = 2 n^2
*   Obtained in similar manner as the even case: translate to origin, then notice that a point belongs to the untranslated lattice point
*     if and only if the point lies on (x + 0.5) and (y + 0.5). Therefore, we enlarge the circle by a factor of 2
*
* Notice that both equation has its RHS squared, therefore we the 3 (mod 4) primes can be arbitrary.
* Our only restriction is that the 1 (mod 4) primes must satisfy m = (2b1 + 1) * (2b2 + 2) * ..., where bi are their exponents
*
* The rest is trivial, except for finding number of primes 4k+1 < n, for some large n
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 316500;

long long n;
int m;

bool is_prime[N];
vector<int> primes_4k_1;
vector<int> primes_4k_3;
void generate_primes(int n) {
  for (int i = 2; i <= n; ++i) is_prime[i] = true;

  for (int p = 2; p*p <= n; ++p) {
    if (!is_prime[p]) continue;
    for (int j = p*2; j < n; j += p) {
      is_prime[j] = false;
    }
  }

  primes_4k_3.push_back(2);
  for (int p = 3; p <= n; ++p) {
    if (is_prime[p]) {
      if (p & 2) primes_4k_3.push_back(p);
      else primes_4k_1.push_back(p);
    }
  }
}

int sn;
long long dp1[N*2], dp3[N*2];
vector<long long> n_div_i;
void compute_primes_mod_4(long long n) {
  n_div_i.clear();

  for (long long i = 1; i*i <= n; ++i) {
    n_div_i.push_back(n / i);
  }
  sn = n_div_i.size();
  for (int i = n_div_i.back() - 1; i > 0; --i) {
    n_div_i.push_back(i);
  }

  for (int i = 0; i < n_div_i.size(); ++i) {
    dp1[i] = n_div_i[i] - 1 >> 2; // init with number of 1 (mod 4) integers <= n_div_i and > 2
    dp3[i] = n_div_i[i] + 1 >> 2; // Number of 3 (mod 4) integers <= n_div_i and > 2
  }

  for (int p = 3; p <= sn; ++p) {
    if (is_prime[p]) {
      long long p2 = 1LL * p * p;

      long long sp1 = dp1[n_div_i.size() - p + 1]; // the count up to p-1
      long long sp3 = dp3[n_div_i.size() - p + 1];

      // "Sieve" the prime p for all dp
      for (int j = 0; j < n_div_i.size(); ++j) {
        if (n_div_i[j] < p2) break;

        // Actually try to find dp that stores 1 .. n_div_i[j] / p
        long long idx = n_div_i[j] / p;
        idx = (idx <= sn ? n_div_i.size() - idx : (j+1) * p - 1);

        // 4k + 3
        if (p & 2) {
          dp1[j] -= dp3[idx] - sp3;
          dp3[j] -= dp1[idx] - sp1;
        } else {
          dp1[j] -= dp1[idx] - sp1;
          dp3[j] -= dp3[idx] - sp3;
        }
      }
    }
  }
}

inline int dp_idx(long long n) {
  return n <= sn ? n_div_i.size() - n : ::n/n - 1;
}

// Count number of integers <= n s.t. all its prime factorization is 3 (mod 4)
long long count_4k_3(long long n, int x=0) {
  if (1LL * primes_4k_3[x] * primes_4k_3[x] > n) {

    return dp3[dp_idx(n)] + (n >= 2) - x + 1;
  }

  return count_4k_3(n / primes_4k_3[x], x) + count_4k_3(n, x+1);
}

// Count number of integers <= n s.t. exactly one of its prime factorization is 1 (mod 4)
long long count_one_4k_1(long long n, int x1=0, int x3=0) {
  if (primes_4k_1[x1] < primes_4k_3[x3]) {
    if (1LL * primes_4k_1[x1] * primes_4k_1[x1] > n) {
      return dp1[dp_idx(n)] - x1;
    }

    return count_4k_3(n / primes_4k_1[x1], x3) + count_one_4k_1(n, x1+1, x3);
  }

  if (1LL * primes_4k_3[x3] * primes_4k_3[x3] > n) {
    return max(0LL, dp1[dp_idx(n)] - x1);
  }

  return count_one_4k_1(n / primes_4k_3[x3], x1, x3) + count_one_4k_1(n, x1, x3+1);
}

// Count number of integers <= n s.t. it has prime factorization 1 (mod 4) that have exponents `factors`
long long count(vector<int> factors, long long n=::n, int x=0) {
  if (factors.size() == 0) {
    return count_4k_3(n);
  }

  long long ret = 0;

  if (factors.size() == 1 && factors[0] == 1) {
    return count_one_4k_1(n, x);
  }

  int p = primes_4k_1[x];
  for (int i = 0; i < factors.size(); ++i) {
    long long tmpn = n;
    for (int j = 0; j < factors[i]; ++j) {
      tmpn /= p;
      if (tmpn == 0) return 0LL;
    }

    vector<int> nfactors;
    for (int j = 0; j < factors.size(); ++j) {
      if (i == j) continue;
      nfactors.push_back(factors[j]);
    }

    ret += count(nfactors, tmpn, x+1);
  }

  return ret + count(factors, n, x+1);
}

long long solve(long long n, int m) {
  compute_primes_mod_4(n);

  vector<int> factors;
  for (int i = 3; i <= m; ++i) if (is_prime[i] && m % i == 0) {
    factors.push_back(i - 1 >> 1);
    m /= i;
  }
  
  long long ret = count(factors);
  
  auto mul = [](int x, int y) { return (x*2 + 1) * (y*2 + 1) - 1 >> 1; };
  
  if (factors.size() == 2) ret += count({mul(factors[0], factors[1])});
  
  if (factors.size() == 3) {
    ret += count({mul(factors[0], factors[1]), factors[2]});
    ret += count({mul(factors[0], factors[2]), factors[1]});
    ret += count({mul(factors[1], factors[2]), factors[0]});
  }

  return ret;
}

int main() {
  generate_primes(N-1);
  int q;
  scanf("%d", &q);
  while (q--) {
    scanf("%lld %d", &n, &m);
    printf("%lld\n", solve(n, m));
  }
  return 0;
}
