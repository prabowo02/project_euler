# For a fixed n = prod(pi^ei), number of (ordered) pairs is prod(2ei + 1)

# There's also aw hyperbola method by noticing that Dirichlet series of it is zeta^3(s) / zeta(2s)

import math
import sys

sys.setrecursionlimit(10**7)

def g(n):
    def build_count_primes(n):
        sn = math.isqrt(n)
        ns = [n // i for i in range(1, sn + 1)] + \
             [i for i in range(1, sn + (1 if sn*sn != n else 0))][::-1]
        count = {
          x: x - 1 for x in ns
        }

        for p in range(2, sn + 1):
            if count[p] == count[p - 1]:
                continue

            for x in ns:
                if p*p > x:
                    break
                count[x] -= count[x // p] - count[p - 1]

        return count

    pi = build_count_primes(n)

    primes = [p for p in range(2, math.isqrt(n) + 1) if pi[p] != pi[p - 1]]

    print('Done init')

    def dp(x, num):
        if x >= len(primes) or primes[x] * primes[x] > num:
            return 3 * max(0, pi[num] - pi[primes[x - 1]]) + 1
        e, pe = 0, 1
        ret = 0
        while pe <= num:
            ret += (2*e + 1) * dp(x + 1, num // pe)
            e += 1
            pe *= primes[x]

        return ret

    return (dp(0, n) + n) // 2


if __name__ == '__main__':
    print(g(10**6))
    print(g(10**12))
