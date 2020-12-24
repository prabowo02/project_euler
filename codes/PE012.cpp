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

int t, n;
int pos[] = {1, 2, 3, 7, 8, 15, 24, 32, 35, 63, 80, 104, 224, 384, 560, 935, 1224, 1664, 1728, 2015, 2079, 5984, 12375, 14399, 21735, 41040};
int ans[] = {1, 2, 4, 6, 9, 16, 18, 20, 24, 36, 40, 48, 90, 112 ,128, 144, 162, 168, 192, 240, 320, 480, 576, 648, 768, 1024};

int Main () {
    int n;
    scanf("%d", &n);
    int tmp = pos[upper_bound(ans, ans + 26, n) - ans];
    printf("%d\n", tmp * (tmp + 1) >> 1);
    return 0;
}

int main () {

    int t;
    scanf("%d", &t);
    while (t--) Main ();

/*
    int cnt = 0;
    int i = 1;
    int maks = 0;
    while (cnt < 1000) {
        cnt = 0;

        for (int j=1; j*j<=i*(i+1)/2; j++) {
            if (i*(i+1)/2 % j == 0) {
                cnt += 2;
                if (j * j == i*(i+1)/2) cnt--;
            }
        }

        if (maks < cnt) {
            maks = cnt;
            cout << "Current highest : " << maks << endl;
            cout << "at : " << i << endl;
        }

        i++;
    }
*/
    return 0;
}
