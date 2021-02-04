#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e16;

bool isPrime(int n) {
  for (int i = 2; i*i <= n; ++i) if (n % i == 0) return false;
  return true; 
}

int main() {
  int n;
  scanf("%d", &n);

  vector<int> primes;
  for (int i = 2; i < n; ++i) if (isPrime(i)) primes.push_back(i);

  double bound = 0;
  for (int p : primes) bound += log(p);
  bound /= 2;

  // mitm
  vector<pair<double, vector<int>>> sums;
  int mid = primes.size() / 2;
  for (int mask = 0; mask < 1 << mid; ++mask) {
    vector<int> factors;
    double sum = 0;
    for (int i = 0; i < mid; ++i) {
      if (mask >> i & 1) {
        factors.push_back(primes[i]);
        sum += log(primes[i]);
      }
    }
    sums.emplace_back(sum, factors);
  }
  sort(sums.begin(), sums.end());

  int mid2 = primes.size() - mid;
  double ans = 0; vector<int> factorAns;
  for (int mask = 0; mask < 1 << mid2; ++mask) {
    vector<int> factors;
    double sum = 0;
    for (int i = 0; i < mid2; ++i) {
      if (mask >> i & 1) {
        factors.push_back(primes[i + mid]);
        sum += log(primes[i + mid]);
      }
    }

    if (sum > bound) continue;
    int idx = upper_bound(sums.begin(), sums.end(), make_pair(bound - sum, vector<int>())) - sums.begin() - 1;
    if (sums[idx].first + sum > ans) {
      ans = sums[idx].first + sum;
      factorAns = sums[idx].second;
      for (int p : factors) factorAns.push_back(p);
    }
  }

  long long prod = 1;
  for (int f : factorAns) {
    prod = prod * f % MOD;
  }

  printf("%lld\n", prod);
  return 0;
}
