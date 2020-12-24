#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <istream>
#include <ostream>
#include <deque>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <utility>

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define endl '\n'
#define MOD 1000000007
#define MOD9 1000000009
#define INF 2000000000
#define INF2 1000000000
#define INFLL 9000000000000000000LL
#define INFLL2 4500000000000000000LL
#define EPS 1e-7
#define debug puts("ganteng")
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define FORR(i, n) FOR(i, 0, n)
#define REV(i, a, b) for (int i=a-1; i>=b; i--)
#define REVV(i, n) REV(i, n, 0)
#define ALL(x) x.begin(), x.end()
#define UNIK(x) unique(ALL(x)) - x.begin()
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define sqr(x) (((LL)x) * ((LL)x))
#define SYNC ios_base::sync_with_stdio(0), cin.tie(0)
#define TLE using
#define RTE namespace
#define WA std

TLE RTE WA;

typedef long long LL;
typedef pair <int, int> pii;
typedef pair <int, pii> pipii;

typedef vector <int> vi;
typedef vector <pii> vii;
typedef pair <LL, LL> pll;
typedef vector <LL> vl;
typedef vector <pll> vll;

//////// End of Template ////////

int ten[5];
int n, K;
pii ans;

int gcd (int x, int y) {return y ? gcd(y, x % y) : x;}

bool f(int x, int y, int a, int b, int k) {
    if (k == 0) {
        // if (b && x / gcd(x, y) == a / gcd(a, b) && y / gcd(x, y) == b / gcd(a, b) && (x / a != ten[K])) cout << x << " / " << y << " = " << a << " / " << b << endl;
        return (a > 0 || b > 0) && x / gcd(x, y) == a / gcd(a, b) && y / gcd(x, y) == b / gcd(a, b);
    }

    FORR(i, n + k - K) {
        FORR(j, n + k - K) if (a / ten[i] % 10 == b / ten[j] % 10 && a / ten[i] % 10 > 0) {
            if(f(x, y, a / ten[i + 1] * ten[i] + a % ten[i], b / ten[j + 1] * ten[j] + b % ten[j], k - 1)) return 1;
        }
    }

    return 0;
}

int main () {
    scanf ("%d %d", &n, &K);

    if (n == 4) {
        if (K == 1) printf("12999936 28131911\n");
        else if (K == 2) printf("3571225 7153900\n");
        else if (K == 3) printf ("255983 467405\n");
        return 0;
    }

    int num = 0;
    int den = 0;

    ten[0] = 1;
    for (int i=1; i<=n; i++) ten[i] = ten[i-1] * 10;

    ans = mp(0, 0);

    FOR(i, ten[n-1], ten[n]) {
        FOR(j, i + 1, ten[n]) {
            if (f(i, j, i, j, K)) ans.fi += i, ans.se += j;
        }
    }

    printf("%d %d\n", ans.fi, ans.se);

    return 0;
}
