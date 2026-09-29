def W(N, mod=10**9+7):
    t = pow(2, N, mod)
    perm = t
    a, b = 1, 1
    res = 0
    for i in range(N - 1):
        # number of distinct (i+2) N-bit strings s.t. their XOR is 0
        # dp(n) = perm(2^N, n-1) - (n-1) * (2^N-n+2) * dp(n-2)
        a, b = b, (perm - (i + 1) * (t - i) * a) % mod
        perm = perm * (t - i - 1) % mod
        res = (b - (i + 2) * res) % mod

    return (perm * pow(t, -1, mod) * (t - N) - res) % mod


if __name__ == '__main__':
    print(W(1))
    print(W(2))
    print(W(3))
    print(W(5))
    print(W(100))
    print(W(10**7))
