#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

const int N = 700;
const LL INF = 1000000000000000000;

struct node {
    int x, y;
    LL dist;
    
    node (int _x, int _y, LL _dist) {
        x = _x;
        y = _y;
        dist = _dist;
    }
    
    bool operator < (const node &other) const {
        return dist > other.dist;
    }
};

int a[N][N];
bool vis[N][N];

int main() {
    int n;
    scanf ("%d", &n);
    for (int i=0; i<n; i++) 
        for (int j=0; j<n; j++)
            scanf ("%d", &a[i][j]);
    
    priority_queue <node> pq;
    pq.push(node(0, 0, a[0][0]));
    
    int dx[4] = {0, -1, 0, 1};
    int dy[4] = {1, 0, -1, 0};
    while (pq.top().x != n - 1 || pq.top().y != n - 1) {
        node now = pq.top();
        pq.pop();
        
        if (vis[now.x][now.y]) continue;
        vis[now.x][now.y] = 1;
        
        for (int i=0; i<4; i++) {
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            
            pq.push(node(nx, ny, now.dist + a[nx][ny]));
        }
    }
    
    printf ("%lld\n", pq.top().dist);
    
    return 0;
}
