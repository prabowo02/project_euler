#include <bits/stdc++.h>
using namespace std;

const int N = 2000000005;

bool isPrime[N];
int R[N];
void sieve() {
  memset(isPrime, true, sizeof isPrime);
  for (int i = 2; i < N; ++i) {
    if (!isPrime[i]) continue;
    for (int j = i*2; j < N; j += i) {
      isPrime[j] = false;
    }
  }

  for (int i = 1; i < N; ++i) {
    for (int j = i; j < N; j += i) {
      if (R[j] == -1 || R[j] >= j) continue;
      if (i > R[j] + 1) R[j] = -1;
      else R[j] += i;
    }
  }
}

inline bool practical(int n) {
  return R[n] >= n;
}

int main() {
  sieve();
  for (int n = 11; n + 9 < N; ++n) {
    if (isPrime[n - 9] && !isPrime[n - 7] && !isPrime[n - 5] && isPrime[n - 3] && !isPrime[n - 1] &&
        !isPrime[n + 1] && isPrime[n + 3] && !isPrime[n + 5] && !isPrime[n + 7] && isPrime[n + 9]) {
      if (practical(n - 8) && practical(n - 4) && practical(n) && practical(n + 4) && practical(n + 8)) {
        cout << n << endl;
      }
    }
  }

// ans:
// 219869980
// 312501820
// 360613700
// 1146521020

  return 0;
}
