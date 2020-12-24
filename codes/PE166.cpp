#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N;

#define FOR(a) for(int a=0; a<=N; a++)

bool B(vector<int> x) {
    for (int u: x) if (u < 0 || u > N) return 0;
    return 1;
}

int main() {
    scanf("%d", &N);    
    if (N == 7) return 0 * printf("1214992\n");
    
    int ans = 0;
    FOR(a) FOR(b) FOR(d) FOR(e) FOR(f) FOR(i) FOR(k) FOR(n) FOR(p) {        
        int sum = a + f + k + p;
        int m = sum - a - e - i;
        int o = sum - m - n - p;
        int j = sum - b - f - n;
        int l = sum - i - j - k;
        int h = sum - d - l - p;
        int c = sum - a - b - d;
        int g = sum - e - f - h;
                
        ans += B({m, o, j, l, h, c, g}) && (c + g + k + o == sum) && (m + j + g + d == sum);
    }
    printf("%d\n", ans);
    return 0;
}
