// (1 +/- f)^1000
// - find minimum + to s.t. can exceed 1e9
// - find the probs s.t. at least that number of + occur

// (1 + f*2)^a (1 - f)^b ≥ 1e9
// 2a(1 - f) - b(1 + 2f) = 0
// 2a - 2af - b - 2bf = 0
// 2a - b = (2a + 2b) f
// f = (2a - b) / (2a + 2b)

#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

double dp[N][N];
double dfs(int x, int y) {
  if (y == 0) return 1;
  if (x == 0) return 0;
  if (dp[x][y] > -0.5) return dp[x][y];
  return dp[x][y] = dfs(x - 1, y) * 0.5 + dfs(x - 1, y - 1) * 0.5;
}

int main() {
  int flip = 1000, goal = 1e9;
  // scanf("%d %d", &flip, &goal);

  int least = -1;
  for (int i = (flip + 2) / 3; i <= flip; ++i) {
    double f = (double) (i*3 - flip) / (flip * 2);
    if (pow(1 + f*2, i) * pow(1 - f, flip - i) > goal) {
      least = i;
      break;
    }
  }

  cerr << least << " " << (double) (least*3 - flip) / (flip * 2) << endl;

  for (int i = 0; i <= flip; ++i) for (int j = 0; j <= flip; ++j) dp[i][j] = -1;

  printf("%.12lf\n", dfs(flip, least));
  return 0;
}
