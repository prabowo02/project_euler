# 10a + b = k
# ==> a = (k - b) / 10

# a + bm = (k - b)/10 + bm = k/10 + b(m - 1/10)

# When k = 0, we want a + bm = 0, so m = 1/10 (mod p)
# But when k > 0, we already have m - 1/10 = 0, so it follows a + bm is not 0

import math


def solve(n):
    n += 1
    is_primes = [True for _ in range(n)]
    for i in range(2, n):
        if not is_primes[i]:
            continue
        for j in range(i * 2, n, i):
            is_primes[j] = False

    return sum([pow(10, -1, p) for p in range(2, n) if is_primes[p] and p % 2 != 0 and p % 5 != 0])


if __name__ == '__main__':
    print(solve(10**7))
