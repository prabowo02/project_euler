// We use the gf: (1 + xq)(1 + xq^2) ... (1 + xq^n)
// The answer is the sum of all coefficient [x^k q^(r mod m)]
// Applying the cauchy's q-binomial theorem: the gf became sum_j x^j q^(j(j+1)/2) [n j]_q, 
//   where [n k]_q is the q-binomial coefficient
// Since we only care about coefficient x^k: we only need to find [q^(r mod m)] q^(k(k+1)/2) [n k]_q
//
// Applying series multisection, we now only need to find the sum:
//   1/m sum w^-jr w^(jk(k+1)/2) [n k]_{w^j}
// Applying q-lucas theorem, [n k]_w = C(n/d, k/d) [n%d k%d]_w, where w is d-th primitive root of unity
// Since n%d <= k%d (from the problem constraint), then [n%d k%d] = 1 if n%d = k%d, 0 otherwise
//
// The sum_{j=0}^m can be transformed into sum_{d|m} C(n/d, k/d) * {sum all d-th primitive root of unity power k(k+1)/2-r} 
// Sum of k-th power of all d-th primitive root of unity is mu(r)*phi(d)/phi(r), where mu is mobius function and r = d/gcd(n,d)
//
// Now the only problem is to compute binomial mod p^e
// The rough idea is to compute only n! without the i mod p parts, by expand it using stirling number
// Then the product of stirling number expansion is magically a polynom of degree 2e-2 (which I dont really understand why yet)
// Using these as references:
// - https://gist.github.com/min-25/a5496354e10064a581d6b0c52c727a26
// - https://min-25.hatenablog.com/entry/2017/11/01/185400

#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

const __int128 ONE = 1;

long long power(long long x, long long y, long long m) {
  long long ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = ONE * ret * x % m;
    x = ONE * x * x % m;
  }

  return ret;
}

vector<pair<long long, int>> factorize(long long n) {
  vector<pair<long long, int>> ret;

  int e = 0;
  while (n % 2 == 0) {
    n >>= 1;
    ++e;
  }
  if (e) ret.emplace_back(2, e);

  e = 0;
  while (n % 3 == 0) {
    n /= 3;
    ++e;
  }
  if (e) ret.emplace_back(3, e);

  for (long long i = 5; i*i <= n;) {
    e = 0;
    while (n % i == 0) {
      n /= i;
      ++e;
    }
    if (e) ret.emplace_back(i, e);

    i += 2;

    e = 0;
    while (n % i == 0) {
      n /= i;
      ++e;
    }
    if (e) ret.emplace_back(i, e);

    i += 4;
  }

  if (n > 1) ret.emplace_back(n, 1);

  return ret;
}

long long gcd(long long x, long long y) {
  long long tmp;
  while (y) {
    tmp = x;
    x = y;
    y = tmp % y;
  }

  return x;
}

struct Number {
  long long n;
  vector<pair<long long, int>> primeFactors;

  vector<long long> divisors;
  vector<long long> phi;
  vector<int> mobius;

  Number(long long _n): n(_n) {
    primeFactors = factorize(n);

    // divisors, phi, mobius
    vector<tuple<long long, long long, int>> res;
    res.emplace_back(1LL, 1LL, 1);
    for (pair<long long, int> pe: primeFactors) {
      long long p = pe.first;
      int e = pe.second;
      int sz = res.size();
      
      for (int i=0; i<sz; i++) {
        long long num = 1;
        for (int j=0; j<e; j++) {
          num *= p;
          res.emplace_back(
            get<0>(res[i]) * num,
            get<1>(res[i]) * num / p * (p-1),
            get<2>(res[i]) * (j == 0 ? -1 : 0)
          );
        }
      }
    }
  
    sort(res.begin(), res.end());

    divisors.resize(res.size());
    phi.resize(res.size());
    mobius.resize(res.size());
    for (int i = 0; i < res.size(); ++i) {
      tie(divisors[i], phi[i], mobius[i]) = res[i];
    }
  }

  // d must divides n
  int getDivisorIdx(long long d) {
    return lower_bound(divisors.begin(), divisors.end(), d) - divisors.begin();
  }
};

namespace BinomialWithoutMod {
  long long p = 1, pe = 1;
  int e = 0;

  long long pPower[64];

  // First kind
  long long stirling[300000];

  long long pstirling[64];

  long long fact[125], ifact[125];
  int pfact[125];

  long long lagrangeCoeff[125];

  long long prods[125];

  // Computes (np+1)(np+2) ... (np+m) % p^e
  // with m < p
  long long rising_factorial(long long n, long long m) {
    long long ret = 0;
    long long pn = 1;
    int ep = (e < p ? e : p);
    int idx = m*ep;
    for (int j = 0; j < ep; ++j) {
      ret = stirling[idx+j] * pn + ret;
      pn = pn * p * n; 
    }

    return ret;
  }

  // Compute inverse of n mod p^e
  // map<pair<long long, int>, long long> memoInv;
  inline long long inv(long long n) {
    // map<pair<long long, int>, long long>::iterator it = memoInv.find({n, i}); 
    // if (it != memoInv.end()) return it->second;
    long long ret = 1;
    for (int i = 1; i < e; ++i) {
      ret = ret * n;
      n = n * n;
    }

    return ret;
  }

  int pfactorsnum[125];
  long long prenum[125], sufnum[125];
  gp_hash_table<long long, long long> memoL;
  long long lagrangeInterpolate(long long ndp) {
    if (memoL.find(ndp) != memoL.end()) return memoL[ndp];

    int len = e*2 - 1;
    int ptot = 0;

    for (int i = 0; i < len; ++i) {
      long long num = ndp - i;
      pfactorsnum[i] = 0;
      while (num % p == 0) {
        num /= p;
        ++pfactorsnum[i];
      }
      ptot += pfactorsnum[i];
      prenum[i] = sufnum[i] = num;

      if (i > 0) prenum[i] = prenum[i-1] * prenum[i];
    }

    for (int i = len-2; i >= 0; --i) {
      sufnum[i] = sufnum[i] * sufnum[i+1];
    }

    long long sum = 0;
    for (int j = 0; j < len; ++j) {
      int j2 = len - 1 - j;
      int pfactor = ptot - pfactorsnum[j] - pfact[j] - pfact[j2];

      if (pfactor >= e) continue;

      long long numerator = (j > 0 ? prenum[j-1] : 1) * (j < len-1 ? sufnum[j+1] : 1);

      sum = numerator * lagrangeCoeff[j] * pPower[pfactor] + sum;
    }

    return memoL[ndp] = sum;
  }

  // n! / (p-1)!^{n/p} % p^e, but p, 2p, ... is not multiplied
  // unordered_map<long long, long long> memoF;
  long long factorial_without_p(long long n) {
    // unordered_map<long long, long long>::iterator it = memoF.find(n); 
    // if (it != memoF.end()) return it->second;

    long long ndp = n / p;
    long long ret = rising_factorial(ndp, n%p);

    if (ndp <= e*2 - 2) {
      return ret * prods[ndp];
      // return memoF[n] = (__int128) ret * prods[ndp] % pe;
    }

    ret = ret * lagrangeInterpolate(ndp);
    return ret;
  }

  // n! but without the p factors
  gp_hash_table<long long, long long> memoFa;
  long long factorial(long long n) {
    if (memoFa.find(n) != memoFa.end()) return memoFa[n];

    long long ret = 1;
    long long _n = n;

    while (n > 0) {
      ret = ret * factorial_without_p(n);
      n /= p;
    }

    return memoFa[_n] = ret;
  }

  // Legendre formula to compute p-adic valuation of n!
  gp_hash_table<long long, long long> memoLe;
  long long legendre(long long n) {
    if (memoLe.find(n) != memoLe.end()) return memoLe[n];

    long long ret = 0;
    long long _n = n;

    do {
      ret += n /= p;
    } while (n >= p);

    return memoLe[_n] = ret;
  }

  void setMod(long long _p, int _e) {
    memoL.clear(); memoFa.clear(); memoLe.clear();
    p = _p, e = _e;

    pe = 1;
    for (int i = 0; i < e; ++i) {
      pPower[i] = pe;
      pe *= p;
    }

    int ep = (e < p ? e : p);
    stirling[0] = 1;
    for (int i = 1; i < ep; ++i) stirling[i] = 0;
    for (int i = 1; i <= p; ++i) {
      int idx = i*ep;
      stirling[idx] = stirling[idx - ep] * i;
      for (int j = 1; j < ep; ++j) {
        stirling[idx + j] = i * stirling[idx-ep + j] + stirling[idx-ep + j-1];
      }
    }

    // prods.resize(e*2 - 1);
    long long prod = 1;
    long long invStirling = inv(stirling[(p-1)*ep]);

    for (int i = 0; i <= e*2 - 3; ++i) {
      prods[i] = prod;
      prod = prod * rising_factorial(i, p-1) % pe * invStirling;
    }
    prods[e*2 - 2] = prod;

    // pstirling.resize(e);
    pstirling[0] = 1;
    for (int i = 1; i < e; ++i) pstirling[i] = pstirling[i-1] * stirling[(p-1)*ep];

    int len = e*2 - 1;
    // fact.resize(len); ifact.resize(len); pfact.resize(len);
    fact[0] = 1LL; pfact[0] = 0;
    for (int i = 1; i < len; ++i) {
      long long num = i;
      pfact[i] = 0;
      while (num % p == 0) {
        ++pfact[i];
        num /= p;
      }

      ifact[i-1] = num;
      pfact[i] += pfact[i-1];
      fact[i] = fact[i-1] * num;
    }

    ifact[len-1] = inv(fact[len-1]);
    for (int i = len-2; i >= 0; --i) {
      ifact[i] = ifact[i+1] * ifact[i];
    }

    // lagrangeCoeff.resize(len);
    for (int i = 0; i < len; ++i) {
      long long denominator = ifact[i] * ifact[len-1 - i];
      if (len - 1 - i & 1) denominator = pe - denominator;

      lagrangeCoeff[i] = denominator * prods[i];
    }
  }

  long long binomial_coefficient(long long n, long long k) {
    long long binom_padic = legendre(n) - legendre(k) - legendre(n-k);
    if (binom_padic >= e) return 0LL;

    return pPower[binom_padic] * factorial(n)
        * inv(factorial(k) * factorial(n-k))
        * pstirling[binom_padic] % pe;
  }
}

namespace Binomial {
  long long p = 1, pe = 1;
  int e = 0;

  long long pPower[64];

  // First kind
  long long stirling[300000];

  long long pstirling[64];

  long long fact[125], ifact[125];
  int pfact[125];

  long long lagrangeCoeff[125];

  long long prods[125];

  // Computes (np+1)(np+2) ... (np+m) % p^e
  // with m < p
  long long rising_factorial(long long n, long long m) {
    long long ret = 0;
    long long pn = 1;
    int ep = (e < p ? e : p);
    int idx = m*ep;
    for (int j = 0; j < ep; ++j) {
      ret = (ONE * stirling[idx+j] * pn + ret) % pe;
      pn = ONE * pn * p * n % pe; 
    }

    return ret;
  }

  // Compute inverse of n mod p^e
  // map<pair<long long, int>, long long> memoInv;
  inline long long inv(long long n) {
    // map<pair<long long, int>, long long>::iterator it = memoInv.find({n, i}); 
    // if (it != memoInv.end()) return it->second;
    return power(n, pe / p * (p-1) - 1, pe);
    // return memoInv[{n, i}] = power(n, pe / p * (p-1) - 1, pe);
  }

  int pfactorsnum[125];
  long long prenum[125], sufnum[125];
  gp_hash_table<long long, long long> memoL;
  long long lagrangeInterpolate(long long ndp) {
    if (memoL.find(ndp) != memoL.end()) return memoL[ndp];

    int len = e*2 - 1;
    int ptot = 0;

    for (int i = 0; i < len; ++i) {
      long long num = ndp - i;
      pfactorsnum[i] = 0;
      while (num % p == 0) {
        num /= p;
        ++pfactorsnum[i];
      }
      ptot += pfactorsnum[i];
      prenum[i] = sufnum[i] = num;

      if (i > 0) prenum[i] = (__int128) prenum[i-1] * prenum[i] % pe;
    }

    for (int i = len-2; i >= 0; --i) {
      sufnum[i] = (__int128) sufnum[i] * sufnum[i+1] % pe;
    }

    long long sum = 0;
    for (int j = 0; j < len; ++j) {
      int j2 = len - 1 - j;
      int pfactor = ptot - pfactorsnum[j] - pfact[j] - pfact[j2];

      if (pfactor >= e) continue;

      long long numerator = (__int128) (j > 0 ? prenum[j-1] : 1) * (j < len-1 ? sufnum[j+1] : 1) % pe;

      sum = ((__int128) numerator * lagrangeCoeff[j] % pe * pPower[pfactor] + sum) % pe;
    }

    return memoL[ndp] = sum;
  }

  // n! / (p-1)!^{n/p} % p^e, but p, 2p, ... is not multiplied
  // unordered_map<long long, long long> memoF;
  long long factorial_without_p(long long n) {
    // unordered_map<long long, long long>::iterator it = memoF.find(n); 
    // if (it != memoF.end()) return it->second;

    long long ndp = n / p;
    long long ret = rising_factorial(ndp, n%p);

    if (ndp <= e*2 - 2) {
      return (__int128) ret * prods[ndp] % pe;
      // return memoF[n] = (__int128) ret * prods[ndp] % pe;
    }

    ret = (__int128) ret * lagrangeInterpolate(ndp) % pe;
    // return memoF[n] = ret;
    return ret;
  }

  // n! but without the p factors
  gp_hash_table<long long, long long> memoFa;
  long long factorial(long long n) {
    if (memoFa.find(n) != memoFa.end()) return memoFa[n];

    long long ret = 1;
    long long _n = n;

    while (n > 0) {
      ret = (__int128) ret * factorial_without_p(n) % pe;
      n /= p;
    }

    return memoFa[_n] = ret;
  }

  // Legendre formula to compute p-adic valuation of n!
  gp_hash_table<long long, long long> memoLe;
  long long legendre(long long n) {
    if (memoLe.find(n) != memoLe.end()) return memoLe[n];

    long long ret = 0;
    long long _n = n;

    do {
      ret += n /= p;
    } while (n >= p);

    return memoLe[_n] = ret;
  }

  void setMod(long long _p, int _e) {
    memoL.clear(); memoFa.clear(); memoLe.clear();
    p = _p, e = _e;

    // pPower.resize(e);
    pe = 1;
    for (int i = 0; i < e; ++i) {
      pPower[i] = pe;
      pe *= p;
    }

    int ep = (e < p ? e : p);
    // stirling = vector<vector<long long>>(p+1, vector<long long>(ep+1, 0));

    // stirling[0].resize(ep+1, 0);
    // stirling[0][0] = 1;
    stirling[0] = 1;
    for (int i = 1; i < ep; ++i) stirling[i] = 0;
    for (int i = 1; i <= p; ++i) {
      // stirling[i].resize(ep+1, 0);
      int idx = i*ep;
      stirling[idx] = ONE * stirling[idx - ep] * i % pe;
      for (int j = 1; j < ep; ++j) {
        // stirling[i][j] = (ONE * (i-1) * stirling[i-1][j] + stirling[i-1][j-1]) % pe;
        stirling[idx + j] = (ONE * i * stirling[idx-ep + j] + stirling[idx-ep + j-1]) % pe;
      }
    }

    // prods.resize(e*2 - 1);
    long long prod = 1;
    long long invStirling = inv(stirling[(p-1)*ep]);

    for (int i = 0; i <= e*2 - 3; ++i) {
      prods[i] = prod;
      prod = ONE * prod * rising_factorial(i, p-1) % pe * invStirling % pe;
    }
    prods[e*2 - 2] = prod;

    // pstirling.resize(e);
    pstirling[0] = 1;
    for (int i = 1; i < e; ++i) pstirling[i] = ONE * pstirling[i-1] * stirling[(p-1)*ep] % pe;

    int len = e*2 - 1;
    // fact.resize(len); ifact.resize(len); pfact.resize(len);
    fact[0] = 1LL; pfact[0] = 0;
    for (int i = 1; i < len; ++i) {
      long long num = i;
      pfact[i] = 0;
      while (num % p == 0) {
        ++pfact[i];
        num /= p;
      }

      ifact[i-1] = num;
      pfact[i] += pfact[i-1];
      fact[i] = ONE * fact[i-1] * num % pe;
    }

    ifact[len-1] = inv(fact[len-1]);
    for (int i = len-2; i >= 0; --i) {
      ifact[i] = ONE * ifact[i+1] * ifact[i] % pe;
    }

    // lagrangeCoeff.resize(len);
    for (int i = 0; i < len; ++i) {
      long long denominator = ONE * ifact[i] * ifact[len-1 - i] % pe;
      if (len - 1 - i & 1) denominator = pe - denominator;

      lagrangeCoeff[i] = ONE * denominator * prods[i] % pe;
    }
  }

  long long binomial_coefficient(long long n, long long k) {
    long long binom_padic = legendre(n) - legendre(k) - legendre(n-k);
    if (binom_padic >= e) return 0LL;

    return ONE * pPower[binom_padic] * factorial(n) % pe
        * inv(ONE * factorial(k) * factorial(n-k) % pe) % pe
        * pstirling[binom_padic] % pe;
  }
}

long long solve(long long m, long long r, long long n, long long k, long long M) {
  Number num(m);

  long long expo = (ONE * k * (k+1) / 2 - r) % m;
  if (expo < 0) expo += m;

  long long coeffs[num.divisors.size()];

  for (int i = 0; i < num.divisors.size(); ++i) {
    long long d = num.divisors[i];

    if (n % d < k % d) {
      coeffs[i] = 0;
      continue;
    }

    long long phiD = num.phi[i];

    int idx = num.getDivisorIdx(d / gcd(expo, d));
    // sum of e-th power of all primitive root mod d
    coeffs[i] = num.mobius[idx] * phiD / num.phi[idx];
  }

  vector<pair<long long, int>> primeFactors = factorize(M);

  long long ans = 0;
  for (const pair<long long, int> &pe: primeFactors) {
    if (pe.first == 2)
      BinomialWithoutMod::setMod(pe.first, pe.second);
    else 
      Binomial::setMod(pe.first, pe.second);

    long long sum = 0;
    for (int i = 0; i < num.divisors.size(); ++i) {
      if (coeffs[i] == 0) continue;
      long long d = num.divisors[i];

      if (pe.first == 2)
        sum = (ONE * coeffs[i] * BinomialWithoutMod::binomial_coefficient(n/d, k/d) + sum) % BinomialWithoutMod::pe;
      else
        sum = (ONE * coeffs[i] * Binomial::binomial_coefficient(n/d, k/d) + sum) % Binomial::pe;
    }

    if (pe.first == 2)
      ans = (ONE * M/BinomialWithoutMod::pe * power(M / BinomialWithoutMod::pe, BinomialWithoutMod::pe/2 - 1, BinomialWithoutMod::pe) % M * sum + ans) % M;
    else
      ans = (ONE * M/Binomial::pe * Binomial::inv(M/Binomial::pe) % M * sum + ans) % M;
  }

  if (ans < 0) ans += M;
  return ans;
}

int main() {
  long long m, r, n, k, M;
  scanf("%lld %lld %lld %lld %lld", &m, &r, &n, &k, &M);
  printf("%lld\n", solve(m, r, n, k, M));
  return 0;
}
