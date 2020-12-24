#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair <int, int> pii;

LL cross (pii x, pii y, pii z) {
    return 1LL * (y.first - x.first) * (z.second - y.second) - 1LL * (y.second - x.second) * (z.first - y.first);
}

int main() {
    pii origin = make_pair(0, 0);
    
    int n;
    scanf ("%d", &n);
    
    int ans = 0;
    while (n--) {
        pii p1, p2, p3;
        scanf ("%d %d %d %d %d %d", &p1.first, &p1.second, &p2.first, &p2.second, &p3.first, &p3.second);
        
        ans += (abs(cross(origin, p1, p2)) + abs(cross(origin, p2, p3)) + abs(cross(origin, p3, p1)) == abs(cross(p1, p2, p3)));
    }
    
    printf ("%d\n", ans);
    return 0;
}
