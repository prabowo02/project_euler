// By Cayley-Hamilton Theorem, a matrix A^N (A has order k) can be written as the characteristic polynomial of A,
// i.e. A^N = c_{k-1} A^(N-1) + ... c_0 A^(N-k), c is the coefficients of the characteristic polynomial
// Therefore, the matrix A^N can be written as a matrix polynomial of degree k,
// i.e. A^N = a0 A^0 + ... + a_{k-1} A^{k-1}, for some coefficients a

// In the case for this problem, A^n = A^(n-1999) + A^(n-2000)

#include <bits/stdc++.h>
using namespace std;

const int MOD = 20092010;
const int K = 2000;

vector<int> multiply(vector<int> x, vector<int> y) {
  vector<int> ret(K * 2);
  for (int i = 0; i < x.size(); ++i) {
    for (int j = 0; j < y.size(); ++j) {
      ret[i + j] = (1LL * x[i] * y[j] + ret[i + j]) % MOD;
    }
  }

  for (int i = (int) ret.size() - 1; i >= K; --i) {
    ret[i - K] = (ret[i - K] + ret[i]) % MOD;
    ret[i - K + 1] = (ret[i - K + 1] + ret[i]) % MOD;
  }

  ret.resize(K);
  return ret;
}

vector<int> power(long long n) {
  vector<int> ret = {1}, a = {0, 1};
  for (; n; n >>= 1) {
    if (n & 1) ret = multiply(ret, a);
    a = multiply(a, a);
  }
  return ret;
}

int solve(long long n) {
  int ans = 0;
  for (int c : power(n)) {
    ans = (ans + c) % MOD;
  }
  return ans;
}

int brute(int n) {
  if (n < K) return 1;
  vector<int> g(K, 1);
  for (int i = K; i <= n; ++i) {
    g[i % K] = (g[i % K] + g[(i + 1) % K]) % MOD;
  }
  return g[n % K];
}

void test() {
  for (int n : {0, 1, 2, 1999, 2000, 2001, 2002, 10000, 20000, 100000, 200000}) {
    int ans = brute(n);
    cerr << n << ": " << ans << endl;
    assert(solve(n) == ans);
  }
}

int main() {
  // test();
  long long n = 1e18;
  // scanf("%lld", &n);

  printf("%d\n", solve(n));
  return 0;
}
