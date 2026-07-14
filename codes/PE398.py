# [x^n] 1 / (1 - x)^m = C(n + m - 1, m - 1)

# Brute size of second smallest, say s.
# And how many segments (exclude smallest) to its left, say k.
# Consider smallest to its left.
# Smallest must have size at most s: (x - x^{s+1}) / (1 - x)
# Segments to its left has size at least s+1 (x^{s+1}) / (1 - x)
# Segments to its right has size at least s: (x^s) / (1 - x)

# Our G.F. [x^n] (x - x^{s+1}) / (1 - x) * (x^{s+1} / (1 - x))^k * (x^s / (1 - x))^{m-k-2} * x^s
# = [x^{n - 1 - s - (s+1)k - s(m-k-2)}] (1 - x^s) / (1 - x)^{m-1}
# = [x^{n - 1 - k - s(m-1)}] (1 - x^s) / (1 - x)^{m-1}

# Do the same when smallest is to its right, in which the smallest can have size at most s-1

# [x^{n - 1 - k - s(m-1)}] (1 - x^{s-1}) / (1 - x)^{m-1}

import functools
import math


def E(n, m):
    @functools.cache
    def count(t):
        return math.comb(t + m - 2, m - 2)

    res = 0
    for s in range(1, n // m + 2):
        add = 0

        for k in range(m - 1):
            t = n - 1 - k - s*(m-1)
            if t < 0:
                break
            add += count(t) * m
            if t >= s:
                add -= count(t - s) * (k + 1)
            if t >= s - 1:
                add -= count(t - (s-1)) * (m - k - 1)
        res += add * s

    return res / math.comb(n - 1, m - 1)


if __name__ == '__main__':
    print(E(3, 2))
    print(E(8, 3))
    print(E(10**7, 100))
