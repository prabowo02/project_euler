#include <bits/stdc++.h>
using namespace std;

long long solve(vector<int> bowls) {
  set<pair<int, int>> intervals;
  auto insert = [&](pair<int, int> p) {
    auto it = intervals.lower_bound(p);
    if (it != intervals.end() && it ->first == p.second + 1) {
      p.second = it->second;
      intervals.erase(it);
    }

    it = intervals.lower_bound(p);
    if (it != intervals.begin()) {
      --it;
      if (it->second == p.first - 1) {
        p.first = it->first;
        intervals.erase(it);
      }
    }

    intervals.insert(p);
  };

  auto add = [&](int x) {
    auto it = intervals.lower_bound({x+1, x});
    if (it == intervals.begin()) {
      insert({x, x});
      return 0LL;
    }
    --it;
    if (it->second < x) {
      insert({x, x});
      return 0LL;
    }

    int l = it->first, r = it->second;
    intervals.erase(it);
    insert({l - 1, l + r - x - 1});
    insert({r + l - x + 1, r + 1});
    return 1LL * (x - l + 1) * (r - x + 1);
  };

  long long ret = 0;
  for (int i = 0; i < bowls.size(); ++i) {
    for (int j = 0; j < bowls[i]; ++j) {
      ret += add(i);
    }
  }

  return ret;
}

int main() {
  cout << solve({289, 145}) << endl;

  vector<int> bowls;
  int t = 123456;
  for (int i = 0; i < 1500; ++i) {
    if (t % 2 == 0) {
      t /= 2;
    } else {
      t = (t / 2) ^ 926252;
    }
    bowls.push_back((t % (1 << 11)) + 1);
  }
  cout << solve(bowls) << endl;
  return 0;
}
