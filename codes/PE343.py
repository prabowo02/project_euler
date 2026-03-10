# f(n) = [largest prime factor of n+1] - 1

# n^3 + 1 = (n + 1)(n^2 - n + 1)
# n^2 - n + 1 = 0 (mod p) ==> n = (1 +/- sqrt(-3)) / 2 (mod p)

# Alternatively, directly factor n^3 + 1 = 0 (mod p), sol is -1, -n, -n^2


def tonelli_shanks(x, p):
    assert pow(x, (p - 1) // 2, p) == 1

    S = ((p - 1) & -(p - 1)).bit_length() - 1
    Q = (p - 1) >> S
    for z in range(1, p):
        if pow(z, (p - 1) // 2, p) == p - 1:
            break

    M, c, t, R = S, pow(z, Q, p), pow(x, Q, p), pow(x, (Q + 1) // 2, p)
    while True:
        if t == 0:
            return 0
        if t == 1:
            return R

        ti = t
        for i in range(1, M):
            ti = ti * ti % p
            if ti == 1:
                break

        assert ti == 1

        b = pow(c, pow(2, M - i - 1), p)
        M, c, t, R = i, b*b % p, t*b*b % p, R*b % p


def solve(N):
    lpf = [n for n in range(N + 2)] # largest prime factors
    for p in range(2, len(lpf)):
        if lpf[p] != p:
            continue
        for i in range(p, len(lpf), p):
            lpf[i] = p

    num = [n**2 - n + 1 for n in range(N + 1)]
    lpf2 = [1 for n in range(N + 1)] # largest prime factors for n^2 - n + 1
    for i in range(N + 1):
        while num[i] % 2 == 0:
            num[i] //= 2
            lpf2[i] = 2

        while num[i] % 3 == 0:
            num[i] //= 3
            lpf2[i] = 3

    for p in range(5, len(lpf)):
        if lpf[p] != p:
            continue

        if pow(-3, (p - 1) // 2, p) == p - 1:
            # -3 is quadratic non residue
            continue

        r = tonelli_shanks(p - 3, p)
        assert (1 + r) * (p + 1) // 2 % p in ()
        for i in range((1 + r) * (p + 1) // 2 % p, len(num), p):
            while num[i] % p == 0:
                num[i] //= p
                lpf2[i] = p
        for i in range((1 - r) * (p + 1) // 2 % p, len(num), p):
            while num[i] % p == 0:
                num[i] //= p
                lpf2[i] = p

    for i in range(len(num)):
        if num[i] > 1:
            lpf2[i] = num[i]

    return sum(max(lpf[i + 1], lpf2[i]) - 1 for i in range(1, N + 1))


if __name__ == '__main__':
    print(solve(100))
    print(solve(2000000))
