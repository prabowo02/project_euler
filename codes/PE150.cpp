#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    vector <vector<int>> v;
    for (int i=0; i<n; i++) {
        v.push_back(vector<int>(i+1));
        for (int j=0; j<=i; j++)
            scanf("%d", &v[i][j]);
        
        for (int j=1; j<v[i].size(); j++) v[i][j] += v[i][j-1];
    }

    vector<long long> ans;
    for (int i=0; i<n; i++) {        
        for (int j=0; j<=i; j++) {
            long long tmp = 0;
            for (int k=i; k<n; k++) {
                tmp += v[k][j + (k - i)] - (j ? v[k][j-1] : 0);
                ans.push_back(tmp);
            }
        }
    }

    sort(ans.begin(), ans.end());
    for (int i=0; i<k; i++)
        printf("%lld\n", ans[i]);

    return 0;
}
