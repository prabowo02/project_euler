#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long LL;
const int N = 2222;

int ans[N * N];
LL dp[N][N];

int dist[N * N];

int main() {
    for (int i=1; i<N; i++) {
        for (int j=1; j<N; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + i * j;
            if (dp[i][j] >= N * N) {
                // cout << i << " " << j << " " << dp[i][j] << endl;
                break;
            }
            
            ans[dp[i][j]] = max(ans[dp[i][j]], i * j);
        }
    }
    
    queue <int> q;
    for (int i=1; i<N*N; i++) {
        if (ans[i]) {
            q.push(i);
            dist[i] = 1;
        }
    }    
    
    while (q.size()) {
        int now = q.front();
        q.pop();
        
        if (now - 1 > 0) {
            if (dist[now - 1] == 0) {
                q.push(now - 1);
                ans[now - 1] = ans[now];
                dist[now - 1] = dist[now] + 1;
            } else if (dist[now - 1] == dist[now] + 1) {
                ans[now - 1] = max(ans[now - 1], ans[now]);
            }
        }
        
        if (now + 1 < N * N) {
            if (dist[now + 1] == 0) {
                q.push(now + 1);
                ans[now + 1] = ans[now];
                dist[now + 1] = dist[now] + 1;
            } else if (dist[now + 1] == dist[now] + 1) {
                ans[now + 1] = max(ans[now + 1], ans[now]);
            }
        }
    }
    
    int t;
    scanf ("%d", &t);
    while (t--) {
        int n;
        scanf ("%d", &n);
        assert (1 <= n && n <= 2000000);
        printf ("%d\n", ans[n]);
    }
    return 0;
}
