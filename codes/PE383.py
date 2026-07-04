# v5((2n-1)!) < 2v5(n!)
# ==> v5((2n)!) - v5(n!) - v5(n!) < v5(2n)
# ==> v5(C(2n, n)) < v5(2n)

# If n = 5^a * b; then we need number of carries of b+b < a

import functools

def solve(n):
    fives = []
    while n > 0:
        fives.append(n % 5)
        n //= 5

    cnt, ans = 0, 0
    while fives:
        @functools.cache
        def f(x, c, lim, carry):
            if c < 0:
                return 0
            if x < 0:
                return 1 - carry

            ret = 0
            for i in range(1 if x == 0 else 0, fives[x] + 1 if lim else 5):
                nlim = lim and i == fives[x]
                if carry == 0:
                    if i < 2:
                        ret += f(x - 1, c, nlim, 0)
                        ret += f(x - 1, c - 1, nlim, 1)
                    elif i == 2:
                        ret += f(x - 1, c, nlim, 0)
                else:
                    if i == 2:
                        ret += f(x - 1, c - 1, nlim, 1)
                    elif i > 2:
                        ret += f(x - 1, c, nlim, 0)
                        ret += f(x - 1, c - 1, nlim, 1)
            return ret

        ans += f(len(fives) - 1, cnt - 1, True, 0)
        ans += f(len(fives) - 1, cnt - 2, True, 1)

        cnt += 1
        fives = fives[1:]

    return ans


if __name__ == '__main__':
    print(solve(1000))
    print(solve(10**9))
    print(solve(10**18))
