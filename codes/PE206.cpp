#include <bits/stdc++.h>
using namespace std;

int a[20];

long long num[2][15000000];

vector<int> mapping[100][100][10];

std::ostream& operator << ( std::ostream& os, __int128 value ) {
    if (value < 0) {
        os << "-";
        value = -value;
    }
    
    vector<int> v;
    while (value > 0) {
        v.push_back(value % 10);
        value /= 10;
    }
    if (v.size() == 0) v.push_back(0);
    reverse(v.begin(), v.end());
    for (int d: v) os << d; 
    return os;
}

int main() {
    clock_t t = clock();
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++) scanf("%d", a + i);
    
    __int128 maks = a[0];
    for (int i=1; i<n; i++) {
        maks = maks * 100 + 90 + a[i];
    }
    
    int len[2] = {0, 0};
    for (int i=0; i<1000; i++) {
        if (i*i % 10 == a[n-1] && i*i / 100 % 10 == a[n-2]) {
            num[1][len[1]++] = i;
        }
    }
    
    for (int i=0; i<100; i++) {
        for (int j=0; j<50; j++) {
            for (int k=0; k<100; k++) {
                mapping[i][j*2][(i + j*2*k) / 10 % 10].push_back(k);
            }
        }
    }
    
    // for (int i=0; i<10; i++) if (i*i % 10 == a[n-1]) num[0][len[0]++] = i;
    __int128 mul = 10;
    for (int i=2; i<n; i++) {
        mul *= 100;
        int dig = a[n-i-1];
        len[i&1] = 0;
        for (int j=0; j<len[i+1&1]; j++) {
            __int128 cur = num[i+1&1][j];
            int hundred = cur*cur / mul % 100;
            int ten = num[i+1&1][j] * 2 % 100;
            for (int k: mapping[hundred][ten][dig]) {
                __int128 tmp = mul * k + cur;  
                if (tmp*tmp > maks || tmp > 1000000000000000000LL) break;
                // if (tmp*tmp / (mul * 10) % 10 == dig) {
                num[i&1][len[i&1]++] = tmp;
                // }
            }
            
        }
    }
    
    cout << num[n+1&1][0] << endl;
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
