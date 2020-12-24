#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// mathworld.wolfram.com
// Schmerl and Spiegel (1994) proved that Ulam sequences (2,v) for odd v>=5 have exactly two even terms. 

// http://oeis.org/A100729
int period[] = {0, 0, 32, 26, 444, 1628, 5906, 80, 126960, 380882, 2097152};

// http://oeis.org/A100730
int diff[] = {0, 0, 126, 126, 1778, 6510, 23622, 510, 507842, 1523526, 8388606};

// U(2, 2n+1)_k = U(2, 2n+1)_{k - period[n]} + diff[n], for n > some_constant

int main() {
    int n; long long k;
    scanf("%d %lld", &n, &k);
    
    int even = n+1 << 2;
    
    vector<int> ulams = {0, 2, 2*n + 1};
    while (ulams.back() + 2 < even) ulams.push_back(ulams.back() + 2);
    ulams.push_back(even); int st = (int) ulams.size();
    ulams.push_back(even + 1);
    
    int idx = 2; 
    while (ulams.size() < period[n] + st) {
        if (ulams.back() + 2 < ulams[idx] + even) {
            ulams.push_back(ulams.back() + 2);
        } else if (ulams.back() + 2 > ulams[idx] + even) {
            ulams.push_back(ulams[idx++] + even);
            if (ulams[idx] % 2 == 0) idx++;
        } else {
            idx++; if (ulams[idx] % 2 == 0) idx++;
            ulams.push_back(ulams[idx++] + even);
            if (ulams[idx] % 2 == 0) idx++;
            continue;
        }        
    }
    
    // for (int ulam: ulams) cerr << ulam << endl;
    
    if (k < period[n] + st) printf("%d\n", ulams[k]);
    else printf("%lld\n", max((k - st) / period[n], 0LL) * diff[n] + ulams[(k - st) % period[n] + st]);
        
    return 0;
}
