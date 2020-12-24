#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3005;

int n;
int l, a[10005], f[N*N];
int m, b[10005], g[N*N];

int s[N][N];
int anti[N][N];
int psum[5][N][N];

bool inrange(int i, int x, int y) {
    return x >= 0 && x <= i && y >= 0 && y <= i;
}

int main() {
    scanf("%d", &n);
    
    scanf("%d", &l);
    for (int i=0; i<l; i++) scanf("%d", a + i);
    for (int i=0; i<5; i++) scanf("%d", f + i);
    for (int i=5; i<n*n; i++) f[i] = (f[i-1] + f[i-2] + f[i-3] + f[i-4] + f[i-5]) % l;
    
    scanf("%d", &m);
    for (int i=0; i<m; i++) scanf("%d", b + i);
    for (int i=0; i<5; i++) scanf("%d", g + i);
    for (int i=5; i<n*n; i++) g[i] = (g[i-1] + g[i-2] + g[i-3] + g[i-4] + g[i-5]) % m;
    
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) s[i][j] = a[f[i*n + j]] + b[g[i*n + j]];  
    
    for (int i=0; i<5; i++) psum[i][0][0] = s[0][0];    
        
    int maks = s[0][0];
    printf("%d\n", s[0][0]);
        
    int dx[4] = {0, -1, -1};
    int dy[4] = {-1, 0, -1};
    for (int i=1; i<n; i++) {
        for (int j=0; j<=i; j++) {
            
            for (int k=0; k<3; k++) 
                if (inrange(i, j + dx[k], i + dy[k]))
                    maks = max(maks, psum[k][j][i] = max(psum[k][j + dx[k]][i + dy[k]] + s[j][i], s[j][i]));
                else maks = max(maks, psum[k][j][i] = s[j][i]);
            
            for (int k=0; k<3; k++)
                if (inrange(i, i + dx[k], j + dy[k]))
                    maks = max(maks, psum[k][i][j] = max(psum[k][i + dx[k]][j + dy[k]] + s[i][j], s[i][j]));
                else maks = max(maks, psum[k][i][j] = s[i][j]);
                
            if (j < i) {
                maks = max(maks, psum[3][i][j] = max(psum[3][i-1][j+1] + s[i][j], s[i][j]));
                maks = max(maks, psum[3][i][j] = max(psum[3][i][j], anti[i][j] = anti[i-1][j+1] + s[i][j] + s[j][i]));
                
                maks = max(maks, psum[4][j][i] = max(psum[4][j+1][i-1] + s[j][i], s[j][i]));
                maks = max(maks, psum[4][j][i] = max(psum[4][j][i], anti[i][j]));                
            } else psum[3][i][j] = psum[4][i][j] = anti[i][j] = s[i][j];
        }
        printf("%d\n", maks);
    }        
        
    return 0;
}
