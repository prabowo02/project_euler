#include <bits/stdc++.h>
using namespace std;

// floor(sqrt(n^2 - x^2))
int cs(int n, int x) {
  int y = sqrt(1LL*n*n - 1LL*x*x);
  while (1LL*x*x + 1LL*y*y < 1LL*n*n) ++y;
  return y;
}

long long T(int n) {
  if (n == 1) {
    return 1;
  }
  if (n == 3) {
    return 1;
  }
  if (n == 5) {
    return 3;
  }
  if (n % 2 == 1) {
    return 0;
  }
  long long ans = 0;

  // Count black of initial board, and toggle them
  int oddCount = 0;
  vector<bool> odd(n);
  for (int i = 0; i < n; ++i) {
    int l = cs(n - 1, i), r = cs(n, i);
    if (r - l & 1) {
      odd[i] = true;
      ++oddCount;
    }

    ans += r - l;
  }

  // Toggle all black again, and exclude those that have been toggled twice
  // At this point, (i, j) is black iff odd[i] "xor" odd[j] "xor" initially black
  for (int i = 0; i < n; ++i) {
    int l = cs(n - 1, i), r = cs(n, i);
    if (odd[i]) {
      ans += n - oddCount;
      for (int j = l; j < r; ++j) {
        if (!odd[j]) {
          ans -= 2;
        }
      }
    } else {
      ans += oddCount;
      for (int j = l; j < r; ++j) {
        if (odd[j]) {
          ans -= 2;
        }
      }
    }
  }

  fprintf(stderr, "T(%d) = %lld\n", n, ans);
  return ans;
}

int main() {
  long long ans = 0;
  for (int i = 3; i <= 31; ++i) {
    ans += T((1 << i) - i);
  }
  printf("%lld\n", ans);
  return 0;
}
