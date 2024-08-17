from fractions import Fraction
import functools


def gen(n):
    is_squares = [False for _ in range(n*n + 1)]
    for i in range(n + 1):
        is_squares[i*i] = True

    ret = []
    for i in range(1, n + 1):
        for j in range(n):
            if i*i + j*j > n*n:
                break
            if is_squares[i*i + j*j]:
                ret.extend([
                    (i, j),
                    (-j, i),
                    (-i, -j),
                    (j, -i),
                ])

    def key(p):
        if p[0] < 0 or p[0] == 0 and p[1] > 0:
            m, x, y = 1, -p[0], -p[1]
        else:
            m, x, y = -1, p[0], p[1]

        if x == 0:
            x, y = 1, -n

        return (m, Fraction(y, x))

    d = {}
    for p in ret:
        d.setdefault(key(p), []).append(p)

    ret = []
    for k in sorted(d):
        ret.append(tuple(d[k]))
    return ret


def solve(n):
    sqrt = {i*i: i for i in range(n + 1)}
    edges = gen(n)

    @functools.cache
    def f(n, x, y, idx):
        if n < 0 or abs(x) > n or abs(y) > n:
            return 0
        if (x, y) == (0, 0) and idx > 0:
            return 1
        if idx >= len(edges):
            return 0

        ret = 0
        for i in range(idx, len(edges)):
            if i >= idx + len(edges) // 2 - 1:
                break

            for p in edges[i]:
                ret += f(n - sqrt[p[0]*p[0] + p[1]*p[1]], x + p[0], y + p[1], i + 1)

        return ret

    return f(n, 0, 0, 0)


if __name__ == '__main__':
    n = int(input())
    print(solve(n))

