#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>
#include <string>
using namespace std;

const int N = 1 << 8;

vector <int> c;
int deg[N];
vector <int> edge[N];

int main() {
    int t;
    scanf ("%d", &t);
    while (t--) {
        char login[5];
        scanf ("%s", login);
        
        for (int i=0; i<3; i++) c.push_back(login[i]);
        for (int i=1; i<3; i++) {
            edge[login[i-1]].push_back(login[i]);
            deg[login[i]]++;
        }
    }
    
    sort (c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    
    priority_queue <int, vector<int>, greater<int> > pq;
    string ans;
    
    for (int i=0; i<c.size(); i++) {
        if (deg[c[i]] == 0) pq.push(c[i]);
    }
    
    while (pq.size()) {
        int now = pq.top();
        pq.pop();
        
        ans += now;
        
        for (int i=0; i<edge[now].size(); i++) {
            int v = edge[now][i];
            
            deg[v]--;
            if (deg[v] == 0) pq.push(v);
        }
    }
    
    if (ans.size() != c.size()) printf ("SMTH WRONG\n");
    else cout << ans << endl;
    
    return 0;
}
