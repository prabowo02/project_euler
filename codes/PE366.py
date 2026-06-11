# The game is Fibonacci nim
# Represent the number of stones using Zeckendorf
# You win if and only if after taking the suffix from the Zeckendorf,
#   the next player can't remove the next smallest from Zeckendorm
# The largest such move must have left the remaining Zeckendorf to be "2-separated",
#   i.e. every neighbouring Fibo are of gap exactly 2
# So you brute these prefix, then compute the suffix that can be used as the next-to-move suffix

def solve(n):
    fib = [0, 1]
    while fib[-1] < n:
        fib.append(fib[-1] + fib[-2])

    ans = 0
    for i in range(2, len(fib)):
        s = n
        for j in range(i, 1, -2):
            s -= fib[j]
            if s < 0:
                break
            lo = min(s + fib[j], (fib[j + 2] - 1) // 2) - fib[j] + 1 if j < i else 0
            hi = min(s, (fib[j] - 1) // 2)

            ans += (hi + lo) * (hi - lo + 1) // 2

    return ans


def brute(n):
    import functools
    @functools.cache
    def f(n, m):
        if n == 0:
            return False
        return any(not f(n - i, i*2) for i in range(min(n, m), 0, -1))

    def M(n):
        for i in range(n - 1, 0, -1):
            if not f(n - i, i*2):
                return i
        return 0

    return sum(M(i) for i in range(1, n + 1))

if __name__ == '__main__':
    print(solve(100))
    # for i in range(100):
    #     if brute(i) != solve(i):
    #         print(i, brute(i), solve(i))
    print(solve(10**18) % 10**8)
