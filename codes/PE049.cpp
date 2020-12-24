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
typedef vector <pipii> vivii;

//////// End of Template ////////

const int N = 1000000;
bool prime [N];

int main () {
    memset (prime, 1, sizeof prime);
    for (int i=2; i*i<N; i++) if (prime[i]) for (int j=i<<1; j<N; j+=i) prime[j] = 0;

    map <vi, vi> m;
    for (int i=2; i<N; i++) {
        if (!prime[i]) continue;
        vi v;
        int tmp = i;
        while (tmp) {
            v.pb(tmp % 10);
            tmp /= 10;
        }

        sort (ALL(v));

        m[v].pb(i);
    }

    // freopen("tes.out", "w", stdout);
    int n, k;
    scanf ("%d %d", &n, &k);

    if (k == 3) {
            vivii ans;
        for (map <vi, vi> :: iterator it = m.begin(); it != m.end(); ++it) {
            int sz = it->se.size();
            FORR(i, sz) FOR(j, i + 1, sz) FOR(k, j + 1, sz) {
                if (it->se[k] - it->se[j] == it->se[j] - it->se[i] && it->se[i] < n) {
                    ans.pb(mp(it->se[i], mp(it->se[j], it->se[k])));
                }
            }

        }
            sort (ALL(ans));
            FORR(i, ans.size()) {
                printf("%d%d%d\n", ans[i].fi, ans[i].se.fi, ans[i].se.se);
            }
    }

    if (k == 4) {
        vector <pair<pii, pii> > ans;
        for (map <vi, vi> :: iterator it = m.begin(); it != m.end(); ++it) {
            int sz = it->se.size();
            FORR(i, sz) FOR(j, i + 1, sz) FOR(k, j + 1, sz) FOR(l, k + 1, sz) {
                if (it -> se[l] - it->se[k] == it->se[k] - it->se[j] && it->se[k] - it->se[j] == it->se[j] - it->se[i] && it->se[i] < n) {
                    ans.pb( mp( mp( it->se[i], it->se[j]), mp(it->se[k], it->se[l]) ) ) ;
                }
            }

        }
            sort (ALL(ans));
            FORR(i, ans.size()) {
                printf("%d%d%d%d\n", ans[i].fi.fi, ans[i].fi.se, ans[i].se.fi, ans[i].se.se);
            }
    }

    return 0;
}
