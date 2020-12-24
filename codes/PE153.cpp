#include <bits/stdc++.h>
using namespace std;

int n;

long long s[20000];
long long sumOfDivisors(int n) {
    int i;
    
    long long ret = 0;
    for (i = 1; i*i<=n; i++) ret += n - n % i;
    
    int j = i - 1;
    int hi, lo = n;
    for (i = 1; i*i<n; i++) {
        hi = lo;
        lo = n / (i + 1);
        
        if (lo < j) lo = j;
        
        ret += (long long) (lo + hi + 1) * (hi - lo) * i >> 1;
    }
        
    return ret;
}

int main() {
    clock_t t = clock();
    
    for (int i=1; i<20000; i++) s[i] = sumOfDivisors(i);
    scanf("%d", &n);
    
    long long ans = 0;
    
    ans = sumOfDivisors(n);
    
    queue<pair<int, int>> q;
    q.push({1, 1});
    
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        
        if (x <= y) {
            int d = x*x + y*y;

            long long tmp = n / d;
            if (tmp < 20000) tmp = s[tmp];
            else tmp = sumOfDivisors(tmp);

            ans += tmp * (x == y ? x<<1 : x+y<<1);
        }

        if ((x+y)*(x+y) + y*y <= n) q.push({x+y, y});
        if (x*x + (x+y)*(x+y) <= n) q.push({x, x+y});
    }
    printf("%lld\n", ans);
    fprintf(stderr, "%.6lf\n", (double) (clock() - t) / CLOCKS_PER_SEC);
    return 0;
}
