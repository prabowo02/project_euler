#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 10000000;

int phi[N];

int main() {
    /*
    for (int i=1; i<N; i++) phi[i] = i;
    for (int i=2; i<N; i++) if (i == phi[i]) for (int j=i; j<N; j+=i) phi[j] = phi[j] / i * (i - 1);
    
    int n; scanf ("%d", &n);
    int ans = 21; 
    for (int i=6018162; i<n; i++) {
        string s = to_string(i);
        string t = to_string(phi[i]);
        
        sort (s.begin(), s.end());
        sort (t.begin(), t.end());
        
        if (s != t) continue;
        
        if (1LL * i * phi[ans] < 1LL * ans * phi[i]) cout << (ans = i) << endl;
    }
    printf ("%d\n", ans);
    return 0;
    */
    
    int ans[] = {291, 2817, 2991, 4435, 20617, 45421, 69271, 75841, 162619, 176569, 284029, 400399, 474883, 732031, 778669, 783169, 1014109, 1288663, 1504051, 1514419, 1924891, 1956103, 2006737, 2044501, 2094901, 2239261, 2710627, 2868469, 3582907, 3689251, 4198273, 4696009, 5050429, 5380657, 5886817, 6018163, 6636841, 7026037, 7357291, 7507321, 8316907, 8319823};
    
    int n; scanf ("%d", &n);
    int now = 21;
    for (int a: ans) {
        if (a < n) now = a;
        else break;
    }
    return 0 * printf ("%d\n", now); 
}
