#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s;
    scanf ("%d %d", &n, &s);
    
    int a[n], b[n];
    int vis = 0;
    
    vector <string> ans;
    for (int i=0; i<1<<2*n; i++) {
        if (__builtin_popcount(i) ^ n) continue;
        
        int sum1 = 0;
        int sum2 = 0;
        int idx = 0;
        for (int j=0; j<2*n; j++) {
            if (i >> j & 1) {
                a[idx++] = j + 1;
                sum1 += j + 1;
            } else sum2 += j + 1;
        }
        
        if (sum1 * 2 + sum2 != n * s) continue;
                    
        do {
            vis = i;
            idx = 0;
            for (int j=1; j<n; j++) {
                int num = s - a[j] - a[j-1] - 1;
                if (vis >> num & 1) {
                    sort (a + j + 1, a + n, greater<int>());
                    break;
                }
                if (num < 0 || num >= n * 2) {
                    sort (a + j + 1, a + n, greater<int>());
                    break;
                }
                vis |= 1 << num;
                b[idx++] = num + 1;
            }
            
            int num = s - a[n-1] - a[0] - 1;
            if (vis >> num & 1) continue;
            if (num < 0 || num >= n * 2) continue;
            b[idx++] = num + 1;
            
            if (idx == n) {
                stringstream ss;
                
                int idx = 0;
                for (int i=1; i<n; i++) {
                    if (b[i] < b[idx]) {
                        idx = i;
                    }
                }
            
                for (int i=idx; i<n-1; i++) 
                    ss << b[i] << a[i] << a[i+1];
            
                ss << b[n-1] << a[n-1] << a[0];

                for (int i=0; i<idx; i++)
                    ss << b[i] << a[i] << a[i+1];
            
                ans.push_back(ss.str());
            }
        } while (next_permutation(a + 1, a + n));
    }

    sort(ans.begin(), ans.end());
    for (int i=0; i<ans.size(); i++)
        cout << ans[i] << '\n';
    return 0;
}
