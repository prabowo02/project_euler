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

string unit (int x) {
    if (x == 0) return "";
    if (x == 1) return "One ";
    if (x == 2) return "Two ";
    if (x == 3) return "Three ";
    if (x == 4) return "Four ";
    if (x == 5) return "Five ";
    if (x == 6) return "Six ";
    if (x == 7) return "Seven ";
    if (x == 8) return "Eight ";
    if (x == 9) return "Nine ";
    return "";
}

string thousand (int x) {
    string ret;

    if (x / 100) ret = unit(x / 100) + "Hundred ";

    x %= 100;

    if (x >= 10 && x < 20) {
        if (x == 10) ret += "Ten ";
        if (x == 11) ret += "Eleven ";
        if (x == 12) ret += "Twelve ";
        if (x == 13) ret += "Thirteen ";
        if (x == 14) ret += "Fourteen ";
        if (x == 15) ret += "Fifteen ";
        if (x == 16) ret += "Sixteen ";
        if (x == 17) ret += "Seventeen ";
        if (x == 18) ret += "Eighteen ";
        if (x == 19) ret += "Nineteen ";
        return ret;
    } else if (x / 10) {
        if (x / 10 == 2) ret += "Twenty ";
        if (x / 10 == 3) ret += "Thirty ";
        if (x / 10 == 4) ret += "Forty ";
        if (x / 10 == 5) ret += "Fifty ";
        if (x / 10 == 6) ret += "Sixty ";
        if (x / 10 == 7) ret += "Seventy ";
        if (x / 10 == 8) ret += "Eighty ";
        if (x / 10 == 9) ret += "Ninety ";
    }

    x %= 10;
    ret += unit(x);
    return ret;
}

string number (LL x, int y = 0) {
    if (x == 0) {
        if (y == 0) return "Zero ";
        return "";
    }

    string ret;
    ret = number(x / 1000, y + 1) + thousand(x % 1000);
    if (x % 1000) {
        if (y == 1) ret += "Thousand ";
        if (y == 2) ret += "Million ";
        if (y == 3) ret += "Billion ";
        if (y == 4) ret += "Trillion ";
    }

    return ret;
}

int Main () {
    LL n;
    scanf("%lld", &n);
    cout << number (n) << endl;
    return 0;
}

int main () {
    int t;
    scanf("%d", &t);
    while (t--) Main ();
    return 0;
}
