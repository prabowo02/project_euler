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

int len (LL x) {
    int ret = 0;
    while (x) ret++, x /= 10;
    return ret;
}

bool vis[100002];

int main () {
    int n;
    scanf ("%d", &n);

    int ans = 0;

    for (LL i=1; i<10000; i++) {
        for (int j=1; j<10000; j++) {
            LL tmp = len(i) + len(j) + len(i * j);
            if (tmp > n) break;
            if (tmp < n) continue;

            if (vis[i * j]) continue;

            bool s[10] = {};

            tmp = i;
            while (tmp) s[tmp % 10] = 1, tmp /= 10;

            tmp = j;
            while (tmp) s[tmp % 10] = 1, tmp /= 10;

            tmp = i * j;
            while (tmp) s[tmp % 10] = 1, tmp /= 10;

            bool ok = 1;
            if (s[0]) continue;
            for (int i=1; i<=n; i++) ok &= s[i];

            if (ok) ans += i * j, vis[i * j] = 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}
