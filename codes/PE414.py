# Suppose our base-B digits after sorted is [a b c d e] (a is least significant)
# Then an iteration will result in:
# (e - a)(B^4 - 1) + (d - b)(B^3 - B)

# Meaning that if the gaps e-a and d-b the same, they will all transition to the same number
# So we can treat this two gaps as a single class which is only O(B^2)

# Assumption: any numbers not from the same class as the Kaprekar constant will transition
# to a number that is not the constant;
# So we can assume that if it reaches the same class as the constant, it's not the constant yet.


import functools
import math
import sys

sys.setrecursionlimit(10**7)


def S(B):
    @functools.cache
    def step(a, b):
        nxt = b * B**4 + a * B**3 - (b + a * B)
        digs = sorted([nxt % B, nxt // B % B, nxt // B**2 % B, nxt // B**3 % B, nxt // B**4])
        nb, na = digs[-1] - digs[0], digs[-2] - digs[1]

        if (a, b) == (na, nb):
            return 0
        return 1 + step(na, nb)


    # assumes b > 0
    def count(a, b):
        if a == b:
            return (B - b) * math.comb(5, 3) * 2 + (B - b) * (a - 1) * 120 // 2 // 2

        if a == 0:
            return (B - b) * math.comb(5, 4) * 2 + (B - b) * (b - 1) * 120 // 6

        # First dig = second dig
        #   third dig = second dig/fourth dig
        ret = (B - b) * 120 // 6 + (B - b) * 120 // 2 // 2
        #   third dig != second dig/fourth dig
        ret += (B - b) * (a - 1) * 120 // 2

        # Fourth dig = fifth dig, by symmetry
        ret *= 2

        # 1 2 4 5 are different
        # 3 is same as 2/4
        ret += (B - b) * (b - a - 1) * 120 // 2 * 2
        # 3 is different
        ret += (B - b) * (b - a - 1) * (a - 1) * 120

        return ret


    ans = 0
    for b in range(1, B):
        for a in range(b + 1):
            ans += step(a, b) * count(a, b)
    return B**5 - B - 1 + ans



if __name__ == '__main__':
    print(S(15))
    print(S(111))
    print(sum(S(6*k + 3) for k in range(2, 301)) % 10**18)
