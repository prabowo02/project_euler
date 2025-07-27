# Euclid games: losing if x/phi < y < x*phi and x != y
# Number of losing positions in row y: exactly y-1

import functools
import decimal


# sum_x floor((ax + b) / n)
@functools.cache
def S(a, b, m, n):
    if a >= m:
        return (a // m) * n * (n - 1) // 2 + S(a % m, b, m, n)
    if b >= m:
        return (b // m) * n + S(a, b % m, m, n)

    n_, b_ = divmod(a*n + b, m)
    if n_ == 0:
        return 0

    return S(m, b_, a, n_)


# sum_x^n x*floor((ax + b) / m)
@functools.cache
def S1(a, b, m, n):
    if a >= m:
        return (a // m) * (n - 1) * n * (2*n - 1) // 6 + S1(a % m, b, m, n)
    if b >= m:
        return (b // m) * n * (n - 1) // 2 + S1(a, b % m, m, n)

    n_, b_ = divmod(a*n + b, m)
    if n_ == 0:
        return 0

    return ((2 * n - 1) * S(m, b_, a, n_) - S2(m, b_, a, n_)) // 2


# sum_x^n floor((ax + b) / m)^2
@functools.cache
def S2(a, b, m, n):
    if a >= m:
        return (a // m)**2 * (n - 1) * n * (2*n - 1) // 6 + S2(a % m, b, m, n) + 2 * (a // m) * S1(a % m, b, m, n)
    if b >= m:
        return (b // m)**2 * n + S2(a, b % m, m, n) + 2 * (b // m) * S(a, b % m, m, n)

    n_, b_ = divmod(a*n + b, m)
    if n_ == 0:
        return 0

    return (2 * n_ - 1) * S(m, b_, a, n_) - 2 * S1(m, b_, a, n_)


def linear(N):
    ans = 0
    for i in range(N):
        ans += i * (i + 1)

    PHI = (1 + 5**0.5) / 2
    for i in range(int(N / PHI) + 1, N + 1):
        ans -= i * (int(PHI * i) - N)

    return ans


def solve(N):
    decimal.getcontext().prec = 50
    PHI = (decimal.Decimal(5).sqrt() + 1) / 2

    L = int(N / PHI)    
    a, b = PHI.as_integer_ratio()

    ans = (N - 1) * N * (2*N - 1) // 6 + N * (N - 1) // 2
    ans -= S1(a, 0, b, N + 1) - S1(a, 0, b, L + 1)
    ans += (N + L + 1) * (N - L) // 2 * N

    return ans


if __name__ == '__main__':
    print(linear(10))
    print(linear(10**4))
    print(solve(10**4))
    print(solve(10**16) % 7**10)
