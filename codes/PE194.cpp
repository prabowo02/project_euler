#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int a, b, c;
vector<long long> A, B;

vector<pair<int, int>> positionsA, positionsB;
pair<int, int> leftA, rightA, leftB, rightB; // pair node

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  
  return ret;
}

inline pair<int, int> add(pair<int, int> a, pair<int, int> b) {
  return {a.first + b.first, a.second + b.second};
}

inline pair<int, int> subtract(pair<int, int> a, pair<int, int> b) {
  return {a.first - b.first, a.second - b.second};
}

void printEdges(vector<long long> &edges) {
  for (long long u: edges) cerr << (bitset<64>(u)) << endl;
}

vector<long long> contract_edge(vector<long long> edges, int u, int v) {
  // cerr << "Begin contract: " << u << " " << v << endl; printEdges(edges);
  
  int n = edges.size();
  
  edges[u] |= edges[v];
  for (int i=0; i<n; i++) edges[i] |= (edges[i] >> v & 1) << u;
  edges[u] &= ~(1LL << u);
  
  for (int i=0; i<n; i++) {
    edges[i] = (edges[i] & (1LL << v) - 1) | (edges[i] & ~((1LL << v+1) - 1)) >> 1;
  }
  
  for (int i=v+1; i<n; i++) edges[i-1] = edges[i];
  edges.pop_back();
  
  // cerr << endl; printEdges(edges); cerr << "End contract" << endl << endl;
  
  return edges;
}

vector<long long> delete_edge(vector<long long> edges, int u, int v) {
  // cerr << "Begin delete: " << u << " " << v << endl; printEdges(edges);
  edges[u] &= ~(1LL << v);
  edges[v] &= ~(1LL << u);
  // cerr << endl; printEdges(edges); cerr << "End delete" << endl << endl;
  
  return edges;
}

pair<int, int> chooseEdge(vector<long long> &edges) {
  pair<int, int> edge = {-1, -1};
  int maks = -1;
  for (int u=0; u<edges.size(); ++u) {
    for (int v=u+1; v<edges.size(); ++v) {
      if (edges[u] >> v & 1) {
        if (maks == -1 || __builtin_popcountll(edges[u]) + __builtin_popcountll(edges[v]) < maks) {
          maks = __builtin_popcountll(edges[u]) + __builtin_popcountll(edges[v]);
          edge = {u, v};
        }
      }
    }
  }
  
  return edge;
}

pair<int, int> suggestNonEdge = {-1, -1};
pair<int, int> chooseNonEdge(vector<long long> &edges) {
  return suggestNonEdge;
  
  pair<int, int> edge = {-1, -1};
  int maks = -1;
  for (int u=0; u<edges.size(); ++u) {
    for (int v=u+1; v<edges.size(); ++v) {
      if (edges[u] >> v & 1); else {
        if (maks == -1 || max(__builtin_popcountll(edges[u]), __builtin_popcountll(edges[v])) > maks) {
          maks = max(__builtin_popcountll(edges[u]), __builtin_popcountll(edges[v]));
          edge = {u, v};
        }
      }
    }
  }
  
  return edge;
}

vector<long long> keep_nodes(vector<long long> edges, vector<int> nodes) {
  for (int i=0; i<nodes.size(); i++) edges[i] = edges[nodes[i]];
  edges.resize(nodes.size());
  
  for (int i=0; i<edges.size(); i++) {
    for (int j=0; j<nodes.size(); ++j) {
      edges[i] = (edges[i] & ~(1LL << j)) | (edges[i] >> nodes[j] & 1) << j;
    }
    edges[i] &= (1LL << nodes.size()) - 1;
  }
  // cerr << "End keep nodes" << endl; printEdges(edges); cerr << endl;
  
  return edges;
}

vector<vector<int>> components(vector<long long> &edges) {
  // cerr << "Start components" << endl;
  
  vector<bool> vis(edges.size(), false);
  vector<vector<int>> ret;
  
  for (int i=0; i<edges.size(); i++) {
    if (vis[i]) continue;
    
    queue<int> q;
    q.push(i);
    vis[i] = true;
    
    vector<int> component;
    
    while (q.size()) {
      int u = q.front();
      q.pop();
      
      component.push_back(u);
      
      for (int v=0; v<edges.size(); ++v) {
        if (edges[u] >> v & 1) {
          if (vis[v]) continue;
          vis[v] = true;
          q.push(v);
        }
      }
    }
    
    sort(component.begin(), component.end());
    
    ret.push_back(component);
  }
  // cerr << "End components: " << ret.size() << endl;
  
  return ret;
}

inline vector<pair<pair<int, int>, pair<int, int>>> generateEdges(const vector<long long> &A, 
    const vector<pair<int, int>> &positions, pair<int, int> left, pair<int, int> right, int steps) {
  // generate edge list of the graph
  vector<pair<pair<int, int>, pair<int, int>>> initial;
  pair<int, int> leftmost = min(positions[left.first], positions[left.second]);

  for (int i = 0; i < (int)A.size(); i++) {
    for (int j = 0; j < i; j++) {
      if ((A[i] >> j) & 1) {
        pair<int, int> u = positions[i];
        pair<int, int> v = positions[j];

        u = subtract(u, leftmost);
        v = subtract(v, leftmost);

        if (u > v) {
          initial.push_back({v, u});
        } else {
          initial.push_back({u, v});
        }
      }
    }
  }

  sort(initial.begin(), initial.end());
  initial.resize(unique(initial.begin(), initial.end()) - initial.begin());
  if (steps == 1) {
    return initial;
  }

  vector<pair<pair<int, int>, pair<int, int>>> edges;
  pair<int, int> translate = subtract(min(positions[right.first], positions[right.second]), leftmost);
  leftmost = {0, 0};
  while (steps--) {
    for (auto edge: initial) {
      edge.first = add(edge.first, leftmost);
      edge.second = add(edge.second, leftmost);
      edges.push_back(edge);
    }

    leftmost = add(leftmost, translate);
  }

  sort(edges.begin(), edges.end());
  edges.resize(unique(edges.begin(), edges.end()) - edges.begin());
  return edges;
}

// SmallestDivisor returns tuple of the graph, quotient for graph A, and quotient for graph B
tuple<vector<long long>, int, int> smallestDivisor(
    vector<long long> A, vector<pair<int, int>> positionsA, pair<int, int> leftA, pair<int, int> rightA, 
    vector<long long> B, vector<pair<int, int>> positionsB, pair<int, int> leftB, pair<int, int> rightB) {
  // Find a graph g such that g|A and g|B
  int widthA = positionsA[rightA.first].first - positionsA[leftA.first].first;
  int widthB = positionsB[rightB.first].first - positionsB[leftB.first].first;

  // Has assumption widthA >= 1 and widthB >= 1
  int d = __gcd(widthA, widthB);
  for (int shift = 1; shift <= d; shift++) {
    if (d % shift != 0) {
      continue;
    }

    // Number of repetition for graph A and B
    int numA = widthA / shift;
    int numB = widthB / shift;

    if ((positionsA[rightA.first].second - positionsA[leftA.first].second) % numA != 0
        || (positionsA[rightA.second].second - positionsA[leftA.second].second) % numA != 0) {
      continue;
    }

    vector<long long> unit = A;
    const vector<pair<int, int>> &unitPositions = positionsA;
    for (int u = 0; u < unit.size(); u++) {
      if (positionsA[u].first - positionsA[leftA.first].first > shift) {
        // Remove node u from graph
        unit[u] = 0;
        for (int v = 0; v < unit.size(); v++) {
          unit[v] &= ~(1 << u);
        }
      }
    }

    pair<int, int> unitLeft = leftA;
    pair<int, int> unitRight = {
      (positionsA[rightA.first].second - positionsA[leftA.first].second) / numA + positionsA[leftA.first].second,
      (positionsA[rightA.second].second - positionsA[leftA.second].second) / numA + positionsA[leftA.second].second
    };

    // Check unitRight in unit graph
    short vis = 0;
    for (int u = 0; u < unit.size(); u++) {
      if (unit[u] == 0) {
        continue;
      }

      if (unitPositions[u].first == shift + positionsA[leftA.first].first) {
        if (!(vis & 1) && unitPositions[u].second == unitRight.first) {
          vis |= 1;
          unitRight.first = u;
        }

        if (!((vis >> 1) & 1) && unitPositions[u].second == unitRight.second) {
          vis |= 2;
          unitRight.second = u;
        }
      }
    }

    if (vis != 3) {
      continue;
    }

    auto unitToA = generateEdges(unit, unitPositions, unitLeft, unitRight, numA);
    auto edgesA = generateEdges(A, positionsA, leftA, rightA, 1);

    auto unitToB = generateEdges(unit, unitPositions, unitLeft, unitRight, numB);
    auto edgesB = generateEdges(B, positionsB, leftB, rightB, 1);

    if (unitToA == edgesA && unitToB == edgesB) {
      vector<int> nodes;
      for (int i=0; i<unit.size(); i++) {
        if (unit[i] != 0) nodes.push_back(i);
      }
      
      unit = keep_nodes(unit, nodes);
      return make_tuple(unit, numA, numB);
    }
  }

  return make_tuple(vector<long long>(), 0, 0);
}

int countEdges(vector<long long> &edges) {
  int ret = 0;
  for (int i=0; i<edges.size(); i++) ret += __builtin_popcountll(edges[i]);
  return ret / 2;
}

vector<int> lexBfs(vector<long long> &edges) {
  int n = edges.size();
  int current_label[n];
  set<pair<long long, int>> s;
  long long vis = 0;
  
  for (int i=0; i<n; i++) {
    current_label[i] = 0;
    s.insert({0, i});
  }
  
  vector<int> ret;
  for (int i=0; i<n; i++) {
    int u = -1;
    long long label;
    do {
      label = s.rbegin()->first;
      u = s.rbegin()->second;
      s.erase({label, u});
    } while ((vis >> u & 1) || label != current_label[u]);
    
    vis |= 1LL << u;
    // cerr << "Lex " << i << " " << u << endl;
    ret.push_back(u);
    
    for (int j=0; j<n; j++) {
      if (edges[i] >> j & 1); else continue;
      if (vis >> j & 1) continue;
      
      s.insert({current_label[j] |= 1LL << i, j});
    }
  }
  
  return ret;
}

int countColoringIfChordal(vector<long long> &edges) {
  vector<int> ordering = lexBfs(edges);
  long long vis = 0;
  
  int ret = 1;
  for (int u: ordering) {
    long long neighbors = edges[u] & vis;
    
    int cnt = 0;
    while (neighbors > 0) {
      int u = __builtin_ctzll(neighbors);
      neighbors -= 1LL << u;
      
      if ((edges[u] & neighbors) != neighbors) {
        int v = __builtin_ctzll((edges[u] & neighbors) ^ neighbors);
        suggestNonEdge = {u, v};
        return -1;
      }
      ++cnt;
    }
    
    vis |= 1LL << u;
    
    ret = 1LL * ret * (c - cnt) % MOD;
  }
  
  return ret;
}

vector<long long> addEdge(vector<long long> edges, int u, int v) {
  edges[u] |= 1LL << v;
  edges[v] |= 1LL << u;
  
  return edges;
}

vector<long long> identifyEdge(vector<long long> edges, int u, int v) {
  int n = edges.size();
  
  edges[u] |= edges[v];
  for (int i=0; i<n; i++) edges[i] |= (edges[i] >> v & 1) << u;
  
  for (int i=0; i<n; i++) {
    edges[i] = (edges[i] & (1LL << v) - 1) | (edges[i] & ~((1LL << v+1) - 1)) >> 1;
  }
  
  for (int i=v+1; i<n; i++) edges[i-1] = edges[i];
  edges.pop_back();
  
  return edges;
}

map<vector<long long>, int> memo;
int countGraphColoring(vector<long long> edges) {
  // cerr << "Start count" << endl; printEdges(edges); cerr << endl;
  // Complete this function
  vector<vector<int>> comps = components(edges);
  
  if (comps.size() > 1) {
    long long ret = 1;
    for (int i=0; i<comps.size(); i++) {
      ret = ret * countGraphColoring(keep_nodes(edges, comps[i])) % MOD;
    }
    
    return ret;
  }
  
  int chordalCount = countColoringIfChordal(edges);
  if (chordalCount != -1) return chordalCount;
  
  if (memo.find(edges) != memo.end()) return memo[edges];
  
  pair<int, int> edge = chooseEdge(edges);
  
  return memo[edges] = (countGraphColoring(delete_edge(edges, edge.first, edge.second)) -
                        countGraphColoring(contract_edge(edges, edge.first, edge.second)) + MOD
                       ) % MOD;
}


/*
map<vector<long long>, int> memo;
int countGraphColoring(vector<long long> edges) {
  int chordalCount = countColoringIfChordal(edges);
  if (chordalCount != -1) return chordalCount;
  
  if (memo.find(edges) != memo.end()) return memo[edges];
  
  pair<int, int> edge = chooseNonEdge(edges);
  
  return memo[edges] = (countGraphColoring(addEdge(edges, edge.first, edge.second)) +
                        countGraphColoring(identifyEdge(edges, edge.first, edge.second))) % MOD;
}
*/

void readGraph(vector<long long> &A, vector<pair<int, int>> &positions, pair<int, int> &left, pair<int, int> &right) {
  int n, m;
  scanf("%d %d", &n, &m);
  
  int x, y;
  for (int i=0; i<n; i++) {
    scanf("%d %d", &x, &y);
    positions.push_back({x, y});
  }
  
  A = vector<long long>(n, 0);
  int u, v;
  for (int i=0; i<m; i++) {
    scanf("%d %d", &u, &v);
    --u, --v;
    
    A[u] |= 1LL << v;
    A[v] |= 1LL << u;
    if (i == 0) {
      if (positions[u] < positions[v]) {
        left = {u, v};
      } else {
        left = {v, u};
      }
    }

    if (i == 1) {
      if (positions[u] < positions[v]) {
        right = {u, v};
      } else {
        right = {v, u};
      }
    }
  }
}

void read() {
  scanf("%d %d %d", &a, &b, &c);
  readGraph(A, positionsA, leftA, rightA); 
  readGraph(B, positionsB, leftB, rightB);
}

int solve() {
  read();

  vector<long long> unit;
  int numA, numB;
  tie(unit, numA, numB) = smallestDivisor(A, positionsA, leftA, rightA, B, positionsB, leftB, rightB);
  
  int countA, countB;
  if (unit.size() == 0) {
    countA = countGraphColoring(A);
    countB = countGraphColoring(B);    
  } else {  
    a = a * numA + b * numB;
    b = 0;
    
    countA = countGraphColoring(unit);
    countB = 0;
  }

  int invC = 1LL * power(c, MOD-2) * power(c-1, MOD-2) % MOD;
  countA = 1LL * countA * invC % MOD;
  countB = 1LL * countB * invC % MOD;
  
  int result = 1LL * power(countA, a) * power(countB, b) % MOD;
  for (int i=0; i<a; i++) {
    result = 1LL * result * (a+b-i) % MOD;
    result = 1LL * result * power(i+1, MOD-2) % MOD;
  }
  
  result = 1LL * result * c * (c-1) % MOD;
  
  printf("%d\n", result);
  return 0;
}

int main() {
  clock_t t = clock();
  solve();
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}
