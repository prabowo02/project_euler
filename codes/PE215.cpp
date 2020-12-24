#include <bits/stdc++.h>
using namespace std;

int w, h, mod;

int n, m;
int U[6000000];
int V[6000000];

int node[6000000];

void f(int x, int y, int st1, int st2) {
  if (x > w || y > w) return;
  if (x == w) {
    if (w - y == 2 || w - y == 3) {
      U[m] = st1; V[m] = st2;
      m++;
      node[n++] = st2;
    }
    return;
  }
  if (y == w) {
    if (w - x == 2 || w - x == 3) {
      U[m] = st1; V[m] = st2;
      m++;
      node[n++] = st2;
    }
    return;
  }
  
  if (x < y) {
    if (x + 2 != y) f(x+2, y, st1 << 1, st2);
    if (x + 3 != y) f(x+3, y, st1 << 1 | 1, st2);
  } else {
    if (y + 2 != x) f(x, y+2, st1, st2 << 1);
    if (y + 3 != x) f(x, y+3, st1, st2 << 1 | 1);
  }
}

long long dp[2][1000000];

int solve() {
  scanf("%d %d %d", &w, &h, &mod);
  // w = 45; h = 100; mod = 1000;
  f(0, 0, 1, 1);
  cerr << n << endl;
  
  sort(node, node + n);
  n = unique(node, node + n) - node;
  
  for (int i=0; i<m; i++) {
    U[i] = lower_bound(node, node + n, U[i]) - node;
    V[i] = lower_bound(node, node + n, V[i]) - node;
  }
  
  for (int i=0; i<n; i++) dp[0][i] = 1;
  
  for (int i=0; i<h/2; i++) {
    int cur = i & 1;
    int nxt = cur ^ 1;
    
    for (int j=0; j<n; j++) dp[nxt][j] = 0;
    for (int j=0; j<m; j++) {
      dp[nxt][V[j]] += dp[cur][U[j]];
    }
    for (int j=0; j<n; j++) dp[nxt][j] %= mod;
  }
  
  int lo = h / 2 & 1;
  int hi = (h - 1) / 2 & 1;
  
  long long ans = 0;
  for (int i=0; i<n; i++) ans = (ans + dp[lo][i] * dp[hi][i]) % mod;
  printf("%lld\n", ans % mod);
  
  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
