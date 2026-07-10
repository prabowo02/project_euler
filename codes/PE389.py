import functools
import sys

sys.setrecursionlimit(10**6)

# Also possible with G.F.
# T(x) = sum_{1<=k<=4}(x^k) / 4
# C(x) = T(sum_{1<=k<=6}{x^k} / 6)
# ...
# V = I''(1) + I'(1) - I'(1)^2

def solve():
    dice = [4, 6, 8, 12, 20]

    @functools.cache
    def count(x, n, s):
        if n == 0:
            return 1 if s == 0 else 0
        return sum(count(x, n - 1, s - i) for i in range(1, min(dice[x], s) + 1)) / dice[x]

    @functools.cache
    def E2(x, n):
        if x == len(dice) - 1:
            return n * sum(i*i for i in range(1, dice[-1] + 1)) / dice[-1] + \
                n * (n - 1) * sum(i*j for i in range(1, dice[-1] + 1) for j in range(1, dice[-1] + 1)) / dice[-1]**2
        ret = 0
        for s in range(n, dice[x] * n + 1):
            ret += E2(x + 1, s) * count(x, n, s)
        return ret

    @functools.cache
    def E1(x, n):
        if x == len(dice) - 1:
            return n * sum(i for i in range(1, dice[-1] + 1)) / dice[-1]
        ret = 0
        for s in range(n, dice[x] * n + 1):
            ret += E1(x + 1, s) * count(x, n, s)
        return ret

    return E2(0, 1) - E1(0, 1)**2


if __name__ == '__main__':
    print('{:.4f}'.format(solve()))
