// Generate all possible eulerian cycle of the de-brujin graph

#include <bits/stdc++.h>
using namespace std;

const int N = 5;

int n;

bool used[1 << (N - 1)][2];

void dfs(int u, int mask, vector<int> &path) {
  int v = (u & ~(1 << (n-2))) << 1;
  long long ret = 0;
  int bit = mask >> u & 1;

  if (!used[u][bit]) {
    used[u][bit] = 1;
    dfs(v | bit, mask, path);
  }

  bit ^= 1;

  if (!used[u][bit]) {
    used[u][bit] = 1;
    dfs(v | bit, mask, path);
  }

  path.push_back(u);
}

int main() {
  scanf("%d", &n);

  vector<int> ans;
  for (int mask = 0; mask < 1 << (1 << (n - 1)); ++mask) {
    vector<int> path;
    for (int i = 0; i < 1 << (n - 1); ++i) used[i][0] = used[i][1] = false;
    dfs(0, mask, path);
    reverse(path.begin(), path.end());

    int res = 0;
    for (int i = 1; i + n - 1 < path.size(); ++i) {
      res = (res << 1) + (path[i] & 1);
    }
    while ((res & 1) == 0) res >>= 1;
    ans.push_back(res);
  }

  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

  cerr << ans.size() << endl;
  long long sum = 0;
  for (int u : ans) {
    sum += u;
    // cerr << (bitset<32>(u)) << endl;
  }

  printf("%lld\n", sum);
  return 0;
}
