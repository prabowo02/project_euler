#include <bits/stdc++.h>
using namespace std;

int t;
int N[6];

int ngon(int n, int k) {
  return k * ((n - 2) * k - (n - 4)) >> 1;
}

vector <int> polygon[10];

vector < vector<int> > ans;
void solve (vector <int> &v, int mask) {
  if (mask == (1 << t) - 1) {
    if (v[0] / 100 == v.back() % 100) {
      ans.push_back(v);
      sort (ans.back().begin(), ans.back().end());
      if (unique(ans.back().begin(), ans.back().end()) - ans.back().begin() != ans.back().size()) ans.pop_back();
    }
    return;
  }
  
  for (int i=0; i<t; i++) {
    if (mask >> i & 1) continue;
    for (int j=0; j<polygon[N[i]].size(); j++) {
      if (v.size() && v.back() % 100 != polygon[N[i]][j] / 100) continue;
      v.push_back(polygon[N[i]][j]);
      solve(v, mask | 1 << i);
      v.pop_back();
    }
  }
}

int main () {

  for (int i=3; i<=8; i++) {
    for (int j=1; ngon(i, j)<10000; j++) {
      if (ngon(i, j) >= 1000) polygon[i].push_back(ngon(i, j));
    }
  } 
  
  scanf ("%d", &t);
  for (int i=0; i<t; i++) scanf ("%d", N + i);
  
  vector <int> tmp;
  solve(tmp, 0);
  
  sort (ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  
  vector <int> sum;
  for (int i=0; i<ans.size(); i++) {
    int tmp = 0;
    for (int j=0; j<t; j++) tmp += ans[i][j];
    sum.push_back(tmp);
  }
  
  sort (sum.begin(), sum.end());
  for (int i=0; i<sum.size(); i++) printf ("%d\n", sum[i]);
  
  return 0;
}
