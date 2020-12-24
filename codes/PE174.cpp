#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

int n;
int nDivisors[MAXN];
bool isSquare[MAXN];

int N[11][MAXN];

int main() {
    for (int n=2; n<MAXN; n++) {
        int cnt = 0;
        for (int d=2; d*d<n; d+=2) {
            if ((n - d*d) % (d*2)) continue;
            ++cnt;
        }
        
        if (cnt <= 10) ++N[cnt][n];
    }
    
    for (int k=1; k<=10; k++) for (int n=1; n<MAXN; n++) N[k][n] += N[k][n-1];
        
    for (int n=1; n<MAXN; n++) for (int k=1; k<10; k++) N[10][n] += N[k][n];            
    
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        
        printf("%d\n", N[10][n]);
    }
    
    return 0;
}
