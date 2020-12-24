#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 6000006;

int t;
bool prime[N];

int subtask1() {
    vector<int> primes1, primes2, primes3;
    primes1.push_back(4);
    primes2.push_back(16);
    memset(prime, 1, sizeof prime); prime[1] = prime[0] = 0;
    for (int i=2; i<N; i++) if (prime[i]) {        
        for (int j=i*2; j<N; j+=i) prime[j] = 0;        
        if (i & 1) primes1.push_back(i * 4);
        if (i & 1) primes2.push_back(i * 16);
        if ((i & 3) == 3) primes3.push_back(i);        
    }    
    
    int L, R;
    while(t--) {
        scanf("%d %d", &L, &R);                
        printf("%d\n", 
              (upper_bound(primes1.begin(), primes1.end(), R) - lower_bound(primes1.begin(), primes1.end(), L)) +
              (upper_bound(primes2.begin(), primes2.end(), R) - lower_bound(primes2.begin(), primes2.end(), L)) +
              (upper_bound(primes3.begin(), primes3.end(), R) - lower_bound(primes3.begin(), primes3.end(), L))              
        );        
    }
    
    return 0;
}

void subtask2() {
    long long L, R;
    scanf("%lld %lld", &L, &R);
    
    int n = R - L + 1;
    bool prime2[n]; for (int i=0; i<n; i++) prime2[i] = 1;
    
    for (long long i=0; i*i<=R; i++) prime[i] = 1;
    for (long long i=2; i*i<=R; i++) if (prime[i]) {
        for (long long j=i*2; j*j<=R; j+=i) prime[j] = 0;
        long long j = L / i * i; if (j < L) j += i; if (j == i) j += i;
        for(; j<=R; j+=i) prime2[j-L] = 0;
    }
    
    int ans = 0;
    for(long long i=L; i<=R; i++) if (prime2[i-L]) 
        if ((i & 3) == 3) ans++;
    
    n = (R >> 2) - (L >> 2) + 1;
    for (int i=0; i<n; i++) prime2[i] = 1;
    
    for (long long i=0; i*i<=R>>2; i++) prime[i] = 1;
    for (long long i=2; i*i<=R>>2; i++) if (prime[i]) {
        for (long long j=i*2; j*j<=R>>2; j+=i) prime[j] = 0;
        long long j = (L >> 2) / i * i; if (j < L >> 2) j += i; while (j <= i) j += i;
        for(; j<=R>>2; j+=i) prime2[j-(L>>2)] = 0;
    }
    
    for (long long i=L>>2; i<=R>>2; i++) if (prime2[i-(L>>2)] && (i & 1)) {
        if (i << 2 >= L) ans++;
    }
    
    n = (R >> 4) - (L >> 4) + 1;
    for (int i=0; i<n; i++) prime2[i] = 1;
    
    for (long long i=0; i*i<=R>>4; i++) prime[i] = 1;
    for (long long i=2; i*i<=R>>4; i++) if (prime[i]) {
        for (long long j=i*2; j*j<=R>>4; j+=i) prime[j] = 0;
        long long j = (L >> 4) / i * i; if (j < L >> 4) j += i; while (j <= i) j += i;
        for(; j<=R>>4; j+=i) prime2[j-(L>>4)] = 0;
    }
    
    for (long long i=L>>4; i<=R>>4; i++) if (prime2[i-(L>>4)] && (i & 1)) {
        if (i << 4 >= L) ans++;
    }
    
    printf("%d\n", ans);        
    return;
}

int main() {
    scanf("%d", &t); 
    if (t > 10) subtask1();
    else while(t--) subtask2();
    return 0;
}
