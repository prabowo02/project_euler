import functools
import sys


sys.setrecursionlimit(10000)


@functools.cache
def f(L, R):
    if L >= R:
        return 0
    return min([i + max(f(L, i - 1), f(i + 1, R)) for i in range(L, R + 1)])


def brute(N):
    return [f(1, n) for n in range(N)]


def solve(N):
    N += 1

    # The root will split into two subtrees: left subtree which we already know the optimal cost, and right subtree
    # We assume the right subtree always has only at most two different heights, with its left child being higher than right
    @functools.cache
    def f(L, R):
        if L >= R:
            return 0
        if R - L == 1:
            return L
        if R - L == 2:
            return L + 1

        sz = R - L + 1
        h = len(bin(sz)) - 3
        if (1 << h) + (1 << h - 1) - 1 < sz:
            # left subtree and right subtree same height
            m = L + (1 << h) - 1
            return m + f(m+1, R)
        else:
            # left subtree higher than right subtree
            m = R - (1 << h - 1) + 1
            return m + max(f(L, m-1), f(m+1, R))

    dp = [0, 0]
    for n in range(2, N):
        if n % 10000 == 0:
            print(n)

        l, r = 1, n
        res = 10**9
        while l <= r:
            mid = (l + r) // 2
            costL, costR = dp[mid-1], f(mid+1, n)
            res = min(res, mid + max(costL, costR))
            if costL < costR:
                l = mid + 1
            else:
                r = mid - 1

        # Brute random values to the left.
        for i in range(max(1, r - len(bin(n)) * 10), r):
            res = min(res, max(dp[i - 1], f(i + 1, n)) + i)

        dp.append(res)

    return sum(dp)



if __name__ == '__main__':
    print(solve(100))
    print(solve(1000))
    print(solve(200000)) # Takes a few minutes
