# If i is the smallest index that s.t. p divides F_i, then
# i*p and its multiply are the (only) indices s.t. p^2 divides the fibo

# F_{p - legendre(p, 5)} can be divided by p, and F_{a} divides F_{ab},
# so the smallest index i that makes p divides F_i can be found by checking for 
# each divisor of it.

import math


def fibo(n, mod):
    f0, f1 = 0, 1
    a, b = 1, 0
    while n:
        if n & 1:
            a, b = (a*f0 + b*f1) % mod, (a*f1 + b*(f0+f1)) % mod
        f0, f1 = (f0*f0 + f1*f1) % mod, (2*f0 + f1)*f1 % mod
        n >>= 1
    return b


def solve(n):
    # Largest prime factor
    lprimes = [i for i in range(n * 2)]
    for p in range(2, len(lprimes)):
        if lprimes[p] != p:
            continue;
        for i in range(p+p, len(lprimes), p):
            lprimes[i] = p

    def pdivisors(n):
        ret = []
        while n > 1:
            ret.append(lprimes[n])
            n //= lprimes[n]
        return ret

    sq_indices = {6, 12, 25} # for 2^2, 3^2, 5^2

    for p in range(7, len(lprimes)):
        if lprimes[p] != p:
            continue

        num = p - (1 if p % 5 in (1, 4) else -1)

        for q in pdivisors(num):
            if fibo(num // q, p) == 0:
                num //= q

        sq_indices.add(num * p)

    sq_free = [True for _ in range(n * 2)]
    for i in sq_indices:
        for j in range(i, len(sq_free), i):
            sq_free[j] = False

    for i in range(1, len(sq_free)):
        if not sq_free[i]:
            continue
        n -= 1
        if n == 0:
            res = i * math.log10((1 + 5**0.5) / 2) - math.log10(5) / 2
            return '{},{:.1f}e{}'.format(fibo(i, 10**16), 10**(res - math.floor(res)), math.floor(res))

    assert False


if __name__ == '__main__':
    print(solve(200))
    print(solve(10**8))
