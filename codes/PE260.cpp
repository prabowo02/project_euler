// There are at most O(N^2) losing positions
//   proof. There are only O(7N^2) "lines", where each line can only contain at most one losing position
// For each of these losing positions, mark some positions as winning by adding stones

#include <bits/stdc++.h>
using namespace std;

const int N = 1001;

bool win[N][N][N];
void solution1(int n) {
  int ans = 0;
  for (int x = 0; x <= n; ++x) {
    for (int y = x; y <= n; ++y) {
      for (int z = y; z <= n; ++z) {
        if (win[x][y][z]) continue;

        for (int k = 1; k < y - x; ++k) win[x + k][y][z] = true;
        for (int k = max(1, y - x); k < z - x; ++k) win[y][x + k][z] = true;
        for (int k = max(1, z - x); k <= n - x; ++k) win[y][z][x + k] = true;
        for (int k = 1; k < z - y; ++k) win[x][y + k][z] = true;
        for (int k = max(1, z - y); k <= n - y; ++k) win[x][z][y + k] = true;
        for (int k = 1; k <= n - z; ++k) win[x][y][z + k] = true;

        for (int k = 1; k < z - y; ++k) win[x + k][y + k][z] = true;
        for (int k = max(1, z - y); k <= n - y; ++k) (x + k < z ? win[x + k][z][y + k] : win[z][x + k][y + k]) = true;
        for (int k = 1; k <= n - z; ++k) (x + k < y ? win[x + k][y][z + k] : win[y][x + k][z + k]) = true;
        for (int k = 1; k <= n - z; ++k) win[x][y + k][z + k] = true;

        for (int k = 1; k <= n - z; ++k) win[x + k][y + k][z + k] = true;

        ans += x + y + z;
      }
    }
  }
  printf("%d\n", ans);
}

// Memory optimized to O(N^2), if you store "lines" that have losing positions at the moment
bool one[N][N], two[N][N], three[N][N];
void solution2(int n) {
  int ans = 0;
  for (int x = 0; x <= n; ++x) {
    for (int y = x; y <= n; ++y) {
      for (int z = y; z <= n; ++z) {
        if (one[y][z] || one[x][z] || one[x][y]) continue;
        if (two[z][y - x] || two[y][z - x] || two[x][z - y]) continue;
        if (three[y - x][z - x]) continue;
        ans += x + y + z;
        one[y][z] = one[x][z] = one[x][y] = two[z][y - x] = two[y][z - x] = two[x][z - y] = three[y - x][z - x] = true;
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
  int n = 1000;
  scanf("%d", &n);
  solution2(n);
  return 0;
}
