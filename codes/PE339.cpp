#include <bits/stdc++.h>
using namespace std;

double simulate(int n) {
  // This is the "DP" when you have a certain number of black sheeps left
  vector<double> black(n*2 + 1);

  for (int k = 0; k <= n*2; ++k) {
    // k total sheeps
    vector<double> E(black.begin(), black.begin() + k + 1);
    for (int i = 0; i <= k; ++i) E[i] = i;
    double diff = 1;

    // After simulation, it seems that when i*2 <= k, you should drop your white sheep
    // Otherwise, continue the bleat process

    int it = 0;
    while (diff > 1e-8) {
      ++it;
      vector<double> nE = E;
      diff = 0;
      for (int i = 0; i < k; ++i) {
        // i black sheeps
        double t = 0;
        if (i > 0) t += (double) (k - i) / k * max(black[i - 1], E[i - 1]);
        if (i < k) t += (double) i / k * max(black[i + 1], E[i + 1]);
        nE[i] = t;

        diff += abs(nE[i] - E[i]);
      }
      swap(E, nE);
    }

    // cerr << k << ": " << it << endl;

    if (k == n*2) return E[n];

    for (int i = 0; i <= k; ++i) {
      // if (black[i] < E[i]) cerr << 0 << " ";
      // else cerr << 1 << " ";
      black[i] = max(black[i], E[i]);
      cerr << black[i] << " ";
    }
    cerr << endl;
  }

  return -1;
}


double solve(int n) {
  // This is the "DP" when you have a certain number of black sheeps left
  vector<double> black(n*2 + 1);

  for (int k = 0; k <= n*2; ++k) {
    // k total sheep

    vector<double> E(k + 1);
    vector<double> a(k + 1), b(k + 1); // E[x] = a[x] * E[x+1] + b[x]

    // E[i] = (k-i)/k E[i-1] + i/k E[i+1]
    // E[i] = (1 - i/k) (a[i-1] E[i] + b[i-1]) + i/k E[i+1]

    b[k/2] = black[k / 2];
    for (int i = k / 2 + 1; i < k; ++i) {
      double d = 1 - (1 - (double) i / k) * a[i - 1];
      a[i] = (double) i / k / d;
      b[i] = (double) (k - i) / k * b[i - 1] / d;
    }

    E[k] = k;
    black[k] = k;
    for (int i = k - 1; i > k / 2; --i) {
      E[i] = a[i] * E[i + 1] + b[i];
      black[i] = max(black[i], E[i]);
    }

    if (k == n*2) {
      return (double) n / k * (black[n - 1] + E[n + 1]);
    }
  }

  return -1;
}

int main() {
  // printf("%.6lf\n", simulate(5));
  printf("%.6lf\n", solve(5));
  printf("%.6lf\n", solve(100)); // 183.080665
  printf("%.6lf\n", solve(10000));
  return 0;
}
