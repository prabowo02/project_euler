#include <bits/stdc++.h>
using namespace std;

int n, m;

int getBit(int x, int y) {
    return x >> y & 1;
}

int setBit(int x, vector<int> y) {
    for (int i=0; i<y.size(); i++) {
        x |= 1 << y[i];
    }
    return x;
}

int dp[21][8][1 << 8][1 << 6];
int f(int x, int y, int mask1, int mask2) {
    // cerr << x << " " << y << " " << (bitset<5>(mask1)) << " " << (bitset<5>(mask2)) << endl;
    
    if (y == m + 2) return f(x+1, 2, (mask1 << 2 & ~(3 << m + 2)) | (mask2 & 3), mask2 & ~3);
    if (x == n) return mask1 == 0 && mask2 == 0;
    
    long long ret = dp[x][y][mask1][mask2];
    if (~ret) return ret;
        
    int nmask1 = (mask1 & ~(1 << y) | getBit(mask2, y) << y);
    int nmask2 = (mask2 & ~(1 << y));
    
    if (getBit(mask1, y) == 1) return ret = f(x, y+1, setBit(nmask1, {}), nmask2);
    
    ret = 0;
    if (y < m+1 && getBit(nmask1, y + 1) == 0) {
        if (getBit(nmask1, y - 1) == 0) ret += f(x, y+1, setBit(nmask1, {y-1, y+1}), nmask2);
        if (getBit(nmask1, y - 2) == 0) ret += f(x, y+1, setBit(nmask1, {y-2, y+1}), nmask2);
        
        if (y < m && getBit(nmask1, y + 2) == 0) {
            ret += f(x, y+1, setBit(nmask1, {y + 1, y + 2}), nmask2);
        }
    }
    if (y > 2 && getBit(nmask1, y - 2) == 0 && getBit(nmask1, y - 3) == 0) ret += f(x, y+1, setBit(nmask1, {y-2, y-3}), nmask2);
    if (y < m+1 && getBit(nmask1, y - 2) == 0 && getBit(nmask1, y - 1) == 0) ret += f(x, y+1, setBit(nmask1, {y-2, y-1}), nmask2);
    
    if (getBit(nmask1, y - 2) == 0 && getBit(nmask2, y-2) == 0) ret += f(x, y+1, setBit(nmask1, {y-2}), setBit(nmask2, {y-2}));
    
    return dp[x][y][mask1][mask2] = ret % 1000000007;
}

int main() {
    scanf("%d %d", &n, &m);
    swap(n, m);
    
    memset(dp, -1, sizeof dp);
    printf("%d\n", f(0, 2, 0, 0));
    return 0;
}
