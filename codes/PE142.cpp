#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1200;

int gcd(int x, int y) {
    return y ? gcd(y, x % y) : x;
}

LL sqr(LL x) {return x * x;}

bool isSquare(LL x) {
    return sqr(floor(sqrt(x))) == x;
}

vector<pair<int, int>> triples[N * N * 2];

int main() {
    
    for (int m=2; m<N; m++) {
        for (int n=(m & 1 ? 2 : 1); n < m; n += 2) {
            if (gcd(m, n) > 1) continue;
            
            LL a = m*m - n*n;
            LL b = m*n*2;
            LL c = m*m + n*n;
            
            for (int k = 1; c*k < N*N*2; k++)
                triples[k * c].push_back({k * a, k * b});
        }
    }     
    
    vector<vector<LL>> ans;
    for (int i=5; i<N*N; i++) {
        for (int j=0; j<triples[i].size(); j++) {
            LL a = i;
            LL c = triples[i][j].first;
            
            for (int k=0; k<triples[c].size(); k++) {                
                LL b = triples[c][k].first;                         
                
                if (a*a + b*b & 1) continue;
                
                LL x = a*a + b*b >> 1;
                LL y = a*a - x;
                LL z = c*c - x;
                                
                if (x <= 1000000000000LL && x > y && y > z && z > 0 && isSquare(x - z))
                    ans.push_back({x, y, z});
            }
        }
    }
    
    cerr << ans.size() << endl;
    
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++) printf("%lld %lld %lld\n", ans[i][0], ans[i][1], ans[i][2]);
    return 0;
}
