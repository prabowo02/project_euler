# 1+...+N + N + N+...+1 = (N + 2) * N
# Triangle: K * (K + 1) / 2
# 2N^2 + 4N = K^2 + K

# Use integer equation solver and obtain the recursive solution.

import itertools
import math

def test(N):
    ans = []
    for n in itertools.count(1):
        t = 8 * n * (n + 2) + 1
        if math.isqrt(t)**2 == t:
            print(n, (math.isqrt(t) - 1) // 2)
            ans.append(n)
            if len(ans) == N:
                break

    return sum(ans)


def solve(L):
    Ns = [1, 3]
    Ks = [2, 5]
    while len(Ns) < L:
        n, k = Ns[-2], Ks[-2]
        Ns.append(n * 3 + k * 2 + 3)
        Ks.append(n * 4 + k * 3 + 5)

    return sum(Ns[:L])


if __name__ == '__main__':
    print(solve(5))
    print(solve(40))