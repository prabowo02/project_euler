#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1000001;

int phi[N];
LL F[N];

int main() {
    for (int i=1; i<N; i++) phi[i] = i;
    for (int i=2; i<N; i++) if (phi[i] == i) for (int j=i; j<N; j+=i) phi[j] /= i, phi[j] *= i - 1;
        
    for (int i=2; i<N; i++) F[i] = F[i-1] + phi[i];
        
    int t;
    scanf ("%d", &t);
    while (t--) {
        int n;
        scanf ("%d", &n);
        printf ("%lld\n", F[n]);
    }
    return 0;
}
