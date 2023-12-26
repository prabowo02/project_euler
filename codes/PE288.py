def solve(p, q, mod):
    s = 290797
    pn, den = 1, pow(1 - p, -1, mod)
    ans = 0
    for n in range(q):
        s, pn = s * s % 50515093, pn * p % mod
        ans += (s % p) * (1 - pn) * den
    print(ans % mod)

if __name__ == '__main__':
    solve(3, 10000, 3**20)
    solve(61, 10**7, 61**10)
