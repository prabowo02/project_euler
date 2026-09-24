import math


def P(N, mod=10**9+7):
    points = []
    for i in range(1, math.isqrt(N) + 1):
        for j in range(1, math.isqrt(N) + 1):
            s = i*i + j*j
            if math.isqrt(s)**2 == s:
                points.append((i*i, j*j))

    points.append((N, N))

    fact = [1 for _ in range(N*2 + 1)]
    for i in range(1, len(fact)):
        fact[i] = fact[i - 1] * i % mod
    ifact = [1 for _ in range(len(fact))]
    ifact[-1] = pow(fact[-1], -1, mod)
    for i in range(len(fact) - 2, 0, -1):
        ifact[i] = ifact[i + 1] * (i + 1) % mod

    def C(n, k):
        return ifact[k] * ifact[n - k] * fact[n] % mod

    def walk(x, y):
        if x < 0 or y < 0:
            return 0
        return C(x + y, x)

    ans = [0 for _ in points]

    for i in range(len(points)):
        ans[i] = walk(points[i][0], points[i][1])
        for j in range(i):
            ans[i] = (ans[i] - ans[j] * walk(points[i][0] - points[j][0], points[i][1] - points[j][1])) % mod

    return ans[-1]


if __name__ == '__main__':
    print(P(5))
    print(P(16))
    print(P(1000))
    print(P(10**7))
