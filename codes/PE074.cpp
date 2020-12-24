#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int nxt (int x) {
    int ret = 0;
    while (x) {
        ret += fact[x % 10];
        x /= 10;
    }
    return ret;
}

vector <int> ans;
bool vis[3000000];

int Main() {
    int n, l;
    scanf ("%d %d", &n, &l);
    
    bool no = 1;
    for (int i=0; i<=n; i++) {
        if (ans[i] == l) printf ("%d ", i), no = 0;
    }
    
    if (no) printf ("-1");
    
    return 0 * printf ("\n");
}

int main() {
    for (int i=0; i<=1000000; i++) {
        vector <int> num;
        int now = i;
        
        while (!vis[now]) {
            vis[now] = 1;
            num.push_back(now);
            
            if (num.size() > 60) break;
            now = nxt(now);
        }
        
        ans.push_back(num.size());
        while (num.size()) {
            vis[num.back()] = 0;
            num.pop_back();
        }
    }
    ans[0] = 2;
    
    int t;
    scanf ("%d", &t);
    while (t--) Main();
    return 0;
}
