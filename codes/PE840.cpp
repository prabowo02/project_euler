#include <bits/stdc++.h>
using namespace std;

const int MOD = 999676999;
int inv(int n) {
  int ret = 1;
  for (int y = MOD - 2; y > 0; y >>= 1) {
    if (y & 1) ret = 1LL * ret * n % MOD;
    n = 1LL * n * n % MOD;
  }
  return ret;
}

int D(int n) {
  if (n == 1) return 1;
  int ans = n;
  long long sum = 0;
  for (int p = 2; p*p <= n; ++p) {
    while (n % p == 0) {
      sum += inv(p);
      n /= p;
    }
  }
  if (n > 1) sum += inv(n);
  return 1LL * ans * sum % MOD;
}

vector<int> operator * (const vector<int> &a, const vector<int> &b) {
  vector<int> res(a.size() + b.size() - 1);
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
    }
  }
  return res;
}

vector<int> inverse(int n, vector<int> a) {
  a.resize(n*2);
  vector<int> res = {inv(a[0])};
  for (int len = 2; len < n<<1; len <<= 1) {
    vector<int> tmp = res * res * vector<int>(a.begin(), a.begin() + len);
    res.resize(len);
    for (int i = 0; i < len; ++i) res[i] = (2LL * res[i] - tmp[i] + MOD) % MOD;
  }
  res.resize(n);
  return res;
}

int main() {
  int N;
  scanf("%d", &N);
  vector<int> Ds(N + 1);
  for (int i = 1; i <= N; ++i) {
    Ds[i] = D(i);
  }

  vector<int> G(N + 1);
  G[0] = 1;
  for (int n = 1; n <= N; ++n) {
    for (int i = N; i >= n; --i) {
      G[i] = (G[i] - 1LL * Ds[n] * G[i - n]) % MOD;
      if (G[i] < 0) G[i] += MOD;
    }
  }
  G = inverse(N + 1, G);

  int ans = 0;
  for (int n = 1; n <= N; ++n) {
    ans = (ans + G[n]) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}
