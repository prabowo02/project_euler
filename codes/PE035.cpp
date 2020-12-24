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

const int N = 1000001;
bool prime [N];

int main () {
    memset (prime, 1, sizeof prime);
    prime[0] = prime[1] = 0;
    for (int i=2; i*i<N; i++) if (prime[i]) for (int j=i<<1; j<N; j+=i) prime[j] = 0;

    int n;
    scanf ("%d", &n);

    int ans = 0;
    for (int i=2; i<n; i++) {
        int num = 0;
        int tmp = i;
        int ten = 1;

        while (tmp) {
            num++;
            ten *= 10;
            tmp /= 10;
        }

        ten /= 10;

        bool ok = 1;
        tmp = i;
        FORR(j, num) {
            ok &= prime[tmp];
            tmp = tmp / 10 + tmp % 10 * ten;
        }

        if (ok) ans += i;
    }

    printf ("%d\n", ans);

    return 0;
}
