/**
 * Find all possible triangles of ACD and its origin by brute-forcing angle DAC, DCA, and DOC.
 * Do a meet-in-the-middle for all these triangles by having the length of AO + OC = 1.
 * Non-similar quadrangles are checked by rotating and mirroring the acquired angles.
 */

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = 3.1415926535897932384626433;

double cosd[188];
double sind[188];

vector<vector<int>> angles;

int main() {
    clock_t t = clock();
    
    for (int i=0; i<=180; i++) {
        cosd[i] = cos(i * PI / 180);
        sind[i] = sin(i * PI / 180);
    }
    
    int sorted[8];
    
    int cnt = 0;
    for (int c=1; c<=90; c++) {
        vector<pair<double, pair<int, int>>> v;
        for (int a=1; a<c; a++) {
            for (int b=1; b<180-c; b++) {
                double s = sind[b] * sind[c-a] / sind[a+b] / sind[c];
                v.push_back({s, {a, b}});
            }
        }
        sort(v.begin(), v.end());
        
        for (int i=0; i<v.size(); i++) {
            double s = v[i].first;
            int a = v[i].second.first;
            int b = v[i].second.second;
            // if (s > 0.5 + EPS) continue;
            
            pair<double, pair<int, int>> key = {1 - s - EPS, {-1, -1}};
            int l = lower_bound(v.begin(), v.end(), key) - v.begin();
            key.first += EPS * 2;
            int r = lower_bound(v.begin(), v.end(), key) - v.begin();
            
            for (int j=l; j<r; j++) {
                int d = v[j].second.first;
                int e = v[j].second.second;
                
                // Some optimizations.
                if (d > a) continue;
                if (d == a && e > b) continue;
                
                vector<int> sorted = {a, c-a, 180-c-b, b, d, c-d, 180-c-e, e};
                vector<int> mini = sorted;
                
                for (int i=0; i<3; i++) {
                    rotate(sorted.begin(), sorted.begin() + 2, sorted.end());
                    if (sorted < mini) mini = sorted;
                }
                reverse(sorted.begin(), sorted.end());
                for (int i=0; i<4; i++) {
                    rotate(sorted.begin(), sorted.begin() + 2, sorted.end());
                    if (sorted < mini) mini = sorted;
                }
                
                angles.push_back(mini);
            }
        }
    }
    
    sort(angles.begin(), angles.end());
    angles.resize(unique(angles.begin(), angles.end()) - angles.begin());
    
    cerr << angles.size() << endl;
    
    int b[8];
    for (int i=0; i<8; i++) scanf("%d", b + i);
    
    int ans = 0;
    for (int i=0; i<angles.size(); i++) {
        sort(angles[i].begin(), angles[i].end());
        
        bool ok = 1;
        for (int j=0; j<8; j++) if (angles[i][j] > b[j]) {
            ok = 0;
            break;
        }
        ans += ok;
    }
    
    printf("%d\n", ans);
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
