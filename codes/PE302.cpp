#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int biggestPrime[N];
vector<int> primes;
int order[N];

void init() {
  for (int i = 1; i < N; ++i) biggestPrime[i] = 1;
  for (int p = 2; p < N; ++p) {
    if (biggestPrime[p] != 1) continue;
    order[p] = primes.size();
    primes.push_back(p);

    for (int i = p; i < N; i += p) {
      biggestPrime[i] = p;
    }
  }
}

long long cnt;
int phiFact[N];

int exps[100];

void add(int n) {
  while (n > 1) {
    int p = biggestPrime[n];
    --exps[phiFact[order[p]]];
    ++exps[++phiFact[order[p]]];
    n /= p;
  }
}

void dec(int n) {
  while (n > 1) {
    int p = biggestPrime[n];
    --exps[phiFact[order[p]]--];
    ++exps[phiFact[order[p]]];
    n /= p;
  }
}

void dfs(long long n, int i, int g) {
  if (i < 0) {
    if (g != 1) return;
    if (exps[1] > 0) return;
    int gp = 0;
    for (int j = 2; j < 100; ++j) {
      if (exps[j] > 0) {
        gp = gcd(gp, j);
        if (gp == 1) {
          ++cnt;
          break;
        }
      }
    }
    return;
  }
  if (phiFact[i] != 1) {
    dfs(n, i - 1, g);
  }
  n /= primes[i]; n /= primes[i];
  int j = 0;
  add(primes[i] - 1);
  for (; n > 0; n /= primes[i]) {
    ++j; add(primes[i]);
    dfs(n, i - 1, gcd(g, j + 1));
  }
  while (j--) dec(primes[i]);
  dec(primes[i] - 1);
}

long long solve(long long N) {
  cnt = 0;
  for (int i = primes.size() - 1; i >= 0; --i) {
    long long p = primes[i];

    // Largest prime has exponent at least 3
    // Its p-1 factorisation must also be at least 2
    if (biggestPrime[p - 1] != biggestPrime[(p - 1) / biggestPrime[p - 1]] && 
          N / p / p / p / biggestPrime[p - 1] / biggestPrime[p - 1] > 0 ||
          biggestPrime[p - 1] == biggestPrime[(p - 1) / biggestPrime[p - 1]]) {
      add(p - 1);
      int j = 1; add(p);
      for (long long n = N / p / p / p; n > 0; n /= p) {
        ++j; add(p);
        dfs(n, i - 1, j + 1);
      }
      while (j--) dec(p);
      dec(p - 1);
    }
  }
  return cnt;
}

int main() {
  init();
  cout << solve(10000) << endl;
  cout << solve(100000000) << endl;
  cout << solve(1000000000000000000LL) << endl;

  return 0;
}
