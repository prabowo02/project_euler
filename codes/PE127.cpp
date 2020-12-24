#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

typedef long double Double;

int radical[N];
pair<int, int> radicals[N];

long long ans[N];
vector<pair<int, int>> queryC[N];
vector<pair<double, int>> queries;
vector<double> Rs;

long long Bit[N];

void update(int x, int val) {
    for (int i=x+1; i<=N; i+=i&-i)
        Bit[i-1] += val;
}

long long query(int x) {
    long long ret = 0;
    for (int i=x+1; i; i-=i&-i) 
        ret += Bit[i-1];
    return ret;
}

void add(int a, int b, int c) {
    int radABC = radical[a] * radical[b] * radical[c];
    double r = log(radABC) / log(c);
    
    int idx = upper_bound(Rs.begin(), Rs.end(), r) - Rs.begin();
    update(idx, c);
}

int main() {
    clock_t t = clock();
    int triples = 0;
    
    int T;
    scanf("%d", &T);
    for (int i=0; i<T; i++) {
        double r; int l;
        scanf("%lf %d", &r, &l);
        queries.push_back({r, l});
        Rs.push_back(r);
    }
    
    sort(Rs.begin(), Rs.end());
    Rs.resize(unique(Rs.begin(), Rs.end()) - Rs.begin());
    for (int i=0; i<T; i++) {
        int idx = lower_bound(Rs.begin(), Rs.end(), queries[i].first) - Rs.begin();
        
        queryC[ queries[i].second-1 ].push_back({idx, i});
    }
    
    for (int i=1; i<N; i++) radical[i] = 1;
    for (int i=2; i<N; i++) if (radical[i] == 1) {
        for (int j=i; j<N; j+=i) radical[j] *= i;
    }
    
    for (int i=1; i<N; i++) {
        radicals[i].first = radical[i];
        radicals[i].second = i;
    }
    sort(radicals + 1, radicals + N);
    
    vector<int> Bs;
    for (int i=2; i<N; i*=2) Bs.push_back(i);
    for (int i=3; i<N; i*=3) Bs.push_back(i);
    for (int i=5; i<N; i*=5) Bs.push_back(i);
    for (int i=2; i<N; i*=2) for (int j=3; i*j<N; j*=3) Bs.push_back(i*j);
    for (int i=7; i<N; i*=7) Bs.push_back(i);
    for (int i=2; i<N; i*=2) for (int j=5; i*j<N; j*=5) Bs.push_back(i*j);
    for (int i=11; i<N; i*=11) Bs.push_back(i);
    for (int i=13; i<N; i*=13) Bs.push_back(i);
    sort(Bs.begin(), Bs.end(), greater<int>());
    
    for (int c=3; c<N; c++) {
        Double maksCR = pow(c, 1.5);
        
        for (int j=1; j < N && radicals[j].first * 14LL * radical[c] < maksCR; j++) {
            int a = radicals[j].second;
            int b = c - a;
            if (radical[b] < 14) continue;
            
            if (a >= b) continue;
            if (1LL * radical[a] * radical[b] * radical[c] >= maksCR) continue;
            if (__gcd(a, b) > 1) continue;
            
            add(a, b, c);
            
            ++triples;
        }
        
        for (int b: Bs) {
            int a = c - b;
            if (a >= b) break;
            
            if (a <= 0) continue;
            if (1LL * radical[a] * radical[b] * radical[c] >= maksCR) continue;
            if (__gcd(a, b) > 1) continue;
            
            add(a, b, c);
            
            ++triples;
        }
        
        for (int i=0; i<queryC[c].size(); i++) {
            ans[ queryC[c][i].second ] = query(queryC[c][i].first);
        }
    }
    
    for (int i=0; i<T; i++)
        printf("%lld\n", ans[i]);
    
    fprintf(stderr, "%lf sec\n%d\n", (double) (clock() - t) / CLOCKS_PER_SEC, triples);
    
    return 0;
}
