#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000007;

int n;
int sum[1<<20];
int cnt[1<<20];
bool vis[1<<20];

struct Puzzle {
  int empty;
  int mask;

  Puzzle() {
    empty = -1; mask = 0;
  }

  int getIdx() {
    return mask*n*n + empty;
  }
};

bool canMove(const Puzzle &puzzle, int dir) {
  if (dir == 0) {
    return puzzle.empty % n < n-1;
  }

  if (dir == 1) {
    return puzzle.empty % n > 0;
  }

  if (dir == 2) {
    return puzzle.empty < n*n - n;
  }

  if (dir == 3) {
    return puzzle.empty >= n;
  }

  return false;
}

int code[4] = {'L', 'R', 'U', 'D'};

Puzzle move(Puzzle puzzle, int dir) {
  int npos = -1;
  if (dir == 0) {
    npos = puzzle.empty + 1;
  } else if (dir == 1) {
    npos = puzzle.empty - 1;
  } else if (dir == 2) {
    npos = puzzle.empty + n;
  } else if (dir == 3) {
    npos = puzzle.empty - n;
  }

  puzzle.mask &= ~(1 << puzzle.empty);
  puzzle.mask |= (puzzle.mask >> npos & 1) << puzzle.empty;
  puzzle.mask &= ~(1 << npos);
  puzzle.empty = npos;

  return puzzle;
}

Puzzle readPuzzle() {
  Puzzle ret;
  for (int i = 0; i < n; ++i) {
    char s[n+1];
    scanf("%s", s);
    for (int j = 0; j < n; ++j) {
      if (s[j] == 'W') {
        ret.empty = i*n + j;
      } else if (s[j] == 'B') {
        ret.mask |= 1 << i*n + j;
      }
    }
  }

  return ret;
}

int main() {
  scanf("%d", &n);

  Puzzle st = readPuzzle();
  Puzzle en = readPuzzle();

  cnt[st.getIdx()] = 1;

  queue<Puzzle> q;
  q.push(st);

  while (q.size()) {
    Puzzle u = q.front();
    q.pop();

    if (u.getIdx() == en.getIdx()) break;
    if (vis[u.getIdx()]) continue;
    vis[u.getIdx()] = true;

    for (int i = 0; i < 4; ++i) {
      if (!canMove(u, i)) continue;
      
      Puzzle v = move(u, i);
      if (vis[v.getIdx()]) continue;

      q.push(v);

      int uval = u.getIdx(), vval = v.getIdx();
      sum[vval] = (243LL * sum[uval] + 1LL * code[i] * cnt[uval] + sum[vval]) % MOD;
      cnt[vval] = (cnt[vval] + cnt[uval]) % MOD;
    }
  }

  printf("%d\n", sum[en.getIdx()]);
  return 0;
}
