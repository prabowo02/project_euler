# Assume n even (i.e. n+1 coins in total)
# If silver coin is the first coin, first player always win
# If silver coin is the second coin, then xor of alternating gaps has to be positive for first player to win
# Otherwise, we can see the special move as moving to a phantom square, 
#   so the first gap (of size x) actually has size x+1.
#   Xor the alternating gaps, and they have to be positive for the first player to win

import functools


def solve(n, c, mod=10**18):
    _C = [[0 for _ in range(c + 2)] for _ in range(n + 1)]
    _C[0][0] = 1
    for i in range(1, len(_C)):
        _C[i][0] = 1
        for j in range(1, len(_C[0])):
            _C[i][j] = (_C[i - 1][j] + _C[i - 1][j - 1]) % mod
    def C(n, k):
        if k < 0 or k > n:
            return 0
        return _C[n][k]

    # Number of ways to distribute balls into bins such that xor of #balls is 0
    @functools.cache
    def f(balls, bins, bit=0):
        if balls == 0:
            return 1
        if balls & (1 << bit):
            return 0

        ret = 0
        for i in range(0, bins + 1, 2):
            if i * (1 << bit) > balls:
                break
            ret += C(bins, i) * f(balls - i * (1 << bit), bins, bit + 1)
        return ret % mod

    # Number of ways to distribute balls into bins
    def g(balls, bins):
        return C(balls + bins - 1, bins - 1)

    ans = C(n, c + 1) * (c + 1) # all config

    xorgap = c // 2 + 1
    altgap = c + 2 - xorgap

    cnt = 0
    for xorsum in range(n - c):
        altsum = n - c - xorsum - 1
        cnt += f(xorsum, xorgap) * g(altsum, altgap)

    if n % 2 == 1:
        return (ans - cnt * c) % mod

    ans -= cnt

    cnt = 0
    for xorsum in range(n - c):
        altsum = n - c - xorsum - 1
        cnt += (f(xorsum + 1, xorgap) - f(xorsum + 1, xorgap - 1)) * g(altsum, altgap)
    ans -= cnt * (c - 1)

    return ans % mod


if __name__ == '__main__':
    print(solve(10, 2))
    print(solve(100, 10))
    print(solve(1000000, 100, 1_000_003 * 1_000_033))
