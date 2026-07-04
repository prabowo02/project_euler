import functools


def berlekamp_massey(S):
    C, B, e, m = [1], [1], 1, 0

    for n in range(len(S)):
        d = S[n]
        for i in range(1, len(C)):
            d += C[i] * S[n - i]
        m += 1

        if abs(d) < 1e-8:
            continue

        scale = d / e
        D = [0] * m + [scale * b for b in B]

        if len(D) > len(C):
            B = C[:]
            e = d
            C += [0] * (len(D) - len(C))
            m = 0

        for i in range(len(D)):
            C[i] -= D[i]

    for i in range(len(C)):
        C[i] = -int(round(C[i]))

    return C[1:]


def mul(A, B, mod):
    n = len(A)
    return [[sum(A[i][k] * B[k][j] for k in range(n)) % mod
             for j in range(n)] for i in range(n)]

def power(A, y, mod):
    ret = [[1 if i == j else 0 for j in range(len(A))] for i in range(len(A))]
    op = A
    while y:
        if y & 1:
            ret = mul(ret, op, mod)
        op = mul(op, op, mod)
        y //= 2
    return ret


def f(n):
    s = [1, 2, 3]
    for i in range(20):
        s.append(s[-1] + s[-3])

    @functools.cache
    def count_larger(x, t):
        if x < 0:
            return 1 if t == 0 else 0
        return count_larger(x - 1, t) + count_larger(x - 1, max(0, t - s[x]))

    cnt = [count_larger(i - 1, s[i] + 1) for i in range(len(s))]
    for i in range(1, len(cnt)):
        cnt[i] += cnt[i - 1]

    a = berlekamp_massey(cnt)
    
    if n-1 < len(a):
        return cnt[n - 1]

    A = [[1 if i == j + 1 else 0 for j in range(len(a))] for i in range(len(a))]
    A[0] = a

    mod = 10**9
    A = power(A, n - len(a), mod)
    return sum([A[0][j] * cnt[len(a) - j - 1] for j in range(len(a))]) % mod


if __name__ == '__main__':
    print(f(5))
    print(f(10))
    print(f(25))
    print(f(10**18))
