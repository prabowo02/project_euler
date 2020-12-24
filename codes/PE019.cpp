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

bool leap (int y) {
    return y % 100 ? y % 4 == 0 : y % 400 == 0;
}

LL cnt (LL y, int m) {
    LL ret = y / 400 * 688;
    y %= 400;

    int now = 0;
    int sun[12] = {2, 6, 6, 3, 1, 5, 3, 0, 4, 2, 6, 4};

    FORR(i, y) {
        now++, now %= 7;

        FORR(i, 2) ret += sun[i] == now;

        now += leap(i), now %= 7;

        FOR(i, 2, 12) ret += sun[i] == now;
    }

    now++, now %= 7;
    FORR(i, min(2, m)) ret += sun[i] == now;
    now += leap(y), now %= 7;
    FOR(i, min(2, m), m) ret += sun[i] == now;

    return ret;
}

int Main () {
    LL y, yy;
    int m, mm, d, dd;
    scanf("%lld %d %d", &y, &m, &d);
    scanf("%lld %d %d", &yy, &mm, &dd);

    d--; if (d == 0) m--; if (m == 0) y--, m = 12;

    printf("%lld\n", cnt(yy, mm) - cnt(y, m));
    return 0;
}

int main () {
    int t;
    scanf("%d", &t);
    while (t--) Main ();
    return 0;
}
