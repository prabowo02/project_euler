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

int grid[22][22];

int get(int x, int y) {
    if (x >= 0 && x < 20 && y >= 0 && y < 20) return grid[x][y];
    return 0;
}

int main () {

    FORR(i, 20) FORR(j, 20) scanf("%d", &grid[i][j]);

    int ans = 0;
    int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

    FORR(i, 20) FORR(j, 20) FORR(k, 8) {
        int tmp = 1;
        FORR(l, 4) tmp *= get(i + dx[k] * l, j + dy[k] * l);
        MAX(ans, tmp);
    }

    printf("%d\n", ans);
    return 0;
}
