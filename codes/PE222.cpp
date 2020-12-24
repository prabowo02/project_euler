#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define double long double

const int N = 500005;

int R, n;
int r[N];

void alt(int n, int a[]) {
    int b[n], idx = 0;
    for (int i=n-1; i>=0; i-=2) b[idx++] = a[i];
    for (int i=n&1; i<n; i += 2) b[idx++] = a[i];
    
    for (int i=0; i<n; i++) a[i] = b[i];
}

long long compute() {
    double ans = r[0] + r[n-1];
    for (int i=1; i<n; i++) ans += sqrt(1LL * R * (r[i] + r[i-1]) - 1LL * R * R) * 2;
    
    return (long long) round(ans * 1000);
}

int main() {
    scanf("%d %d", &R, &n);
    for (int i=0; i<n; i++) scanf("%d", r + i);
    sort(r, r + n);
    alt(n, r);
    
    cout << compute() << endl;
    return 0;
}
