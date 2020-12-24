#include <bits/stdc++.h>
using namespace std;

int n;
int a[5], b[5];

int totalA, totalB;
int spoiledA[5], spoiledB[5];
int spoiledTotalA, spoiledTotalB;

void simplify(int &x, int &y) {
  int d = __gcd(x, y);
  x /= d, y /= d;
}

bool check() {
  set<pair<int, int>> s;
  s.insert(make_pair(0, 0));

  for (int i = 0; i < n; ++i) {
    int t = min(a[i] / spoiledA[i], b[i] / spoiledB[i]);

    vector<pair<int, int>> v;
    for (int j = 1; j <= t; ++j) {
      for (const pair<int, int> &p: s) {
        v.emplace_back(p.first + spoiledA[i]*j, p.second + spoiledB[i]*j);
      }
    }

    for (const pair<int, int> &p: v) s.insert(p);
  }

  for (int i = 1; spoiledTotalA*i <= totalA && spoiledTotalB*i <= totalB; ++i) {
    if (s.find({spoiledTotalA*i, spoiledTotalB*i}) != s.end()) {
      return true;
    } 
  }

  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
    totalA += a[i];
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", b + i);
    totalB += b[i];
  }

  for (spoiledA[0] = 1; spoiledA[0] < a[0]; ++spoiledA[0]) {
    for (spoiledB[0] = 1; spoiledB[0] <= b[0]; ++spoiledB[0]) {
      if (__gcd(spoiledA[0], spoiledB[0]) != 1) continue;
      int u = spoiledB[0] * a[0];
      int v = spoiledA[0] * b[0];

      if (u <= v) continue;

      simplify(u, v);

      bool can = true;
      for (int i = 1; i < n; ++i) {
        spoiledB[i] = b[i] * u;
        spoiledA[i] = a[i] * v;

        simplify(spoiledA[i], spoiledB[i]);

        if (spoiledA[i] > a[i] || spoiledB[i] > b[i]) {
          can = false;
          break;
        }
      }

      spoiledTotalA = totalA * u;
      spoiledTotalB = totalB * v;

      simplify(spoiledTotalA, spoiledTotalB);

      if (can && spoiledTotalA <= totalA && spoiledTotalB <= totalB) {
        if (check()) return 0 * printf("%d/%d\n", u, v);
      }
    }
  }
  return 0;
}
