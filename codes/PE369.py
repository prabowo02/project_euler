import functools
import itertools


@functools.cache
def trans(mask, cards):
    nmask = mask
    for i in range(16):
        if not (mask >> i & 1):
            continue
        for j in range(4):
            if not (cards >> j & 1):
                continue
            nmask |= 1 << (i | (1 << j))
    return nmask


def mask_with_count(n, k):
    for mask in itertools.combinations(range(n), k):
        yield sum(1 << i for i in mask)


@functools.cache
def dp(mask, n, m):
    if m == 0:
        return 1 if n == 0 and mask & (1 << 15) else 0

    ans = 0
    for i in range(5):
        if i > n:
            break
        for cards in mask_with_count(4, i):
            ans += dp(trans(mask, cards), n - i, m - 1)

    return ans


def f(n):
    return dp(1, n, 13)


if __name__ == '__main__':
    print(f(5))
    print(sum(f(i) for i in range(4, 14)))
