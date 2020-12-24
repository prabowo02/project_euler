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

int d(int x) {
    int ret = -x;
    for (int i=1; i*i<=x; i++) {
        if (x % i == 0) ret += i, ret += x / i * (i * i != x);
    }
    return ret;
}

set <int> amic;

int Main () {
    int n;
    scanf("%d", &n);
    int ans = 0;
    for (set <int> :: iterator it = amic.begin(); it != amic.end(); ++it) {
        if (*it > n) break;
        ans += *it;
    }

    return 0 * printf("%d\n", ans);
}

int main () {
    vii v;

    FOR(i, 1, 100001) v.pb(mp(i, d(i))), v.pb(mp(d(i), i));
    sort (v.begin(), v.end());
    FORR(i, v.size()-1) if (v[i] == v[i + 1] && v[i].fi != v[i].se) amic.insert(v[i].fi), amic.insert(v[i].se);

    // freopen("tc.in", "w", stdout);
    // for (set <int> :: iterator it = amic.begin(); it != amic.end(); ++it) printf("%d ", *it);

    int t;
    scanf("%d", &t);
    while (t--) Main ();

    return 0;
}
