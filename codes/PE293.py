import itertools


def gen(n):
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    def f(prod, idx):
        if prod > n:
            return
        yield prod

        yield from f(prod * primes[idx], idx)
        yield from f(prod * primes[idx + 1], idx + 1)

    yield from f(2, 0)


def is_prime(n):
    _n = n
    for i in range(2, n):
        if i * i > n:
            break
        while n % i == 0:
            n //= i
    return _n == n


def solve(N):
    def fortunate(n):
        for m in itertools.count(3, 2):
            if is_prime(n + m):
                return m

    fortunates = set()
    for n in gen(N):
        fortunates.add(fortunate(n))
    print(fortunates)
    print(len(fortunates))
    print(sum(fortunates))


if __name__ == '__main__':
    solve(10**9)
