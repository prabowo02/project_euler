import decimal


def R(m, n):
    m += 1

    # sum_{0 <= i <= n}(r*i + c)
    def S(r, c, n):
        if int(r * n + c) == 0:
            return 0
        if r >= 1:
            return int(r) * n * (n + 1) // 2 + S(r - int(r), c, n)
        if c >= 1:
            return int(c) * (n + 1) + S(r, c - int(c), n)

        m = int(r*n + c)
        return S(1/r, n - (m-c)/r + 1, m - 1)

    # Count number of lattice s.t. (y/x)^2 >= k
    def count_lattice(k):
        sk = decimal.Decimal(k).sqrt()

        if sk == int(sk):
            sk = int(sk)
            w = n // sk
            return (w - m + 1) * (n + 1) - sk * (m + w) * (w - m + 1) // 2

        y = int(sk * m)
        return S(1 / sk, y / sk - (m - 1), n - y)

    ans = 0
    for y in range(1, n**2 // m**2 + 1):
        if y % 2 == 0:
            ans -= count_lattice(y)
        else:
            ans += count_lattice(y)
    return ans


if __name__ == '__main__':
    print(R(0, 100))
    print(R(100, 10000))
    print(R(2 * 10**6, 10**9))
