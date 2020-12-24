#include <bits/stdc++.h>
using namespace std;

const int N = 64;

int n;
vector<int> edges[N];

long long bfs(int u, long long vertices) {
    long long vis = 1LL << u;
    queue<int> q;
    q.push(u);

    while (q.size()) {
        int u = q.front();
        q.pop();

        for (int v: edges[u]) {
            if (vertices >> v & 1); else continue;
            if (vis >> v & 1) continue;

            q.push(v);
            vis |= 1LL << v;
        }
    }

    return vis;
}

int count_small_vertex_cover(long long vertices) {
    vector<int> cvertex;
    for (int i=0; i<n; i++) if (vertices >> i & 1) cvertex.push_back(i);

    vector<pair<int, int>> es;
    for (int i=0; i<n; i++) if (vertices >> i & 1) for (int j: edges[i]) if (vertices >> j & 1) {
        if (i < j) es.push_back({
            lower_bound(cvertex.begin(), cvertex.end(), i) - cvertex.begin(),
            lower_bound(cvertex.begin(), cvertex.end(), j) - cvertex.begin()
        });
    }

    int ret = 0;
    for (int i=1; i<1<<cvertex.size(); i++) {
        bool is_cover = true;
        for (pair<int, int> e: es) {
            int u = e.first, v = e.second;
            if (!(i >> u & 1) && !(i >> v & 1)) {
                is_cover = false;
                break;
            }
        }
        if (is_cover) ++ret;
    }

    return ret;
}

map<long long, unsigned long long> dp;
unsigned long long count_vertex_cover(long long vertices) {
    if (__builtin_popcountll(vertices) == 0) return 1;
    if (__builtin_popcountll(vertices) == 1) return 2;


    if (dp.find(vertices) != dp.end()) return dp[vertices];

    vector<long long> components;
    long long vis = 0;
    for (int i=0; i<n; i++) {
        if (vertices >> i & 1); else continue;
        if (vis >> i & 1) continue;

        components.push_back(bfs(i, vertices));
        vis |= components.back();
    }

    if (components.size() > 1) {
        unsigned long long ret = 1;
        for (long long component: components) {
            ret *= count_vertex_cover(component);
        }

        return dp[vertices] = ret;
    }

    // if (__builtin_popcountll(vertices) <= 8) return dp[vertices] = count_small_vertex_cover(vertices);

    int max_degree = -1;
    vector<int> heavy_vertices;

    for (int i=0; i<n; i++) {
        if (vertices >> i & 1); else continue;

        int degree = 0;
        for (int v: edges[i]) {
            if (vertices >> v & 1) ++degree;
        }

        if (degree > max_degree) {
            heavy_vertices = {i};
            max_degree = degree;
        } else if (degree == max_degree) {
            heavy_vertices.push_back(i);
        }
    }

    int heavy = heavy_vertices[rand() % heavy_vertices.size()];
    long long neighbor = 1LL << heavy;
    for (int v: edges[heavy]) if (vertices >> v & 1) neighbor |= 1LL << v;

    return dp[vertices] = 
        count_vertex_cover(vertices & ~(1LL << heavy)) + // heavy is in vertex_cover
        count_vertex_cover(vertices & ~neighbor); // heavy is not in vertex_cover
}

void simplify_edges(vector<int> edges[]) {
    vector<pair<int, int>> unique_edges;

    for (int i=0; i<n; i++) {
        for (int j: edges[i]) {
            if (i < j) unique_edges.push_back({i, j});
        }
        edges[i].clear();
    }

    sort(unique_edges.begin(), unique_edges.end());
    unique_edges.resize(unique(unique_edges.begin(), unique_edges.end()) - unique_edges.begin());

    for (pair<int, int> edge: unique_edges) {
        edges[edge.first].push_back(edge.second);
        edges[edge.second].push_back(edge.first);
    }
}

void test() {
    n = 64;
    vector<pair<int, int>> v = {{0, 1}, {0, 16}, {1, 2}, {1, 17}, {2, 3}, {2, 18}, {3, 4}, {3, 19}, {4, 5}, {4, 20}, {5, 6}, {5, 21}, {6, 7}, {6, 22}, {7, 8}, {7, 23}, {8, 9}, {8, 24}, {9, 10}, {9, 25}, {10, 11}, {10, 26}, {11, 12}, {11, 27}, {12, 13}, {12, 28}, {13, 14}, {13, 29}, {14, 15}, {14, 30}, {15, 16}, {15, 31}, {16, 17}, {16, 0}, {17, 18}, {17, 1}, {18, 19}, {18, 2}, {19, 20}, {19, 3}, {20, 21}, {20, 4}, {21, 22}, {21, 5}, {22, 23}, {22, 6}, {23, 24}, {23, 7}, {24, 25}, {24, 8}, {25, 26}, {25, 9}, {26, 27}, {26, 10}, {27, 28}, {27, 11}, {28, 29}, {28, 12}, {29, 30}, {29, 13}, {30, 31}, {30, 14}, {31, 0}, {31, 15}, };

    for (pair<int, int> edge: v) {
        int u = edge.first;
        int v = edge.second;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    simplify_edges(edges);

    clock_t t = clock();
    cout << count_vertex_cover(n < 64 ? (1LL << n) - 1 : -1) << '\n';
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
}

vector<int> parse(char *s) {
    int n = strlen(s);
    s[n++] = '+';
    vector<int> ret;

    int num = 0;
    for (int i=0; i<n; i++) {
        if (s[i] == '+') {
            ret.push_back(num);
            num = 0;
        } else if (s[i] == '0') {
            ++i;
        } else if (s[i] == 'a') {
            num |= 1 << (s[++i] - '1');
        }
    }

    return ret;
}

int compute(vector<int> &formula, int input) {
    if (input == 0) {
        for (int summand: formula) {
            if (summand == 0) return 1;
        }
        return 0;
    }
    int ret = 0;
    for (int summand: formula) {
        if ((summand & input) == summand) ret ^= 1;
    }
    return ret;
}

char s[606];
vector<int> formula_f[6], formula_g[6];
void solve() {
    int n;
    scanf("%d", &n);
    ::n = 1 << n;

    for (int i=0; i<n; i++) {
        scanf("%s", s);
        formula_f[i] = parse(s);
    }

    for (int i=0; i<n; i++) {
        scanf("%s", s);
        formula_g[i] = parse(s);
    }

    for (int i=0; i<1<<n; i++) {
        edges[i].clear();
    }

    long long vertices = (n < 6 ? (1LL << (1LL << n)) - 1 : -1);
    for (int i=0; i<1<<n; i++) {
        int u = 0, v = 0;
        for (int j=0; j<n; j++) {
            u <<= 1, v <<= 1;
            u |= compute(formula_f[j], i);
            v |= compute(formula_g[j], i);
        }

        if (u == v) {
            vertices &= ~(1LL << u);
        } else {
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
    }
    simplify_edges(edges);

    dp.clear();
    cout << count_vertex_cover(vertices) << '\n';
}

void PE209() {
    int q;
    scanf("%d", &q);
    while (q--) {
        solve();
    }
}

int main() {
    // test();
    PE209();
    return 0;
}
