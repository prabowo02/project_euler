#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

const int N = 5000000;

struct Triple {
    int a, b, c;

    Triple () {};
    Triple (int x, int y, int z) : a(x), b(y), c(z) {};
};

// std::vector <Triple> triple;
std::vector <int> peri;

bool coprime (int x, int y) {
    return std::__gcd(x, y) == 1;
}

void triplePy () {
    for (int i=2; i*i<N; i++) for (int j=1; j<i && 2*i*(i+j)<=N; j++) {
        if (coprime(i, j) && (i - j & 1)) {
            // triple.push_back(Triple(i * i - j * j, 2 * i * j, i * i + j * j));
            peri.push_back (2 * i * (i + j));
        }
    }
    return;
}

int cnt[N + 1];
int ans[N + 1];

int Main () {
    int n;
    scanf ("%d", &n);
    printf ("%d\n", ans[n]);
    
    return 0;
}

int main () {
    // freopen ("tes.txt", "w", stdout);
    triplePy () ;
    // std::cout << triple.size() << std::endl;
    // for (int i=0; i<triple.size(); i++) std::cout << triple[i].a << " " << triple[i].b << " " << triple[i].c << std::endl;


    for (int i=0; i<peri.size(); i++) {
        for (int j=1; j*peri[i] < N; j++) cnt[j*peri[i]]++;
    }

    for (int i=1; i<=N; i++) {
        if (cnt[i] <= cnt[i - 1]) {
            cnt[i] = cnt[i - 1];
            ans[i] = ans[i - 1];
        } else ans[i] = i;
    }

    // for (int i=1; i<=10; i++) std::cout << cnt[i] << std::endl;

    int t;
    scanf ("%d", &t);
    while (t--) Main ();

    return 0;
}
