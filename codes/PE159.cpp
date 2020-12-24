#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int digitalRoot(int num) {
    if (num % 9 == 0) return 9;
    return num % 9;
}

const int N = 10000000;
long long mdrs[N+1];

void pre() {
    for (int i=2; i<=N; i++) {
        mdrs[i] = max(mdrs[i], 1LL * digitalRoot(i));
        for (int j=i*2; j<=N; j+=i) {
            if (j / i > i) break;
            mdrs[j] = max(mdrs[j], mdrs[i] + mdrs[j / i]);
        }
        
        // if (i <= 24) cerr << mdrs[i] << endl;        
    }
        
    for (int i=3; i<=N; i++) mdrs[i] += mdrs[i-1];
}

int main(){
    pre();
    
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        
        printf("%lld\n", mdrs[n]);
    }
    return 0;
}
