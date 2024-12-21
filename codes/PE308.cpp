// FRACTRAN program
// https://link.springer.com/chapter/10.1007/978-1-4612-4808-8_2
#include <cstdio>

long long solve(int N) {
    long long ans = 5;
    for (int n = 2; ; ++n) {
        int d;
        for (d = n - 1; d > 0; --d) {
            ans += 1LL * n / d * (d * 4 + 2);
            ans += n % d * 2 + 2;

            if (n % d == 0) {
                ans += n * 3 + d + 1;
                break;
            }

            ans += n * 2 + 1;
            ans += (n % d - 1) * 2 + 1;
        }

        if (d == 1) {
            if (--N == 0) {
                return ans - n * 3 - d - 1;
            }
        }
    }
    return -1;
}

int main() {
    printf("%lld\n", solve(10001));
    return 0;
}
