# A distance of a cell can be uniquely determined by a pair of (x, y), then calc:
# sqrt(3) sqrt(x^2 + y^2 + xy)

# So now, for a fixed distance l, count how many pairs (x, y) such that x^2 + y^2 + xy = z
#   for some z = l^2 / 3

# Also note that x^2 + y^2 + xy is the norm of (x + yw) where w is cube root of unity

# To count the number of solutions, factorize z
# Using something similar to Jacobi's two-square theorem to count number of sum of two square solutions, we can obtain:
# z = 3^{e3} * prod_i p_i^e_i * prod_j q_j^f_j
# Where p_i = 1 (mod 3) and q_j = 2 (mod 3)
# Number of sols is 6 * prod(e_i + 1) and f_j must be all even


import functools
import sys

sys.setrecursionlimit(10**7)

# 450 = 6 * 75
# 75 = 3*5*5
def solve(N):
    sn = 35_000_000 # sqrt(N^2 / 3 / 7^4 / 13^4); 7 and 13 are the first 1 (mod 3) primes

    primes = [True for _ in range(sn)]
    p1 = [] # 1 (mod 3) primes
    p2 = [] # 2 (mod 3) primes
    for p in range(2, sn):
        if not primes[p]:
            continue
        for i in range(p+p, sn, p):
            primes[i] = False

        if p % 3 == 1:
            p1.append(p)
        elif p % 3 == 2:
            p2.append(p)

    # Count number of integers <= n of the form q^(2j) where q = (2 mod 3)
    @functools.cache
    def countq(n, i=0):
        q = p2[i]**2
        if q > n:
            return 1

        ret, qe = 0, 1
        while qe <= n:
            ret += countq(n // qe, i+1)
            qe *= q

        return ret

    # Count number of integers <= n of the form 3^i q^(2j)
    @functools.cache
    def count3q(n):
        three = 1
        ret = 0
        while three <= n:
            ret += countq(n // three)
            three *= 3
        return ret

    divisors = [1, 3, 5, 15, 25, 75]
    @functools.cache
    def count(n, e=75, i=0):
        p = p1[i]
        if e == 1:
            return count3q(n)
        if e % 5 == 0 and p**4 > n or e % 3 == 0 and p**2 > n:
            return 0

        ret = 0
        for d in divisors:
            if e % d != 0:
                continue
            if p**(d - 1) > n:
                break

            ret += count(n // p**(d - 1), e // d, i + 1)
        return ret

    return count(N**2 // 3)


if __name__ == '__main__':
    print(solve(5 * 10**11))
