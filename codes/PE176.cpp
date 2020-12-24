#include <bits/stdc++.h>
using namespace std;

vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
vector<int> e = {53, 20, 10, 6, 4, 3, 2, 2, 1, 1, 1, 1, 1};

long long ans[1000005];
void update(int x, long long val) {
    if (ans[x] == -1) ans[x] = val;
    ans[x] = min(ans[x], val);
}

void f(int x, long long prod, int lst, int carry) {
    if (x == p.size()) return;
    int mini = min(lst, e[x]);

    long long tmp = 1;
    for (int i=1; i<=mini; i++) {
        tmp *= p[x];
        if (prod * tmp / tmp != prod) break;
        if (prod * tmp > 10000000000000000LL) break;
        
        int c;
        if (x) c = carry * (i*2 + 1);
        else c = carry * (i*2 - 1);
        if (c > 2000001) break;
        
        update(c - 1 >> 1, prod*tmp);
        
        f(x+1, prod*tmp, i, c);
    }
}

int main() {
    memset(ans, -1, sizeof ans);
    f(0, 1, 60, 1);
    ans[1] = 3;
    
    int q;
    scanf("%d", &q);
    
    int n;
    while (q--) {
        scanf("%d", &n);
        printf("%lld\n", ans[n]);
    }
    return 0;
}
