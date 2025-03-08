// We can see that AB^2 + AD^2 = BC^2 + CD^2 = (BO - AO)^2 + (BO + AO)^2
// Since AO has to be integer, it follows that the sum of two squares above has to be even.
// It also follows that BO has to be integer too.
// We can also see that BO - AO < AB and AD < BO + AO
// So the problem boils down to: for each s, find number of sum of two squares of s,
//   then C(s, 3) will contribute to the answer

#include <bits/stdc++.h>
using namespace std;

const int BATCH = 1000000;
const int MAXN = 100005;

bool primes[MAXN];
long long cnt[BATCH];
long long num[BATCH];

vector<int> oddPrimes;
void genPrimes() {
  for (int i = 3; i < MAXN; i += 2) primes[i] = true;
  for (int p = 3; p < MAXN; ++p) {
    if (!primes[p]) {
      continue;
    }
    oddPrimes.push_back(p);
    for (int i = p * 2; i < MAXN; i += p) {
      primes[i] = false;
    }
  }
}

long long getSolveRange(long long l, long long r) {
  if (l == 0) l = 1;

  int plen = ceil(sqrt(r));
  for (int i = 0; i < r - l; ++i) {
    cnt[i] = 1;
    num[i] = i + l;
  }

  for (int p : oddPrimes) {
    if (p >= plen) break;
    for (int i = (l % p == 0 ? 0 : p - l % p); i < r - l; i += p) {
      int e = 0;
      while (num[i] % p == 0) {
        ++e;
        num[i] /= p;
      }

      if (p % 4 == 3 && e % 2 == 1) {
        cnt[i] = 0;
      } else if (p % 4 == 1) {
        cnt[i] *= e + 1;
      }
    }
  }

  long long ret = 0;
  for (int i = l % 2; i < r - l; i += 2) {
    int e2 = __builtin_ctzll(i + l);
    num[i] >>= e2;

    if (num[i] != 1) {
      if (num[i] % 4 == 3) {
        cnt[i] = 0;
      } else {
        cnt[i] *= 2;
      }
    }

    if (cnt[i] % 2 == 1) {
      if (e2 % 2 == 0) {
        // We need to count sum of the form 0 + x^2 (but exclude x^2 + x^2)
        ++cnt[i];
      } else {
        --cnt[i];
      }
    }

    cnt[i] /= 2;

    ret += cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / 6;
  }
  return ret;
}

long long solve(long long n) {
  genPrimes();
  long long ret = 0;
  for (long long i = 0; i <= n / 2; i += BATCH) {
    // cerr << "get " << i << " - " << i + BATCH << endl;
    ret += getSolveRange(i, min(i + BATCH, n / 2 + 1));
  }
  return ret;
}

int main() {
  cout << solve(10000) << endl;
  cout << solve(1000000) << endl;
  cout << solve(10000000000LL) << endl;
  return 0;
}
