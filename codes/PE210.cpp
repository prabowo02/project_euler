#include <bits/stdc++.h>
using namespace std;

const __int128 ONE = 1;

// assuming b positive
long long floor(long long a, long long b) {
    return (a >= 0 ? a / b : (a - b + 1) / b);
}

long long ceil(long long a, long long b) {
    return floor(a + b - 1, b);
}

// Find the number of lattice point strictly inside a circle
// with radius spanning from (0, 0) to (a/b, a/b)
long long count_circle_lattice(long long a, long long b) {
    long long ret = 0;
    long double r = (long double) a / b;
    for (int i=ceil(a, b); ONE*i*i*b*b<ONE*2*a*a; i++) {
        int tmp = sqrt(2*r*r - 1LL*i*i);
        while (ONE*b*b * (1LL*tmp*tmp + 1LL*i*i) >= ONE*2*a*a) {
            --tmp;
        }

        while (ONE*b*b * (1LL*(tmp+1)*(tmp+1) + 1LL*i*i) < ONE*2*a*a) {
            ++tmp;
        }

        ret += tmp*2 + 1;
    }
    // cerr << ret << endl;
    ret <<= 2;

    int s = (a % b ? a / b : a / b - 1);
    ret += 4LL*s*s + 4LL*s + 1;

    return ret;
}

// Count the number of lattice point satisfying:
//  - |x| + |y| <= r
//  - x + y <= n
// Assuming |n| <= r
long long count_rectangle(int r, int n) {
    return 1LL * r * (n+r+1) + (n+r+2)/2;
}

// Count the number of lattice point satisfying:
//  - |x| + |y| <= r
//  - a/b <= x + y <= c/d
long long count(int r, long long a, long long b, long long c, long long d) {
    if (ONE*a*d > ONE*b*c) swap(a, c), swap(b, d);
    // cerr << a << " " << b << " " << c << " " << d << endl;
    return count_rectangle(r, floor(c, d)) - count_rectangle(r, a % b ? floor(a, b) : floor(a, b) - 1);
}

int main() {
    int r, a, b, n;
    scanf("%d %d %d %d", &r, &a, &b, &n);

    long long ans = count_circle_lattice(abs(1LL*n*b - a), b);
    // cerr << "circle: " << ans << endl;
    // cerr << "all: " << count_rectangle(r, r) << endl;
    // cerr << "sub: " << count(r, 4LL*n*b - 2*a, b, 2*a, b) << endl;

    ans += count_rectangle(r, r) - count(r, 4LL*n*b - 2*a, b, 2LL*a, b);

    ans -= (r & 1 ? r : r + 1);

    if (a % b == 0) ans += 2;

    printf("%lld\n", ans);
    return 0;
}
