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

const int N = 30000;
bool prime[N];
pipii ans[2002];

bool isprime (int x) {
    assert (x < N);
    if (x < 0) return 0;
    return prime[x];
}

int main () {
    memset (prime, 1, sizeof prime);

    prime[0] = prime[1] = 0;
    for (int i=2; i*i<=N; i++) if (prime[i]) for (int j=2*i; j<=N; j+=i) prime[j] = 0;

    FOR(a, -2000, 2001) FOR(b, -2000, 2001) {
        int cnt = 0;
        while (isprime(cnt * cnt + a * cnt + b)) cnt++;

        if (ans[max(abs(a), abs(b))].fi < cnt) {
            ans[max(abs(a), abs(b))].fi = cnt;
            ans[max(abs(a), abs(b))].se.fi = a;
            ans[max(abs(a), abs(b))].se.se = b;
        }
    }

    FOR(i, 1, 2001) {
        if (ans[i].fi < ans[i-1].fi) {
            ans[i] = ans[i-1];
        }
    }

    int n;
    scanf ("%d", &n);
    printf("%d %d\n", ans[n].se.fi, ans[n].se.se);

    return 0;
}
