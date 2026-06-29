// Let a, b, c be the sides of the triangle.
// Circumradius r = abc / 4A, where A is the area of the triangle
// Equivalently, r^2 * (a+b+c) * (a+b-c) * (a-b+c) * (-a+b+c) = (abc)^2

// If A is the angle opposite of a, then by extended law of sine, 2r sin A = a
// If x = 2r cos A, x^2 + a^2 = (2r)^2, i.e. a must be the leg of a pythagorean triangle.
//   Special case when A = pi, then a = 2r is possibly a side as well.

// So we iterate through all Pythagorean triangles.
// Enumerate all possible sides for a fixed hypothenuse r,
// then check for all possible triangles.

// ===========

// Apparently there is a way to solve it by factorising r
// For a "primitive" r = pi^ei where pi = 1 (mod 4),
//   the contribution by this primitive is 2*prod(e) * 6^|primes| - (gcd(ei) != 0) * 2^{|primes|-1}

#include <bits/stdc++.h>
using namespace std;

long long solve(int N) {
    vector<vector<int>> sides(N + 1);

    queue<pair<int, int>> q;
    q.emplace(1, 2);

    while (!q.empty()) {
        int n, m;
        tie(n, m) = q.front();
        q.pop();

        int c = n*n + m*m;
        if (c > N) continue;

        q.emplace(m, n + m);
        q.emplace(n, n + m);

        if ((n & 1) == (m & 1)) continue;

        int a = m*m - n*n, b = 2*m*n;
        for (int k = 2; k <= N*2 / c; k += 2) {
            int r = k * c / 2;
            sides[r].push_back(k * a);
            sides[r].push_back(k * b);
        }
    }

    long long ans = 0;
    for (int r = 1; r < sides.size(); ++r) {
        sides[r].push_back(r*2);
        sort(sides[r].begin(), sides[r].end());
        for (int i = 0; i < sides[r].size(); ++i) {
            for (int j = i; j < sides[r].size(); ++j) {
                for (int k = j; k < sides[r].size(); ++k) {
                    int a = sides[r][i], b = sides[r][j], c = sides[r][k];
                    if (a + b <= c) break;
                    if ((__int128) a*b*c % r != 0) continue;
                    if ((__int128) (a+b+c) * (a+b-c) * (a-b+c) * (-a+b+c) == (__int128) a*b*c/r*a*b*c/r) {
                        ans += r;
                    }
                }
            }
        }
    }

    return ans;
}

int main() {
    cout << solve(100) << endl;
    cout << solve(1200) << endl;
    cout << solve(10000000) << endl;
    return 0;
}
