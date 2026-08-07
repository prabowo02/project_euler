# x^2 - ax - b = 0
# Let p <= q be their roots
# p + q = -b
# pq = a

# (a(p + q) + 2b)(q - p) - 1/3 (q - p)((p + q)^2 - pq)
# (q - p)((-ab + 2b) - 1/3(b^2 - a))
# right term is rational ==> entire term is rational iff q - p is rational

# rational when (a^2 + 4b) is a square
# p, q = (a + sqrt(a^2 + 4b)) / 2
# it must be p and q are both integers

# We also have q - p = sqrt(a^2 + 4b) = A

# Lattice points: sum_{x=p}^q (ax + b - x^2 + 1)
# = sum_{i=0}^A i(A-i) + 1
# = A*A(A+1)/2 - A(A+1)(2A+1)/6 + A+1
# = (A^3 + 5A + 6) / 6

# We have
# a^2 + 4b = A^2

# For a fixed A:
# |b| <= n ==> |A^2 - a^2| <= 4n
# A^2 - 4n <= a^2 <= min(n^2, A^2 + 4n)

# Both LHS and RHS will grow around "at the same pace" as a (as we increment A from 0)
# i.e. sqrt(A^2 +/- 4n) ~= A
# So we find out when sqrt((A + k)^2 +/- 4n) != sqrt(A^2 +/- 4n) + k
# And there should only be O(sqrt(n)) points that happen

import math
import itertools

def ceilsqrt(x):
    sx = math.isqrt(x)
    return sx if sx*sx == x else sx + 1

def ceildiv(x, y):
    return x // y if x % y == 0 else x // y + 1

def linear_S(n):
    ans = 0
    for A in itertools.count(0):
        L, R = A*A - 4*n, min(n*n, A*A + 4*n)
        if L > R:
            break

        L = 0 if L < 0 else ceilsqrt(L)
        R = math.isqrt(R)

        cnt = R - L + 1
        if L % 2 == R % 2:
            cnt += 1 if A % 2 == R % 2 else -1
        if L == 0 and A % 2 == 0:
            cnt -= 1

        ans += cnt * f(A)

    return ans

def f(A):
    return (A**3 + 5*A + 6) // 6

def sum1(n):
    return n * (n+1) // 2

def sum2(n):
    return n * (n+1) * (2*n+1) // 6

# sum k^3 from k = 1 to n
def sum3(n):
    return (n*(n+1) // 2)**2

# sum k^4 from k = 1 to n
def sum4(n):
    return n * (n+1) * (2*n+1) * (3*n*n + 3*n - 1) // 30

# Returns sum f(k) for k in range(n, -1, -2)
def sumF(n):
    if n < 0:
        return 0
    total = (sum3(n) + 5*sum1(n) + 6*n + 6) // 6
    n2 = n // 2
    even = (8*sum3(n2) + 10*sum1(n2) + 6*n2 + 6) // 6
    return even if n % 2 == 0 else total - even

# Returns sum k*f(k) for k in range(n, -1, -2)
def sumkF(n):
    if n < 0:
        return 0
    total = (sum4(n) + 5*sum2(n) + 6*sum1(n)) // 6
    n2 = n // 2
    even = (16*sum4(n2) + 20*sum2(n2) + 12*sum1(n2)) // 6
    return even if n % 2 == 0 else total - even

def S(n):
    # From 1 to c, how many of them = A (mod 2)
    def getCnt(c, A):
        if c <= 0:
            return 0
        return (c + A % 2) // 2

    # sum(2 * (c + (k-A)/2) * f(k) for k in range(A, -1, -2))
    def getSum(c, A):
        return (2*c - A) * sumF(A) + sumkF(A)

    ans = 0
    lim = math.isqrt(n*n - 4*n) + 1

    A = 0
    while A*A + 4*n <= n*n:
        # sqrt((A + k)^2 + 4n) = sqrt(A^2 + 4n) + k
        # (A + k)^2 + 4n = (C + k)^2
        # k = (C^2 - A^2 - 4n) / (2A - 2C)
        C = math.isqrt(A*A + 4*n)
        k = (C*C - A*A - 4*n) // (2*A - 2*C) + 1

        assert math.isqrt((A + k-1)**2 + 4*n) == math.isqrt(A*A + 4*n) + k-1
        assert math.isqrt((A + k)**2 + 4*n) != math.isqrt(A*A + 4*n) + k

        k = min(k, lim - A)

        ans += getSum(getCnt(C + k - 1, A + k - 1), A + k - 1) + getSum(getCnt(C + k - 2, A + k - 2), A + k - 2)
        ans -= getSum(getCnt(C - 1, A - 1), A - 1) + getSum(getCnt(C - 2, A - 2), A - 2)

        # for i in range(A, A + k):
        #     naive += 2 * getCnt(math.isqrt(i**2 + 4*n), i) * f(i)

        A += k

    nA = math.isqrt(n*n + 4*n) + 1
    ans += sumF(nA - 1) * getCnt(n, nA - 1) * 2 + sumF(nA - 2) * getCnt(n, nA - 2) * 2
    ans -= sumF(A - 1) * getCnt(n, A - 1) * 2 + sumF(A - 2) * getCnt(n, A - 2) * 2

    # for i in range(A, nA):
    #     naive += 2 * getCnt(n, i) * f(i)

    A = 0
    while A*A - 4*n <= 0:
        if A % 2 == 0:
            ans += f(A)
            # naive += f(A)
        A += 1

    lim = math.isqrt(n*n + 4*n) + 1

    while A*A - 4*n <= n*n:
        # sqrt((A + k)^2 - 4n) = sqrt(A^2 - 4n) + k
        # (A + k)^2 - 4n = (C + k)^2
        # k = (C^2 - A^2 + 4n) / (2A - 2C)
        C = ceilsqrt(A*A - 4*n)
        k = (C*C - A*A + 4*n) // (2*A - 2*C) + 1

        assert ceilsqrt((A + k-1)**2 - 4*n) == ceilsqrt(A*A - 4*n) + k-1
        assert ceilsqrt((A + k)**2 - 4*n) != ceilsqrt(A*A - 4*n) + k

        k = min(k, lim - A)

        C = ceilsqrt(A*A - 4*n) - 1

        ans -= getSum(getCnt(C + k - 1, A + k - 1), A + k - 1) + getSum(getCnt(C + k - 2, A + k - 2), A + k - 2)
        ans += getSum(getCnt(C - 1, A - 1), A - 1) + getSum(getCnt(C - 2, A - 2), A - 2)

        # for i in range(A, A + k):
        #     naive -= 2 * getCnt(ceilsqrt(i**2 - 4*n) - 1, i) * f(i)

        A += k

    return ans


if __name__ == '__main__':
    print(linear_S(5))
    print(linear_S(100))

    print(S(5))
    print(S(100))
    print(S(10**12) % 10**8)
