import math


def sum_of_squares(n):
    return n * (n + 1) * (n*2 + 1) // 6


def solve(n):
    res = 0
    sn = math.isqrt(n)
    for i in range(1, sn):
        res += i * (sum_of_squares(n // i) - sum_of_squares(n // (i + 1)))

    for i in range(1, n // sn + 1):
        res += n // i * i*i

    return res


if __name__ == '__main__':
    print(solve(1))
    print(solve(2))
    print(solve(3))
    print(solve(4))
    print(solve(5))
    print(solve(6))
    print(solve(10**15) % 10**9)
