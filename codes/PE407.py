import functools
import sys

sys.setrecursionlimit(100000)


def solve(N):
    lprimes = [p for p in range(N + 1)]
    for p in range(2, len(lprimes)):
        if lprimes[p] != p:
            continue
        for i in range(p*2, len(lprimes), p):
            lprimes[i] = p

    def prime_factors(n):
        ret = []
        while n > 1:
            p, e = lprimes[n], 0
            while n % p == 0:
                n //= p
                e += 1
            ret.append(p**e)
        return ret

    def M(n):
        pf = prime_factors(n)
        return max(
            sum((mask >> j & 1) * (n // pf[j]) * pow(n // pf[j], -1, pf[j]) for j in range(len(pf))) % n
            for mask in range(1 << len(pf))
        )


    ans = 0
    for n in range(2, N + 1):
        ans += M(n)
    return ans


def brute(N):
    return sum(max(a for a in range(n) if a**2 % n == a) for n in range(2, N + 1))


if __name__ == '__main__':
    print(brute(10))
    print(solve(10))
    print(solve(10**7))

