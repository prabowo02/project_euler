import functools


def solve(N):
    # S is a set of exponent
    @functools.cache
    def longest_antichain_length(S):
        @functools.cache
        def dp(x, s):
            if s == 0:
                return 1
            if x == len(S):
                return 0
            return sum(dp(x + 1, s - i)
                       for i in range(min(S[x], s) + 1))

        return max(dp(0, i) for i in range(sum(S) + 1))

    exps = [[] for _ in range(N + 1)]
    for p in range(2, len(exps)):
        if exps[p]:
            continue
        for i in range(p, len(exps), p):
            e, num = 1, i // p
            while num % p == 0:
                e += 1
                num //= p
            exps[i].append(e)

    return sum(longest_antichain_length(tuple(sorted(s))) for s in exps[1:])


if __name__ == '__main__':
    print(solve(10**8))
