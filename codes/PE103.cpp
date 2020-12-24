#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000000;
const int MOD = 715827881;

struct SegTree {
    int sum[N << 2];
    int lazy[N << 2];
    
    void propagate (int node) {
        for (int i=0; i<2; i++) {
            sum[2*node + i + 1] += lazy[node];
            lazy[2 * node + i + 1] += lazy[node];
            
            sum[2 * node + i + 1] %= MOD;
            lazy[2 * node + i + 1] %= MOD;
        }
        
        lazy[node] = 0;
    }
    
    void update (int node, int l, int r, int a, int b, int val) {
        if (l > b || r < a) return;
        if (l >= a && r <= b) {
            sum[node] += val;
            lazy[node] += val;
            sum[node] %= MOD;
            lazy[node] %= MOD;
            return;
        }
        
        propagate(node);
        
        int mid = l + r >> 1;
        update (2 * node + 1, l, mid + 0, a, b, val);
        update (2 * node + 2, mid + 1, r, a, b, val);
        return;
    }
    
    int query (int node, int l, int r, int x) {
        if (l > x || r < x) return 0;
        if (l == x && r == x) return sum[node];
        
        propagate(node);
        
        int mid = l + r >> 1;
        return query(2*node + 1, l, mid, x) + query(2*node + 2, mid+1, r, x);
    }
} tree;

int main() {
    int n;
    scanf ("%d", &n);
    
    tree.update(0, 0, n, 0, 0, 1);
    for (int i=1; i<n; i++) {
        int b = tree.query(0, 0, n, i - 1 >> 1);
        tree.update(0, 0, n, 0, i, b);
    }
    
    for (int i=0; i<n; i++) {
        printf ("%d ", tree.query(0, 0, n, n-i-1));
    }
    return 0;
}
