#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
  while (y) {
    int t = x;
    x = y;
    y = t % y;
  }
  return x;
}

vector<pair<int, int>> dp[10][10];
vector<pair<int, int>> eval(int l, int r) {
  if (l == r) return dp[l][l];
  if (dp[l][r].size() != 0) return dp[l][r];

  for (int i = l; i < r; ++i) {
    for (pair<int, int> num1 : eval(l, i)) for (pair<int, int> num2 : eval(i + 1, r)) {
      dp[l][r].emplace_back(num1.first * num2.second + num2.first * num1.second, num1.second * num2.second);
      dp[l][r].emplace_back(num1.first * num2.second - num2.first * num1.second, num1.second * num2.second);
      dp[l][r].emplace_back(num1.first * num2.first, num1.second * num2.second);
      if (num2.first != 0) dp[l][r].emplace_back(num1.first * num2.second, num1.second * num2.first);
    }
  }

  // normalize
  for (pair<int, int> &p : dp[l][r]) {
    if (p.second < 0) p.first *= -1, p.second *= -1;
    int g = gcd(abs(p.first), p.second);
    p.first /= g, p.second /= g;
  }

  sort(dp[l][r].begin(), dp[l][r].end());
  dp[l][r].resize(unique(dp[l][r].begin(), dp[l][r].end()) - dp[l][r].begin());

  return dp[l][r];
}

vector<int> ans;
void eval(const vector<int> &nums) {
  for (int i = 0; i < nums.size(); ++i) for (int j = i; j < nums.size(); ++j) {
    dp[i][j].clear();
  }
  for (int i = 0; i < nums.size(); ++i) dp[i][i] = {{nums[i], 1}};

  for (pair<int, int> num : eval(0, nums.size() - 1)) {
    if (num.first > 0 && num.first % num.second == 0) ans.push_back(num.first / num.second);
  }
}

void dfs(int x, int acc, vector<int> &nums) {
  if (x == 10) {
    if (acc == 0) {
      // for (int num : nums) cerr << num << " "; cerr << endl;
      eval(nums);
    }
    return;
  }

  acc = acc*10 + x;

  dfs(x + 1, acc, nums);
  nums.push_back(acc);
  dfs(x + 1, 0, nums);
  nums.pop_back();
}

int main() {
  vector<int> v;
  dfs(1, 0, v);
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

  long long sum = 0;
  for (int a : ans) sum += a;
  printf("%lld\n", sum);
  return 0;
}
