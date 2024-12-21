# Answer is k!/n^k * [x^k] (1 + x + x^2 / 2)^n
# But due to floating precision issue, need to use combinatorics approach with log for large numbers

import decimal
import math


def solve(k, n):
    lfact = [decimal.Decimal(0) for _ in range(n + 1)]
    for i in range(1, n + 1):
        lfact[i] = lfact[i - 1] + decimal.Decimal(i).ln()

    ltotal = k * decimal.Decimal(n).ln()

    ans = 0
    for two in range(k // 2 + 1):
        one = k - two * 2
        if one + two > n:
            continue

        p = lfact[n] - lfact[one] - lfact[two] - lfact[n - one - two]
        p += lfact[k] - two * lfact[2]
        p -= ltotal

        ans += p.exp()

    return 1 - ans



if __name__ == '__main__':
    print('{:.10f}'.format(solve(3, 7)))
    print('{:.10f}'.format(solve(20000, 1000000)))
