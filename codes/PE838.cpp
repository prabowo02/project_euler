// If n is prime, then it must be part of the answer
// Let A = product(prime < N that ends with 3)
// Let's factorize n (ended with 3) that is still coprime with A, and find its prime factors
// Primes can only end with 1, 3, 7, 9 (2, 5 are ignored because it would make n not ends with 3)
// There can't be a prime factor that ends with 3 because then it wouldn't be coprime with A
// Suppose there is a prime factor that ends with 1
//   then if we exclude this prime factor, the number still ends with 3
//   and therefore has been handled by the smaller case
// Suppose there are two prime factors that ends with 9
//   But 9*9 % 10 = 1 and hence can be excluded as well
//   Therefore we consider only number with at most one prime factor ending with 9
// Similarly, we can exclude numbers with four prime factors ending with 7
// But we can't have exactly two prime factors ending with 7, since both 7*7 and 7*7*9 are not ending with 3
// Hence we only need to care numbers with prime factors ending with either (7, 9), (9, 7), or (7, 7, 7)
// For the (7, 7, 7) case, we only need to consider numbers of the form p^3, because the case for p*q*r (p <= q <= r) has been handled by p^3
//   Therefore p must be included in A
// 
// Hence we end with a weighted min-vertex cover on bipartite graph.
//   Apply konig's theorem and the answer is the max flow


#include <bits/stdc++.h>
using namespace std;

const int NN = 5000;
const double INF = 1e9;

struct Dinic {
  int s, t;
  vector<int> edges[NN], rev[NN];
  vector<double> cap[NN];
  int dist[NN], it[NN];
  
  void addEdge(int u, int v, double c) {
    if (u == v) return;
    
    rev[u].push_back(edges[v].size());
    cap[u].push_back(c);
    edges[u].push_back(v);
    
    rev[v].push_back((int) edges[u].size() - 1);
    cap[v].push_back(0);
    edges[v].push_back(u);
  }
  
  bool bfs() {
    queue<int> q;
    q.push(s);
    
    for (int i = 0; i <= t; ++i) dist[i] = -1;
    dist[s] = 0;
    
    while (q.size()) {
      int u = q.front();
      q.pop();
      
      for (int i = 0; i < edges[u].size(); ++i) {
        int v = edges[u][i];
        double c = cap[u][i];
        if (dist[v] >= 0 || fabs(c) < 1e-6) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    
    return dist[t] >= 0;
  }
  
  double dfs(int u, double f) {
    if (u == t) return f;
    for (; it[u] < edges[u].size(); ++it[u]) {
      int i = it[u];
      int v = edges[u][i];
      double c = cap[u][i];
      if (dist[v] == dist[u] + 1 && c > 0) {
        double flow = dfs(v, min(f, c));
        if (flow > 0) {
          cap[u][i] -= flow;
          cap[v][rev[u][i]] += flow;
          return flow;
        }
      }
    }
    
    return 0;
  }
  
  double maxflow() {
    double ret = 0;
    while (bfs()) {
      for (int i = 0; i <= t; ++i) it[i] = 0;
      while (double flow = dfs(s, INF)) {
        if (fabs(flow) < 1e-6) break;
        ret += flow;
      }
    }
    
    return ret;
  }
} dinic;


vector<int> primeFactors(int n) {
  vector<int> ret;
  for (int p = 3; p*p <= n; p += 2) {
    while (n % p == 0) {
      ret.push_back(p);
      n /= p;
    }
  }
  if (n > 1) ret.push_back(n);
  return ret;
}

int main() {
  int N = 1000000;
  scanf("%d", &N);

  vector<int> comp79;
  for (int p = 7; p <= N; p += 2) {
    if (p % 10 != 7 && p % 10 != 9) continue;
    if (p % 10 == 7 && p * 19 > N) continue;
    if (p % 10 == 9 && p * 7 > N) continue;
    if (primeFactors(p).size() == 1) {
      comp79.push_back(p);
    }
  }
  sort(comp79.begin(), comp79.end());

  dinic.s = comp79.size();
  dinic.t = dinic.s + 1;
  for (int i = 0; i < comp79.size(); ++i) {
    int p = comp79[i];
    if (p % 10 == 7) dinic.addEdge(dinic.s, i, log(p));
    else dinic.addEdge(i, dinic.t, log(p));
  }

  double ans = 0;
  set<int> sevens;
  for (int n = 3; n <= N; n += 10) {
    vector<int> ps = primeFactors(n);
    if (ps.size() == 3 && ps[0] % 10 == 7 && ps[1] == ps[0] && ps[2] == ps[0]) {
      sevens.insert(ps[0]);
      ans += log(ps[0]);
    } else if (ps.size() == 1) {
      ans += log(ps[0]);
    }
  }
  for (int n = 3; n <= N; n += 10) {
    vector<int> ps = primeFactors(n);
    if (ps.size() == 2 && ((ps[0] % 10 == 9 && ps[1] % 10 == 7) || (ps[0] % 10 == 7 && ps[1] % 10 == 9))) {
      int seven = ps[0];
      int nine = ps[1];
      if (seven % 10 != 7) swap(seven, nine);
      if (sevens.find(seven) == sevens.end()) {
        // cerr << seven << " " << nine << endl;
        dinic.addEdge(
          lower_bound(comp79.begin(), comp79.end(), seven) - comp79.begin(),
          lower_bound(comp79.begin(), comp79.end(), nine) - comp79.begin(),
          INF
        );
      }
    }
  }
  // cerr << dinic.maxflow() << endl;
  ans += dinic.maxflow();

  // Retrieve the product
  // for (int i = 0; i < dinic.edges[dinic.s].size(); ++i) {
  //   int j = dinic.edges[dinic.s][i];
  //   if (dinic.dist[j] == -1) cerr << comp79[j] << " ";
  // }
  // for (int i = 0; i < dinic.edges[dinic.t].size(); ++i) {
  //   int j = dinic.edges[dinic.t][i];
  //   if (dinic.dist[j] != -1) cerr << comp79[j] << " ";
  // }
  // cerr << endl;

  printf("%.06lf\n", ans);
  return 0;
}
