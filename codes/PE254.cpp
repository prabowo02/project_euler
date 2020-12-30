// the value of f(g(n)) starting from n ≥ 64 has the form x999... (i.e. digit n%9 followed by n/9 digit 9)

#include <bits/stdc++.h>
using namespace std;

const int MOD = 362880;
const int MAXN = 155;
const int LEN = 18;

bool smaller(const vector<long long> &s, const vector<long long> &t) {
  long long len0 = 0, len1 = 0;
  for (int i = 0; i < 10; ++i) len0 += s[i], len1 += t[i];
  if (len0 != len1) return len0 < len1;
  for (int i = 0; i < 10; ++i) if (s[i] != t[i]) return s[i] > t[i];
  return false;
}

string g[MAXN];

int ten[LEN];
int dp[MAXN][LEN][MOD];
// determine the existance of f(n) such that
//   sum digit of f(n) is sum, length of f(n) is len, and f(n) % 9! is mod
int f(int sum, int len, int mod) {
  if (sum < 0) return false;
  if (len == 0) return sum == 0 && mod == 0;
  if (~dp[sum][len][mod]) return dp[sum][len][mod];

  bool ret = false;
  for (int d = 0; d < 10; ++d) {
    ret |= f(sum - d, len - 1, (mod + ten[len - 1] * d) % MOD);
  }
  return dp[sum][len][mod] = ret;
}

void init() {
  ten[0] = 1;
  for (int i = 1; i < LEN; ++i) ten[i] = 10LL * ten[i - 1] % MOD;
  memset(dp, -1, sizeof dp);
}

int main() {
  init();

  int N;
  scanf("%d", &N);

  long long sum = 0;
  for (int n = 1; n <= N; ++n) {
    vector<long long> ans;
    long long ansf = 0;

    for (int len = 1; len < LEN; ++len) {
      for (int mod = 0; mod < MOD; ++mod) {
        if (!f(n, len, mod)) continue;

        int sum = n, tmod = mod;
        long long num = 0;
        for (int i = len; i > 0; --i) {
          for (int d = 0; d < 10; ++d) {
            if (f(sum - d, i - 1, (tmod + ten[i - 1] * d) % MOD)) {
              sum -= d;
              tmod = (tmod + ten[i - 1] * d) % MOD;
              num = num * 10 + d;
              break;
            }
          }
        }
        assert(tmod == 0);

        long long tnum = num;

        int fact = MOD;
        vector<long long> digs(10);
        for (int i = 9; i > 0; --i) {
          digs[i] = num / fact;
          num %= fact;
          fact /= i;
        }

        if (ans.size() == 0 || smaller(digs, ans)) {
          ans = digs;
          ansf = tnum;
        }
      }
      // if (ans.size() > 0) break;
    }

    for (int d = 0; d < 10; ++d) sum += d * ans[d];

    cout << n << "\t\t" << ansf << "\t\t";
    if (n < 65) {
      for (int d = 0; d < 10; ++d) {
        for (int i = 0; i < ans[d]; ++i) cout << d;
      }
      cout << endl;
    } else {
      cout << endl;
    }
  }

  cout << sum << endl;
  return 0;
}
