#include <bits/stdc++.h>
using namespace std;

const int S = 5;
const int N = 3000;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

bool vis[N][S][S][1 << S][1 << S][2];
double dp[N][S][S][1 << S][1 << S][2];
double f(int n, int x, int y, int upMask, int loMask, int carry) {
  if (upMask + 1 == 1 << S) return n == 0;
  if (n == 0) return 0;
  double &ret = dp[n][x][y][upMask][loMask][carry];
  if (vis[n][x][y][upMask][loMask][carry]) return ret;
  vis[n][x][y][upMask][loMask][carry] = true;

  vector<pair<int, int>> moves;
  for (int d = 0; d < 4; ++d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= S || ny < 0 || ny >= S) continue;
    moves.emplace_back(nx, ny);
  }

  ret = 0;
  for (auto [nx, ny] : moves) {
    int nupMask = upMask, nloMask = loMask, ncarry = carry;
    if (nx == S - 1 && carry == 0 && (loMask >> ny & 1) == 1) {
      nloMask ^= 1 << ny;
      ncarry ^= 1;
    }
    if (nx == 0 && carry == 1 && (upMask >> ny & 1) == 0) {
      nupMask ^= 1 << ny;
      ncarry ^= 1;
    }

    ret += 1.0 / moves.size() * f(n - 1, nx, ny, nupMask, nloMask, ncarry);
  }

  return ret;
}

void solve() {
  double ans = 0;
  for (int i = 1; i < N; ++i) {
    ans += i * f(i, S/2, S/2, 0, (1 << S) - 1, 0);
    // printf("%d %.012lf\n", i, ans);
  }
  printf("%.012lf\n", ans);
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
}
