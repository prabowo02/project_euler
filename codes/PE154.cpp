#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;

int n;
int p[2], q[2];

int a[2][N];

int main() {
    
    scanf("%d", &n);
    for (int i=0; i<2; i++) scanf("%d %d", p + i, q + i);    
    
    for (int i=0; i<2; i++)
        for (int j=1; j<=n; j++) {        
            int tmp = j;
            while (tmp % p[i] == 0) {
                tmp /= p[i];
                a[i][j]++;
            }
            a[i][j] += a[i][j-1];        
        }
    
    long long ans = 0;
    for (int i=0; i*3<=n; i++) {
        for (int j=i; i+j+j<=n; j++) {
            int k = n - i - j;
            if (k < j) break;
            
            if (a[0][n] - (a[0][i] + a[0][j] + a[0][k]) < q[0]) continue;
            if (a[1][n] - (a[1][i] + a[1][j] + a[1][k]) < q[1]) continue;
                        
            if (i == j && i == k) ans += 1;
            else if (i == j || j == k || i == k) ans += 3;
            else ans += 6;
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
