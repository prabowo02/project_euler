import functools


def f(n):
    def d_digit_count(d):
        def add(mods, x, val):
            mods[x] += val
            mods[x] = min(mods[x], 2)

        @functools.cache
        def dp(x, zero, suff):
            if zero > 1:
                return 0
            if x == 0:
                return zero
            ret = 0
            for i in range(0 if x < d else 1, 10):
                nsuff = [0 for _ in range(d)]
                for j in range(d):
                    add(nsuff, (j*10 + i) % d, suff[j])
                add(nsuff, i % d, 1)

                ret += dp(x - 1, min(2, zero + nsuff[0]), tuple(nsuff))
            return ret

        return dp(d, 0, tuple(0 for _ in range(d)))

    return sum(d_digit_count(d) for d in range(1, n + 1))


if __name__ == '__main__':
    print(f(1))
    print(f(3))
    print(f(7))
    print(f(19))
