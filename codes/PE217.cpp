#include <bits/stdc++.h>
using namespace std;

const int MOD = 1004535809;

int B, L;
int d[10005];

int Bpower[10005];

// a1 + a2 + ... + a_len = sum; a1 in [l, r)
pair<int, int> getRange(int len, int sum, int l, int r);
pair<int, int> combine(pair<int, int> range1, pair<int, int> range2, bool odd, int len);

int **dp1, **dp2, **dp3;
int f(int x, int sum);
int g(int x, int sum);
int h(int x, int sum);

void read() {
  scanf("%d %d", &B, &L);
  for (int i=0; i<L; i++) {
    scanf("%d", d + i);
  }
}

void init_dp(int **&dp) {
  dp = new int*[L/2 + 1];
  
  for (int i=0; i<=L/2; i++) {
    int sum = (B-1) * (L/2) + 1;
    dp[i] = new int[sum];
    dp[i] = new int[sum];
    
    for (int j=0; j<sum; j++) {
      dp[i][j] = -1;
    }
  }
}

void init() {
  init_dp(dp1);
  init_dp(dp2);
  init_dp(dp3);
  
  Bpower[0] = 1;
  for (int i=1; i<=L; i++) {
    Bpower[i] = 1LL * Bpower[i-1] * B % MOD;
  }
}

int solve() {
  read();
  init();
  
  long long ans1 = 0, ans2 = 0;
  int sum = 0, num = 0;
  pair<int, int> term;
  for (int i=0; i<L; i++) {
    if (i < L/2) {
      for (int j=0; j<=(B-1)*(L/2); j++) {
        term = combine(getRange(L/2-i, j-sum, (i==0), d[i]), {f(L/2, j) - f(L/2, j-1), h(L/2, j) - h(L/2, j-1)}, L & 1, L/2);
        ans1 += term.first;
        ans2 += term.second + 1LL * term.first * num % MOD;
      }
      
      sum += d[i];
    } else if (i*2 + 1 == L) {
      term = combine({d[i] - (i == 0), d[i] * (d[i] - 1) / 2}, {f(L/2, sum) - f(L/2, sum-1), h(L/2, sum) - h(L/2, sum-1)}, false, L/2);
      ans1 += term.first;
      ans2 += term.second + 1LL * term.first * num % MOD;
    } else {
      term = getRange(L-i, sum, 0, d[i]);
      ans1 += term.first;
      ans2 += term.second + 1LL * term.first * num % MOD;
      
      sum -= d[i];
    }
    num = (1LL * d[i] * Bpower[L-i-1] + num) % MOD;
  }
  
  if (sum == 0) {
    ++ans1;
    ans2 += num;
  }
  
  for (int i=1; i<L-1; i++) {
    int len = L - i >> 1;
    for (int j=0; j<=(B-1)*len; j++) {
      term = combine(getRange(len, j, 1, B), {f(len, j) - f(len, j-1), h(len, j) - h(len, j-1)}, L-i & 1, len);
      ans1 += term.first;
      ans2 += term.second;
    }
  }
  
  if (L > 1) {
    ans1 += B-1;
    ans2 += B * (B-1) / 2;
  }
  
  ans1 %= MOD; ans2 %= MOD;
  if (ans1 < 0) ans1 += MOD;
  if (ans2 < 0) ans2 += MOD;
  
  printf("%lld %lld\n", ans1, ans2);  
  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}

pair<int, int> getRange(int len, int sum, int l, int r) {
  int count0 = f(len-1, sum-l) - f(len-1, sum-r);
  int count1 = (1LL * sum * count0 + (g(len-1, sum-l) - g(len-1, sum-r))) % MOD;
  count1 = (1LL * count1 * Bpower[len-1] + (h(len-1, sum-l) - h(len-1, sum-r))) % MOD;
  
  return {count0, count1};
}

pair<int, int> combine(pair<int, int> range1, pair<int, int> range2, bool odd, int len) {
  pair<int, int> ret = {
    1LL * range1.first * range2.first % MOD,
    (1LL * range1.first * range2.second + 1LL * range1.second * range2.first % MOD * Bpower[len + (odd ? 1 : 0)]) % MOD
  };
  
  if (odd) {
    ret.second = (1LL * ret.second * B + 1LL * (B * (B-1) / 2) * Bpower[len] % MOD * ret.first) % MOD;
    ret.first = 1LL * ret.first * B % MOD;
  }
  
  return ret;
}

int f(int x, int sum) {
  if (sum < 0) return 0;
  if (x == 0) return 1;
  if (~dp1[x][sum]) return dp1[x][sum];
  
  int ret = f(x-1, sum) - f(x-1, sum - B);
  ret += f(x, sum-1);
  
  if (ret < 0) ret += MOD;
  else if (ret >= MOD) ret -= MOD;
  
  return dp1[x][sum] = ret;
}

int g(int x, int sum) {
  if (sum < 0) return 0;
  if (x == 0) return 0;
  if (~dp2[x][sum]) return dp2[x][sum];
  
  int ret = 1LL * -sum * (f(x, sum) - f(x, sum-1)) % MOD;
  ret += g(x, sum-1);
  
  if (ret < 0) ret += MOD;
  else if (ret >= MOD) ret -= MOD;
  
  return dp2[x][sum] = ret;
}

int h(int x, int sum) {
  if (sum < 0) return 0;
  if (x == 0) return 0;
  if (~dp3[x][sum]) return dp3[x][sum];
  
  int ret = getRange(x, sum, 0, B).second;
  ret += h(x, sum-1);
  
  if (ret < 0) ret += MOD;
  else if (ret >= MOD) ret -= MOD;
  
  return dp3[x][sum] = ret;
}
