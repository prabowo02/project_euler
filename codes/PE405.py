# a(n) --> number of "points" from two T(n) sharing the same major side
# b(n) --> number of points from two T(n) with one major shares with one minor side

# a(n) = a(n-1) + 2a(n-2) + 2; a(0) = 0; a(1) = 2
# b(n) = b(n-1) + 2b(n-2) + 1; b(0) = 0; b(1) = 0
# f(n) = a(n-1) + 4b(n-1) + 4f(n-1); f(0) = 0

import functools
import sys


sys.setrecursionlimit(10**6)

@functools.cache
def a(n):
    if n <= 0:
        return 0
    if n == 1:
        return 2
    return (a(n - 1) + 2 * a(n - 2) + 2) % 17**7


@functools.cache
def b(n):
    if n <= 0:
        return 0
    if n == 1:
        return 0
    return (b(n - 1) + 2 * b(n - 2) + 1) % 17**7


@functools.cache
def f(n):
    if n <= 1:
        return 0
    return (a(n - 1) + 4 * b(n - 1) + 4 * f(n - 1)) % 17**7


# Find f(10^n)
def solve(n):
    A = [
        [1, 2, 0, 0, 2, 0],
        [1, 0, 0, 0, 0, 0],
        [0, 0, 1, 2, 1, 0],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [1, 0, 4, 0, 0, 4],
    ]

    # Pattern repeating every 8 * 17**6

    mod = 17**7
    def multiply(A, B):
        l = len(A)
        return [[sum(A[i][k] * B[k][j] for k in range(l)) % mod for j in range(l)] for i in range(l)]


    def power(A, n):
        l = len(A)
        res = [[1 if i == j else 0 for j in range(l)] for i in range(l)]
        while n > 0:
            if n & 1:
                res = multiply(res, A)
            A = multiply(A, A)
            n >>= 1
        return res

    n %= 4 * 16 * 17**5
    A = power(A, (10**n - 1) % (8 * 17**6))
    return (A[-1][0] * 2 + A[-1][4]) % mod

if __name__ == '__main__':
    print(f(1))
    print(f(2))
    print(f(3))
    print(f(4))
    print(solve(9))
    print(solve(10**18))
