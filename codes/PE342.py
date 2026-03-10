# For phi(n^2) to be a cube, the largest prime factor of n must have exponent 2 (mod 3)

# For its largest prime factor p > 100, we can find try to find x in [1, 10^10 / p^2] such that x has prime factors < p, and phi(x p^2) is a cube. We can try to precompute all the phi of [1, 10^6] for this

# For largest prime factor p <= 100, we'll use DP


import collections
import functools
import itertools

def solve(N):
    S = int(N**0.2) # Threshold to split for cases when p < S and p >= S

    n = N // S**2 + 1
    largestPrimeFactor = [p for p in range(n)]
    for p in range(2, n):
        if largestPrimeFactor[p] != p:
            continue
        for i in range(p, n, p):
            largestPrimeFactor[i] = p

    @functools.cache
    def factorize(n):
        primes = []
        while n > 1:
            primes.append(largestPrimeFactor[n])
            n //= primes[-1]
        return collections.Counter(primes)

    @functools.cache
    def phi(n):
        factors = factorize(n).copy()
        primes = list(factors)

        for p in primes:
            factors += factorize(p - 1)
        factors -= collections.Counter(primes)
        return factors

    def is_cube(factors):
        return all(e % 3 == 0 for e in factors.values())

    ans = 0

    # 3314188388871
    for p in range(S, int(N**0.5)):
        if largestPrimeFactor[p] != p:
            continue

        for i in range(1, N // p**2 + 1):
            if largestPrimeFactor[i] >= p:
                continue
            if is_cube(phi(i) + factorize(i) + factorize(p - 1)):
                ans += i * p**2

    primes = [p for p in range(2, S + 1) if p == largestPrimeFactor[p]]

    def f(n, idx, facts):
        if idx < 0:
            return n

        ret = 0
        factCount = collections.Counter({k: v for k, v in facts})
        if primes[idx] not in factCount:
            ret += f(n, idx - 1, facts)

        startE = {
            0: 2,
            1: 3,
            2: 1,
        }[factCount[primes[idx]]]
        for e in itertools.count(startE, 3):
            if n * primes[idx]**e > N:
                break

            nfactCount = {k: v % 3 for k, v in (factCount + factorize(primes[idx] - 1)).items() if v % 3 != 0 and k < primes[idx]}
            nfactCount = tuple(sorted(nfactCount.items()))
            ret += f(n * primes[idx]**e, idx - 1, nfactCount)
        return ret

    # 2628852496773
    ans += f(1, len(primes) - 1, ()) - 1 # Exclude n = 1

    return ans


if __name__ == '__main__':
    print(solve(10**10))
