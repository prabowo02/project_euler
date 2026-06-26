import functools
import sys

sys.setrecursionlimit(10000)


def solve():
    @functools.cache
    def f(pairs, half):
        res = 1
        if pairs < 499:
            res += (499 - pairs) * 2 / 1000 * f(pairs + 1, half)
        if half == 0:
            res += 1 / 1000 * f(pairs, 1)
        return res * 1000 / (999 - pairs)

    return f(0, 0)

if __name__ == '__main__':
    print('{:.8f}'.format(solve()))
