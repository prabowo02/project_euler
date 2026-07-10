import functools
import math


def D(N):
    mu = [0 for _ in range(math.isqrt(N) + 1)]
    mu[1] = 1
    for i in range(1, len(mu)):
        for j in range(i+i, len(mu), i):
            mu[j] -= mu[i]

    _Mertens = mu[:]
    for i in range(1, len(_Mertens)):
        _Mertens[i] += _Mertens[i - 1]

    @functools.cache
    def Mertens(n):
        if n < len(_Mertens):
            return _Mertens[n]
        sn = math.isqrt(n)
        return 1 + sn * Mertens(sn) \
            - sum(mu[i] * (n // i) for i in range(1, sn + 1)) \
            - sum(Mertens(n // j) for j in range(2, sn + 1))

    # sum f(floor(n/i)) * mu(i); i <= n
    def muDot(f, n):
        sn = math.isqrt(n)
        ret = 0
        for i in range(1, sn):
            ret += f(i) * (Mertens(n // i) - Mertens(n // (i + 1)))
        for i in range(1, n // sn + 1):
            ret += f(n // i) * mu[i]
        return ret

    return 3 + 3 * muDot(lambda x: x*x, N) + muDot(lambda x: x*x*x, N)


if __name__ == '__main__':
    print(D(1000000))
    print(D(10**10))
