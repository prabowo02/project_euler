/**
Let v_p(n) be the p-adic valuation of n
Lemma: For all prime p > sqrt(n), v_p(C(n, m)) <= 1

The elementary symmetric polynomial for all p > sqrt(n) and p | C(n, m) can be computed independently using Newton's identities.
Computing the k-th power sum can be done using "Lucy_Hedgehog"-algorithm for finding the sum of primes.
(https://math.stackexchange.com/questions/1378286/find-the-sum-of-all-primes-smaller-than-a-big-number/2283829)
The algorithm will give the sum of primes power k <= n, <= n/2, <= n/3, ...

After the computation above, the rest can be done using DP, with the base case when p > sqrt(n), we return the result from above.
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1000000000;
const int K = 15;
const int SN = sqrt(N) + 2;
const int MOD = 1004535809;

vector<vector<int>> coefficients = {
  {1},
  {1, 1},
  {1, 3, 2},
  {0, 1, 2, 1},
  {-1, 0, 10, 15, 6},
  {0, -1, 0, 5, 6, 2},  
  {1, 0, -7, 0, 21, 21,  6},  
  {0, 2, 0, -7, 0, 14, 12, 3},
  {-3, 0, 20, 0, -42, 0, 60, 45, 10},  
  {0, -3, 0, 10, 0, -14, 0, 15, 10, 2},  
  {5, 0, -33, 0, 66, 0, -66, 0, 55, 33, 6},  
  {0, 10, 0, -33, 0, 44, 0, -33, 0, 22, 12, 2},  
  {-691, 0, 4550, 0, -9009, 0, 8580, 0, -5005, 0, 2730, 1365, 210},
  {0, -691, 0, 2275, 0, -3003, 0, 2145, 0, -1001, 0, 455, 210, 30},
  {105, 0, -691, 0, 1365, 0, -1287, 0, 715, 0, -273, 0, 105, 45, 6},
  {0, 420, 0, -1382, 0, 1820, 0, -1287, 0, 572, 0, -182, 0, 60, 24, 3},
};

vector<int> denominators = {
  1, 2, 6, 4, 30, 12, 42, 24, 90, 20, 66, 24, 2730, 420, 90, 48,
};

vector<int> denominators_inverse = {
  1, 502267905, 167422635, 753401857, 33484527, 585979222, 454432866, 
  292989611, 11161509, 552494695, 745791737, 292989611, 795165525, 648164772, 
  11161509, 648762710,
};

// Compute 1^k + 2^k + ... + n^k, for k <= 15
int sum_of_power_k(int n, int k) {
  int mul = 1;
  int ret = 0;
  
  for (int c: coefficients[k]) {
    mul = 1LL * mul * n % MOD;
    ret = (1LL * mul * c + ret) % MOD;
  }
  
  ret = 1LL * ret * denominators_inverse[k] % MOD;
  if (ret < 0) ret += MOD;
  
  return ret;
}

bool is_prime[SN];
void generate_primes(int n) {
  memset(is_prime, true, sizeof is_prime);
  is_prime[0] = is_prime[1] = false;
  
  for (int i=2; i<n; i++) if (is_prime[i]) {
    for (int j=i*i; j<n; j+=i) is_prime[j] = false;
  }
}

// Let n! = p_1 * p_2 * ..., where it is possible p_i = p_j, for i < j
// S[K][x] will gives the sum of p_i <= V[x]
// The returned value is sum(p_i ^ k) for k in [1, 15]
long long S[K][SN * 2];
vector<long long> sum_of_primes_factorial(int n) {
  int r = floor(sqrt(n));
  
  vector<int> V(r);
  for (int i=0; i<r; i++) V[i] = n / (i+1);
  for (int i=V[r-1]-1; i>0; i--) {
    V.push_back(i);
  }
  
  for (int i=0; i<V.size(); ++i) {
    for (int k=0; k<K; k++) {
      S[k][i] = sum_of_power_k(V[i], k+1) - 1;
    }
  }
  
  for (int p=2; p<=r; p++) if (is_prime[p]) {
    long long sp[K];
    long long pp[K];
    
    int idx = (int) V.size() - p + 1;
    for (int k=0; k<K; k++) sp[k] = S[k][idx];
    long long p2 = 1LL * p * p;
    
    pp[0] = p;
    for (int i=1; i<K; i++) pp[i] = pp[i-1] * p % MOD;

    for (int i=0; i<V.size(); ++i) {
      if (V[i] < p2) break;
      
      for (int k=0; k<K; k++) {
        int idx = ((i+1) * p <= r ? (i+1)*p - 1 : (int) V.size() - V[i]/p);
        S[k][i] = (S[k][i] - pp[k] * (S[k][idx] - sp[k])) % MOD;
      }
    }
  }

  vector<long long> ret(K);
  for (int k=0; k<K; k++) {
    for (int i=1; i<=r; i++) ret[k] = (ret[k] + S[k][i-1]) % MOD;
  }
  
  for (int p=2; p<=r; p++) if (is_prime[p]) {
    int num = n;
    int cnt = 0;
    while (num >= p) cnt += num /= p;
    cnt -= r;

    long long mul = 1;
    for (int k=0; k<K; k++) {
      mul = mul * p % MOD;
      ret[k] = (1LL * mul * cnt + ret[k]) % MOD;
    }
  }

  return ret;
}

int brute_sum_of_primes_factorial(int n) {
  long long ret = 0;
  for (int p=2; p<=n; p++) if (is_prime[p]) {
    int num = n;
    int cnt = 0;
    while (num >= p) cnt += num /= p;
    
    ret += 1LL * p * cnt;
  }
  
  return ret % MOD;
}

int e[K];
void apply_newton_identities(vector<long long> &p) {
  vector<int> inverse = {
    1, 502267905, 334845270, 753401857, 200907162, 167422635,
    717525578, 878968833, 111615090, 100453581, 456607186,
    585979222, 231815956, 358762789, 66969054
  };
  
  for (int i=0; i<p.size(); i++) {
    e[i] = 0;
    for (int j=0; j<i; j++) {
      long long term = p[j] * e[i-j-1] % MOD;
      if (j & 1) e[i] = (e[i] - term) % MOD;
      else e[i] = (e[i] + term) % MOD;
    }
    
    if (i & 1) e[i] = (e[i] - p[i]) % MOD;
    else e[i] = (e[i] + p[i]) % MOD;
    
    if (e[i] < 0) e[i] += MOD;
    e[i] = 1LL * e[i] * inverse[i] % MOD;
    
    // cerr << p[i] << " " << e[i] << endl;
  }
}

int n, m, k;

int p_adic[SN];

int dp[K][SN];
int f(int omega, int x) {
  if (omega == 0) return 1;
  if (omega < 0) return 0;
  if (x*x > n) return e[omega-1];
  if (~dp[omega-1][x]) return dp[omega-1][x];
  
  if (!is_prime[x]) return dp[omega-1][x] = f(omega, x+1);
  
  long long ret = f(omega, x+1);
  long long mul = 1;
  for (int i=0; i<p_adic[x]; ++i) {
    mul = mul * x % MOD;
    ret = ret + mul*f(omega - (i+1), x+1) % MOD;
  }
  
  return dp[omega-1][x] = ret % MOD;
}

void solve() {
  generate_primes(SN);
  
  scanf("%d %d %d", &n, &m, &k);
  
  vector<long long> v1 = sum_of_primes_factorial(n);
  vector<long long> v2 = sum_of_primes_factorial(m);
  vector<long long> v3 = sum_of_primes_factorial(n-m);
  
  auto vpn = [](int n, int p) {
    int ret = 0;
    while (n > 0) ret += n /= p;
    return ret;
  };
  
  for (int p=2; p*p<=n; p++) if (is_prime[p]) {
    int cnt1 = vpn(n, p), cnt2 = vpn(m, p), cnt3 = vpn(n-m, p);
    p_adic[p] = cnt1 - cnt2 - cnt3;
    
    long long mul = 1;
    for (int i=0; i<k; i++) {
      mul = mul * p % MOD;
      v1[i] = (v1[i] - mul*cnt1) % MOD;
      v2[i] = (v2[i] - mul*cnt2) % MOD;
      v3[i] = (v3[i] - mul*cnt3) % MOD;
    }
  }
  
  vector<long long> p(k);
  for (int i=0; i<k; i++) {
    p[i] = ((v1[i] - v2[i] - v3[i]) % MOD + MOD) % MOD;
  }
  
  apply_newton_identities(p);
  
  memset(dp, -1, sizeof dp);
  for (int i=0; i<k; i++) printf("%d\n", f(i+1, 2));
}

int main() {
  clock_t t = clock();
  solve();
  fprintf(stderr, "%.6lf\n", (double) (clock() - t) / CLOCKS_PER_SEC);
  return 0;
}
