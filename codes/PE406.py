import functools
import sys

sys.setrecursionlimit(100000)


def C(n, a, b):
    def cost(c):
        @functools.cache
        def f(x, y):
            if x * a + y * b > c:
                return 0
            return 1 + f(x + 1, y) + f(x, y + 1)
        return f(0, 0)

    r = 1
    while cost(r) < n:
        r *= 2

    l = 0
    for _ in range(100):
        mid = (l + r) / 2
        if cost(mid) >= n:
            r = mid
        else:
            l = mid
    return l


if __name__ == '__main__':
    print(C(5, 2, 3))
    print(C(500, 2**0.5, 3**0.5))
    print(C(20000, 5, 7))
    print(C(2000000, 5**0.5, 7**0.5))

    res = 0
    a, b = 0, 1
    for k in range(1, 31):
        a, b = b, a + b
        res += C(10**12, k**0.5, a**0.5)
    print('{:.8f}'.format(res))
