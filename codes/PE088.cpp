#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200005;
int ans[N];

void factorize (int n, int prod, int sum = 0, int term = 0, int st = 2) {
    for (int i=st; i*i<=n; i++) {
        if (n % i) continue;
        factorize(n / i, prod, sum + i, term + 1, i);
    }
    
    if (n > 1) sum += n, term += 1;
    
    int tmp = term + prod - sum;
    if (tmp < N) {
        if (ans[tmp] == 0 || ans[tmp] > prod)
            ans[tmp] = prod;
    }
}

void construct (int prod = 1, int sum = 0, int term = 0, int st = 2) {    
    for (int i=st; i<(N<<1)/prod; i++) {
        construct (prod * i, sum + i, term + 1, i);
    }
    
    term += prod - sum;
    if (term < N) if (ans[term] == 0 || ans[term] > prod)
        ans[term] = prod;
}

int main() {
    construct();
    
    int n; scanf ("%d", &n);
    // for (int i=4; i<=n<<1; i++) factorize (i, i);
    
    vector <int> num;
    for (int i=2; i<=n; i++) num.push_back(ans[i]); //, cout << ans[i] << endl;
    sort(num.begin(), num.end());
    num.resize(unique(num.begin(), num.end()) - num.begin());
    
    long long sum = 0;
    for (int i=0; i<num.size(); i++) sum += num[i];
    printf ("%lld\n", sum);
    return 0;
}
