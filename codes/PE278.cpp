#include <bits/stdc++.h>
using namespace std;

void solve(int n) {
  vector<bool> isPrime(n, true);
  vector<int> primes;

  for (int p = 2; p < n; ++p) {
    if (!isPrime[p]) continue;
    primes.push_back(p);
    for (int i = p * 2; i < n; i += p) {
      isPrime[i] = false;
    }
  }

  long long ans = 0;
  for (int i = 0; i < primes.size(); ++i) {
    for (int j = i + 1; j < primes.size(); ++j) {
      for (int k = j + 1; k < primes.size(); ++k) {
        int p = primes[i], q = primes[j], r = primes[k];
        // IMO 1983 P3; A specific case of Frobenius problem
        ans += 2LL * p * q * r - p * q - p * r - q * r;
      }
    }
  }

  cout << ans << endl;
}

int main() {
  int n;
  cin >> n;
  clock_t t = clock();
  solve(n);
  cout << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
