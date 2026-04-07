#include <bits/stdc++.h>

using namespace std;

long long solve(int n) {
    vector<bool> primes(n + 2, true);
    for (int p = 2; p < primes.size(); ++p) {
        if (!primes[p]) continue;
        for (int i = p+p; i < primes.size(); i += p) {
            primes[i] = false;
        }
    }

    vector<bool> can(n + 1, true);
    for (int d = 1; d <= n; ++d) {
        for (int i = d; i <= n; i += d) {
            if (!primes[d + i/d]) {
                can[i] = false;
            }
        }
    }

    long long ret = 0;
    for (int i = 1; i <= n; ++i) {
        if (can[i]) ret += i;
    }
    return ret;
}

int main() {
    printf("%lld\n", solve(100000000));
    return 0;
}