# (sqrt(p) + sqrt(q))^2n + (sqrt(p) - sqrt(q))^2n = {an integer}
# |sqrt(p) - sqrt(q)| < 1 for it to approach 0 for large n
# (sqrt(q) - sqrt(p))^2n < 10^-2011
# 2n > -2011 / log_10{sqrt(q) - sqrt(p)}

import math

YEAR = 2011


def N(p, q):
    return math.ceil(-YEAR / math.log10(math.sqrt(q) - math.sqrt(p)) / 2)


def solve(L):
    ans = 0
    for p in range(1, L):
        for q in range(p + 1, L):
            if p + q > YEAR:
                break
            if math.sqrt(q) - math.sqrt(p) >= 1:
                break
            ans += N(p, q)
    return ans


if __name__ == '__main__':
    print(solve(YEAR))