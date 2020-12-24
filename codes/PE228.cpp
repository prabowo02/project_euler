/**
  The minkowski addition of two convex polygon is a convex polygon,
  where the resulting edges are simply merging the edges of the original two polygons.
  
  Abridged problem statement: Given L and R, find the number of distinct values of x/y, where 0 <= x < y and L <= y <= R.
  
  We first define a totient sum function as Phi(n) = phi(1) + phi(2) + ... + phi(n).
  This can be computed using sqrt decomposition
  The idea is by considering all pairs N * (N+1) / 2 pairs of (x, y) where x <= y,
  then exclude all the pairs with gcd(x, y) > 1.
  
  For gcd < sqrt(n), manually subtract n*(n+1)/2 - Phi(n/2) - Phi(n/3) - ...
  For gcd > sqrt(n), subtract Phi(n/d) * (n/d - n/(d+1)) where d > sqrt(n)
  All divisions are integer divisions.
  
  This has complexity O(N^(3/4)). To further increase the speed, 
  we precompute Phi(n) for n < N^(2/3) using sieve, increasing the total complexity to (N^(2/3))
  
  Back to the original problem, we consider all fractions x/y along with their multiplicities.
  Suppose d = gcd(x, y). Notice that if y/d * (d+1) <= R, then x/y is double counted.
  Therefore, for all y <= R/(d+1) * d, the pairs (x, y) are double counted. The number of such value is Phi(R/(d+1))
  Be careful with the bound L, we actually need to subtract by Phi(max((L-1)/d, R/(d+1)))
  
  For d < sqrt(R), we add these Phi(R/(d+1)) iteratively,
  When d > sqrt(R), there are lot of duplicate values of R/(d+1), and similarly to computing the Phi function above, we add
  R/(d+1) * {its multiplicity}
  The rest is about handling the bound L carefully.
  
  Also, the code is heavily optimized, which may make it look a bit hard to read
*/

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
typedef long long Int;
#else
typedef __int128 Int;
#endif

const Int ONE = 1;
const int N = 10000000;

#ifndef LOCAL
ostream& operator << (std::ostream& os, Int t) {
  vector<int> v;
  while (t > 0) {
    v.push_back(t % 10);
    t /= 10;
  }
  
  while (v.size()) {
    os << v.back();
    v.pop_back();
  }
  
  return os;
}
#endif

unordered_map<long long, Int> memo3;
long long memo2[N];

int primes[N/10], st[N/10];
// Precompute totient sum for small n using segmented sieve
void precomp_totient() {
  memo2[1] = 1;
  memo2[2] = 1;
  
  int sz = 0;
  const int SEG = 200000;
  for (int lo=3; lo<N; lo+=SEG) {
    int hi = min(N, lo + SEG);

    for (int i=lo; i<hi; i++) memo2[i] = i / (2 - (i & 1));
    
    for (int i=0; i<sz; i++) {
      int p = primes[i];
      int j = st[i];
      for (; j<hi; j+=p) memo2[j] = memo2[j] / p * (p-1);
      st[i] = j;
    }
    
    for (int i=lo; i<hi; i+=2) {
      if (memo2[i] == i) {
        int p = primes[sz] = i;
        int j = st[sz] = i;
        
        for (; j<hi; j+=p) memo2[j] = memo2[j] / p * (p-1);
        
        st[sz++] = j;
      }      
      memo2[i] += memo2[i-1] += memo2[i-2];
    }
  }

  /*
  for (int i=3; i<N; i+=2) {
    if (memo2[i] == i) {
      for (int j=i; j<N; j+=i) memo2[j] = memo2[j] / i * (i-1);
    }
    
    memo2[i] += memo2[i-1] += memo2[i-2];
  }
  */
}

// Precompute the totient sum of n/1, n/2, ..., n/i where n/i >= N
// memo[i] will store the totient sum of n/i
void precompute_sum(Int memo[], long long n) {
  int lim = n/N;
  
  long long d, nn;
  Int res;
  
  for (int i=lim; i>=1; --i) {
    nn = n / i;
    if (memo3.find(nn) != memo3.end()) {
      memo[i] = memo3[nn];
      continue;
    }
    
    res = ONE * nn * (nn+1) >> 1;
    
    for (d = 2; d*d < nn; ++d) {
      res -= (d*i > lim ? memo2[nn/d] : memo[d*i]);
    }
    
    for (long long i=nn/d; i>=1; --i) {
      res -= memo2[i] * (nn/i - nn/(i+1));
    }
    
    memo3[nn] = memo[i] = res;
  }
}


Int memoL[100000], memoR[100000];
Int solve(long long L, long long R) {
  Int ret = ONE * R * (R+1) >> 1;

  precompute_sum(memoL, L-1);
  precompute_sum(memoR, R);
  
  int sr = sqrt(R);
  
  long long d, l, r;
  for (d=1; d < sr; ++d) {
    // x/d * (d+1) > R
    // x/d > R/(d+1)
    // x > R/(d+1) * d

    // x = max(L-1, R/(d+1) * d)
    // x/d = max((L-1)/d, R/(d+1))
    
    l = (L-1)/d, r = R/(d+1);
    
    if (l < r) ret -= (r < N ? memo2[r] : memoR[d+1]);
    else ret -= (l < N ? memo2[l] : memoL[d]);
    // ret -= sum_of_totient(max((L-1)/d, R/(d+1)));
  }

  long long nd;
  for (; d < R; d = nd) {
    l = (L-1)/d;
    r = R/(d+1);
    nd = min(R/r, (l > 0 ? (L-1)/l : R) + 1);

    ret -= memo2[max(l, r)] * (nd - d);
  }
  
  return ret;
}

void run() {
  int q;
  scanf("%d", &q);
  while (q--) {
    long long l, r;
    scanf("%lld %lld", &l, &r);
    cout << solve(l, r) << '\n';
  }
}

void test1() {
  int q = 10000;
  long long l, r = l = 4e6;
  while (q--) solve(l, r);
}

int main() {
  clock_t t = clock();
  
  precomp_totient();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  
  // cerr << solve(1864, 1909) << endl;
  // cerr << solve(500, 1000) << endl;
  // cerr << solve(20000000000LL, 40000000000LL) << endl;
  // cerr << solve(40000000000LL, 40000000000LL) << endl;
  
  run();
  
  // test1();
  
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
