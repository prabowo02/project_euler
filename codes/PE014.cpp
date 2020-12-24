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

int pos[63] = {1, 2, 3, 6, 7, 9, 18, 19, 25, 27, 54, 55, 73, 97, 129, 171, 231, 235, 313, 327, 649, 654, 655, 667, 703, 871, 1161, 2223, 2322, 2323, 2463, 2919, 3711, 6171, 10971, 13255, 17647, 17673, 23529, 26623, 34239, 35497, 35655, 52527, 77031, 106239, 142587, 156159, 216367, 230631, 410011, 511935, 626331, 837799, 1117065, 1126015, 1501353, 1564063, 1723519, 2298025, 3064033, 3542887, 3732423};

int f(LL x) {
    if (x == 1) return 0;
    return 1 + f(x & 1 ? (3 * x + 1) : (x >> 1));
}

int Main () {
    int n;
    scanf("%d", &n);
    printf("%d\n", pos[upper_bound(pos, pos + 63, n) - pos - 1]);
    return 0;
}

int main () {

    int t;
    scanf("%d", &t);
    while (t--) Main ();

    /*
    int maks = 0;
    vi ans;
    vi pos;
    for (int i=1; i<=5000000; i++) {
        int tmp = f(i);
        if (tmp >= maks) {
            maks = tmp;
            ans.pb(maks);
            pos.pb(i);
        }
    }
    cout << ans.size() << endl;

    freopen("tmp.txt", "w", stdout);
    printf("ans[] = {"); for (int i=0; i<ans.size(); i++) printf(", %d", ans[i]); printf("};\n");
    printf("pos[] = {"); for (int i=0; i<pos.size(); i++) printf(", %d", pos[i]); printf("};\n");
    */

    return 0;
}
