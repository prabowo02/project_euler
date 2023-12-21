#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

vector<vector<bool>> grid;
vector<vector<bool>> isFilled;
vector<pair<int, int>> polyominoes;
vector<pair<int, int>> neighbours;
int cnt = 0;
int gen(int k) {
  int n = grid.size();
  // cerr << k << " " << polyominoes.size() << endl;
  if (polyominoes.size() == n) {
    // for (int i = 0; i < n; ++i) {
    //   for (int j = 0; j < n; ++j) {
    //     if (isFilled[i][j]) cout << "#";
    //     else cout << ".";
    //   }
    //   cout << endl;
    // }
    // cout << endl;
    int w = 0;
    bool is_mirror = true;
    for (auto [x, y] : polyominoes) {
      w += x - n / 2;
      if (!isFilled[2 * (n / 2) - x][y]) is_mirror = false;
    }
    if (w == 0) return is_mirror ? 2 : 1;
    return 0;
  }

  if (k >= neighbours.size()) return 0;

  int ret = gen(k + 1);

  int x, y;
  tie(x, y) = neighbours[k];

  polyominoes.emplace_back(x, y);
  isFilled[x][y] = true;

  vector<pair<int, int>> neighs;
  for (int j = 0; j < 4; ++j) {
    int nx = x + dx[j], ny = y + dy[j];
    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
    if (grid[nx][ny]) continue;

    neighs.emplace_back(nx, ny);
    grid[nx][ny] = true;
    neighbours.emplace_back(nx, ny);
  }

  ret += gen(k + 1);

  for (auto [nx, ny] : neighs) {
    neighbours.pop_back();
    grid[nx][ny] = false;
  }
  isFilled[x][y] = false;
  polyominoes.pop_back();

  return ret;
}

int solve(int n) {
  grid.assign(n, vector<bool>(n, false));
  isFilled.assign(n + 1, vector<bool>(n + 1, false));
  neighbours = {{n/2, 0}};
  grid[n/2][0] = true;
  polyominoes.clear();
  return gen(0) / 2;
}

int main() {
  int n;
  cin >> n;
  clock_t t = clock();
  cout << solve(n) << endl;
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  // N = 18: ~10 mins
  // N = 15: ~8s
  return 0;
}
