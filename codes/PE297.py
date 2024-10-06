import functools


def solve(n):
    fib, sumfib = [1, 2], [1, 3]
    while fib[-1] < n:
        fib.append(fib[-1] + fib[-2])
        sumfib.append(sumfib[-1] + fib[-1])


    @functools.cache
    def g(i):
        if i < 0:
            return 1, 0
        a, b = g(i - 1)
        c, d = g(i - 2)
        return a + c, b + d + c


    @functools.cache
    def f(i, s):
        if s < 0:
            return 0, 0
        if i < 0:
            return 1, 0
        if sumfib[i] <= s:
            return g(i)

        a, b = f(i - 1, s)
        c, d = f(i - 2, s - fib[i])
        return a + c, b + d + c

    return f(len(fib) - 1, n - 1)[1]


if __name__ == '__main__':
    print(solve(10))
    print(solve(10**6))
    print(solve(10**17))
    print(solve(10**100))
