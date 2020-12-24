#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

struct Matrix {
  vector<vector<int>> v;
  
  Matrix(int n, int val=0) {
    v = vector<vector<int>>(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) v[i][i] = val;
  }

  Matrix operator * (Matrix &other) {
    int n = v.size();

    Matrix ret(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        __int128 sum = 0;
        for (int k = 0; k < n; ++k) {
          sum += 1LL * v[i][k] * other[k][j];
        }
        ret[i][j] = sum % MOD;
      }
    }

    return ret;
  }

  vector<int>& operator [] (int row) {
    return v[row];
  }

  void print() {
    int n = v.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) cerr << v[i][j] << " ";
      cerr << endl;
    }
  }
};

Matrix power(Matrix A, long long y) {
  Matrix ret(A[0].size(), 1);

  for (; y; y >>= 1) {
    if (y & 1) ret = ret * A;
    A = A * A;
  }

  return ret;
}

struct DSU {
  vector<int> par;

  DSU(int n) {
    par = vector<int>(n+1);
    for (int i = 1; i <= n; ++i) par[i] = i;
  }

  int root(int u) {
    if (u == par[u]) return u;
    return par[u] = root(par[u]);
  }

  bool combine(int u, int v) {
    if (root(u) == root(v)) return false;
    par[root(u)] = root(v);
    return true;
  }
};

vector<vector<int>> neighbours(const vector<int> &group) {
  int n = group.size();

  vector<vector<int>> ret;

  // mask == 0
  {
    DSU dsu(n);
    bool can = true;
    int carry = 0;
    for (int i = 0; i < n; ++i) {
      if (group[i] == 0) {
        if (carry == 0) {
          can = false;
          break;
        }
      } else {
        if (carry == 0) carry = group[i];
        else dsu.combine(carry, group[i]), carry = 0;
      }
    }

    if (carry != 0) can = false;

    int root = 0;
    for (int i = 0; i < n; ++i) {
      if (group[i] == 0) continue;

      if (root != 0 && root != dsu.root(group[i])) {
        can = false;
        break;
      }

      root = dsu.root(group[i]);
    }

    if (can) ret.push_back(vector<int>(n, 0));
  }

  for (int nmask = 1; nmask < 1 << n; ++nmask) {
    vector<int> ngroup;
    int carry = 0;
    bool can = true;

    DSU dsu(n);
    int newgroupnum = n + 1;

    for (int i = 0; i < n; ++i) {
      int bit = nmask >> i & 1;

      if (carry == 0) {
        if (bit == 0 && group[i] == 0) {
          can = false;
          break;
        }

        if (bit > 0 && group[i] > 0) {
          ngroup.push_back(group[i]);
          continue;
        }

        ngroup.push_back(0);
        if (bit > 0) {
          carry = -i - 1;
        } else {
          carry = group[i];
        }

      } else {
        if (bit > 0 && group[i] > 0) {
          can = false;
          break;
        }

        if (bit == 0 && group[i] == 0) {
          ngroup.push_back(0);
          continue;
        }

        ngroup.push_back(0);
        if (bit > 0) {
          if (carry > 0) ngroup.back() = carry;
          else ngroup[-carry - 1] = ngroup.back() = newgroupnum++;
        } else {
          if (carry > 0) {
            if (!dsu.combine(carry, group[i])) {
              can = false;
              break;
            }
          } else {
            ngroup[-carry - 1] = group[i];
          }
        }

        carry = 0;
      }
    }

    if (carry != 0) can = false;

    if (!can) continue;

    for (int &u: ngroup) {
      if (1 <= u && u <= n) u = dsu.root(u);
    }

    // renumber
    map<int, int> seen;
    for (int &u: ngroup) {
      if (u == 0) continue;
      if (seen.find(u) != seen.end()) u = seen[u];
      else u = seen[u] = seen.size() + 1;
    }

    ret.push_back(ngroup);
  }

  return ret;
}

vector<vector<int>> bfs(int n) {
  map<vector<int>, int> vis;
  vis[vector<int>(n, 0)] = 0;

  vector<int> st(n, 0);
  st[0] = st.back() = 1;
  vis[st] = 1;

  vector<vector<int>> adjs(1);

  queue<vector<int>> q;
  q.push(st);
  while (q.size()) {
    vector<int> u = q.front();
    q.pop();

    vector<vector<int>> vs = neighbours(u);
    for (vector<int> v: vs) {
      if (vis.find(v) != vis.end()) continue;
      vis[v] = vis.size();
      q.push(v);
    }

    adjs.push_back(vector<int>());
    for (vector<int> v: vs) {
      adjs.back().push_back(vis[v]);
    }
  }

  return adjs;
}

Matrix init_matrix(const vector<vector<int>> adjs) {
  Matrix A(adjs.size());
  for (int i = 1; i < adjs.size(); ++i) {
    for (int v: adjs[i]) {
      A[v][i] = 1;
    }
  }

  A[0][0] = 1;
  return A;
}

int solve(long long n, int m) {
  vector<vector<int>> adjs = bfs(m);
  return power(init_matrix(adjs), n)[0][1];
}

int main() {
  long long n; int m;
  scanf("%d %lld", &m, &n);
  printf("%d\n", solve(n, m));
  return 0;
}
