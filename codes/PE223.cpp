/**
 * Use the same technique as to generate tree of primitive Pythagorean triple with exactly the same matrix, but with roots (1, 1, 1) and (1, 2, 2).
 * Notice that when a = b, two of the childs are equivalent, so handle this separately.
 * Observe that the perimeter is always odd, which can be used to optimize a bit.
 *
 * The code is heavily optimized, using only primitive data types (using struct, stack, vector may result TLE)
 *
 * References: https://web.archive.org/web/20071128165439/http://www.cut-the-knot.org/pythagoras/PT_matrix.shtml
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 50000000;

int sz;
int st[10000][3];

int cnt[N+2 >> 1];

const int MAGIC = 1000;
int tmp[MAGIC];

int init() {
    st[0][0] = st[0][1] = st[0][2] = 1;
    st[1][0] = 1; st[1][1] = st[1][2] = 2;
    sz = 2;
    
    int cur = 0;
    
    while (sz > 0) {
        --sz;
        int a = st[sz][0], b = st[sz][1], c = st[sz][2];
        
        // This will TLE!
        // ++cnt[a+b+c>>1];
        
        // This is batch update of ++cnt[a+b+c>>1], so that cnt is cached only during this time
        tmp[cur++] = a + b + c >> 1;
        if (cur == MAGIC) {
            for (int i=0; i<MAGIC; i++) ++cnt[tmp[i]];
            cur = 0;
        }
        
        if (5*a - 5*b + 7*c <= N) {
            st[sz][0] = a - 2*b + 2*c, st[sz][1] = 2*a - b + 2*c, st[sz][2] = 2*a - 2*b + 3*c;
            ++sz;
        }
        
        if (5*a + 5*b + 7*c <= N) {
            st[sz][0] = a + 2*b + 2*c, st[sz][1] = 2*a + b + 2*c, st[sz][2] = 2*a + 2*b + 3*c;
            ++sz;
        } 
        
        if (a != b && -5*a + 5*b + 7*c <= N) {
            st[sz][0] = -a + 2*b + 2*c, st[sz][1] = -2*a + b + 2*c, st[sz][2] = -2*a + 2*b + 3*c;
            ++sz;
        }
    }
    
    // Batch update the rest of cnts
    for (int i=0; i<cur; i++) ++cnt[tmp[i]];
    
    for (int i=1; i<=N>>1; i++) cnt[i] += cnt[i-1];
    
    return 0;
}

int solve() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", cnt[n-1 >> 1]);
    }
    
    return 0;
}

int main() {
    clock_t t = clock();
    init();
    solve();
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
