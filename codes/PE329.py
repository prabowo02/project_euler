import functools
import fractions


def solve(n, croaks):
    n += 1
    primes = [True for _ in range(n)]
    primes[0], primes[1] = False, False

    for p in range(2, n):
        if not primes[p]:
            continue
        for i in range(p*2, n, p):
            primes[i] = False

    # Frog is at square x at the y-th step
    @functools.cache
    def f(x, y):
        ret = 0
        if y + 1 == len(croaks):
            ret = 1
        else:
            cnt = 0
            if x > 1:
                ret += f(x - 1, y + 1)
                cnt += 1
            if x + 1 < n:
                ret += f(x + 1, y + 1)
                cnt += 1
            ret /= cnt

        if primes[x] == (croaks[y] == 'P'):
            ret *= fractions.Fraction(2, 3)
        else:
            ret *= fractions.Fraction(1, 3)

        return ret

    return sum(f(i, 0) for i in range(1, n)) / (n - 1)


if __name__ == '__main__':
    print(solve(500, 'PPPPNNPPPNPPNPN'))
