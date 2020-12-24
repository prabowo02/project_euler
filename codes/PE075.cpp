#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5000005;

vector <int> triple;
int cnt[N];
int sum[N];

int main() {
    for (int m=2; m<N; m++) {
        for (int n=1; n<m && 2LL*m*(m+n)<N; n++) {
            if (__gcd(n, m) > 1) continue;
            if (m - n & 1)
                triple.push_back(2*m*(m+n));
        }
    }
    
    for (int i=0; i<triple.size(); i++) {
        for (int j=triple[i]; j<N; j+=triple[i])
            cnt[j]++;
    }
    
    for (int i=1; i<N; i++) sum[i] = sum[i-1] + (cnt[i] == 1);
    
    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        printf ("%d\n", sum[n]);
    }
    
    return 0;
}
