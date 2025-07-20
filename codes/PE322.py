import math


def get_base(n, b):
    ret = []
    while n > 0:
        ret.append(n % b)
        n //= b
    return ret


def div_by_p(n, m, p):
    nb, mb = get_base(n, p), get_base(m, p)
    return any([nn < mm for nn, mm in zip(nb, mb)])


# Count numbers < n that are "superset" of m in base b
def count_superset(n, m, b):
    n, m = get_base(n, b), get_base(m, b)
    while len(m) < len(n):
        m.append(0)

    @functools.cache
    def f(x, lim):
        if x < 0:
            return lim == 0
        return sum(f(x - 1, lim and i == n[x]) for i in range(m[x], n[x] + 1 if lim else b))

    return f(len(n) - 1, True)


# Returns T(10^n, 10^m - d)
def solve(n, m, d):
    N, M = 10**n, 10**m

    small2 = [i for i in range(2**m - d, 2**m) if not div_by_p(i, 2**m - d, 2)]
    small5 = [i for i in range(5**m - d, 5**m) if not div_by_p(i, 5**m - d, 5)]

    big2 = count_superset(N // 2**m, (M - d) // 2**m, 2)
    big5 = count_superset(N // 5**m, (M - d) // 5**m, 5)

    res = len(small2) * big2 + len(small5) * big5

    i2, i5 = pow(5**m, -1, 2**m) * 5**m, pow(2**m, -1, 5**m) * 2**m
    for i in small2:
        for j in small5:
            # print(i, j)
            num = (i * i2 + j * i5) % M
            # assert(num % 2**m == i and num % 5**m == j)
            res -= sum(1 for k in range(num, N, M) if not div_by_p(k, M - d, 2) and not div_by_p(k, M - d, 5))

    return N - M + d - res


if __name__ == '__main__':
    print(solve(9, 7, 10))
    print(solve(18, 12, 10))
