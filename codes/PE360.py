import collections

def solve(N):
    two = N & -N
    N //= two

    lpf = [n for n in range(N * 2)] # Largest prime factor
    for p in range(2, len(lpf)):
        if lpf[p] != p:
            continue
        for i in range(p*2, len(lpf), p):
            lpf[i] = p

    def factorise(n):
        ret = collections.Counter()
        while n > 1:
            ret[lpf[n]] += 1
            n //= lpf[n]
        return ret

    ret = N
    for i in range(1, N):
        factors = factorise(N + i) + factorise(N - i)
        cnt = 1
        for p, e in factors.items():
            if p % 4 == 1:
                cnt *= e + 1
            elif p % 4 == 3 and e % 2 == 1:
                cnt = 0
                break
        ret += cnt * i * 4

    return ret * 6 * two


if __name__ == '__main__':
    print(solve(45))
    print(solve(10**10))
