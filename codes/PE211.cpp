#include <bits/stdc++.h>
using namespace std;

const int N = 6000001;
const int K = 1000002;

int q;

long long sqdivisors[N];
vector<int> kaway[K];

vector<int> kquery[K];
vector<int> kindex[K];
long long ans[K];

struct BIT {
    long long sum[N];

    void update(int x) {
        for (int i=x; i<N; i+=i&-i) sum[i] += x;
    }
    
    long long query(int x) {
        long long ret = 0;
        for (int i=x; i; i-=i&-i) ret += sum[i];
        return ret;
    }
} bit;

void init() {
    for (int i=1; i<N; i++) {
        for (int j=i; j<N; j+=i) {
            sqdivisors[j] += 1LL * i * i;
        }
    }
    
    for (int i=1; i<N; i++) {
        int tmp = sqrt(sqdivisors[i]);
        // assert(1LL * tmp * tmp <= sqdivisors[i] && sqdivisors[i] < 1LL * (tmp+1) * (tmp+1));
        int sqaway = min(sqdivisors[i] - 1LL * tmp * tmp, 1LL * (tmp+1) * (tmp+1) - sqdivisors[i]);
        kaway[min(sqaway, K-1)].push_back(i);
    }
    
    // long long maks = 0; for (int i=1; i<N; i++) maks = max(maks, sqdivisors[i]); cerr << maks << endl;
}

void read() {
    scanf("%d", &q);
    for (int i=0; i<q; i++) {
        int n, k;
        scanf("%d %d", &n, &k);
        kquery[k].push_back(n);
        kindex[k].push_back(i);
    }
}

void solve() {
    for (int i=0; i<K; i++) {
        for (int j: kaway[i]) bit.update(j);
        for (int j=0; j<kquery[i].size(); j++) {
            ans[kindex[i][j]] = bit.query(kquery[i][j]);
        }
    }
}

void print() {
    for (int i=0; i<q; i++) {
        printf("%lld\n", ans[i]);
    }
}

int main() {
    // clock_t t = clock();
    init();
    read();
    solve();
    print();
    // cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
