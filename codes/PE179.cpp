#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10000001;
int ndiv[N];

int sum[N];

int main() {
    for (int i=2; i<N; i++) ndiv[i] = 1;
    for (int i=2; i<N; i++) if (ndiv[i] == 1) {
        for (int j=i; j<N; j+=i) {
            int tmp = j;
            int cnt = 0;
            do {
                tmp /= i;
                ++cnt;
            } while (tmp % i == 0);
            
            ndiv[j] *= cnt + 1;
        }
    }
    
    for (int i=2; i<N-1; i++) sum[i] = sum[i-1] + (ndiv[i] == ndiv[i+1]);
    
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", sum[n-1]);
    }
    return 0;
}
