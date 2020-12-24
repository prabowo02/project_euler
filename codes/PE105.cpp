#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int t, n;
int a[N];

short cnt[N * 1000000 + 1];

bool check1() {
    if (n > 24) return 0;
    
    int sum;
    for (int i=1; i<1<<n; i++) {        
        sum = 0;
        for (int j=0; j<n; j++) {
            if (i >> j & 1) sum += a[j];
        }
        
        if (cnt[sum] == t + 1) return 0;
        cnt[sum] = t + 1;
    }
    
    return 1;
}

bool check2() {
    int l = 1;
    int r = n-1;
    int b = a[0];
    int c = 0;
    
    bool cur = 0;
    while (l <= r) {
        if (cur) {
            b += a[l++];
            if (b < c) return 0;
        } else c += a[r--];
        
        cur ^= 1;
    }
    
    return 1;
}

int main() {
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        
        for (int i=0; i<n; i++) scanf ("%d", a + i);
        sort (a, a + n);
        
        if (check2() && check1()) printf ("YES\n");
        else printf ("NO\n");
    }
    return 0;
}
