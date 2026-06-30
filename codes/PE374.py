# 2
# 3
# 4
# 2 3
# 2 4
# 3 4
# 3 5
# 2 3 4

def solve(N, mod):
    ans = 1

    m, cur = 0, 1
    fact, inv = 2, pow(2, -1, mod)
    while cur + m + 3 <= N:
        m += 1
        fact = fact * (m + 2) % mod
        inv = (inv + pow(m + 2, -1, mod)) % mod
        ans += (fact * inv + fact * pow(2, -1, mod) * pow(m+2, -1, mod) * (m + 3)) * m
        ans %= mod
        cur += m + 2

    m += 1
    fact = fact * (m + 2) % mod
    for i in range(m + 2, 1, -1):
        if cur < N:
            ans = (ans + fact * pow(i, -1, mod) * m) % mod
            cur += 1

    return ans


if __name__ == '__main__':
    print(solve(100, 10**15 + 37))
    print(solve(10**14, 982451653))
