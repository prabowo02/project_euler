#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 8000001;

int prime[N];

vector<int> factors(int n) {
    vector<int> ret; ret.push_back(1);
    
    while (n > 1) {
        int cnt = 0;
        int p = prime[n];
        do {
            cnt++;
            n /= p;
        } while (n % p == 0);
        
        int mul = 1; int sz = ret.size();
        for (int i=0; i<cnt; i++) {
            mul *= p;
            for (int j=0; j<sz; j++) ret.push_back(ret[j] * mul);
        }
    }
    
    // for (int i=0; i<ret.size(); i++) cerr << ret[i] << endl;
    
    return ret;
}

int Main() {
    int n;
    scanf ("%d", &n);
    vector<int> f = factors(n);
    
    int ans = 0;
    for (int i=0; i<f.size(); i++) {
        int a = f[i];
        if ((1LL*a*a + n) % (a << 2) == 0) {
            int d = (1LL*a*a + n) / (a << 2);
            if (a - d > 0) ans++;
        }
    }
    
    return 0 * printf ("%d\n", ans);
}

int main() {
    memset(prime, -1, sizeof prime); prime[1] = 1;
    for (int i=2; i<N; i++) if (prime[i] == -1) 
        for (int j=i; j<N; j+=i) prime[j] = i;        
        
    int t;
    scanf ("%d", &t);
    while (t--) Main();
    return 0;
}
