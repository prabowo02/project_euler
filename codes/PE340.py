# Assume a > 2c

# When b - a < n <= b
# F(n) = F(a + F(a + F(a + a + n - c))) = F(3a + n - 2c) = 4a + n - 4c

# When b - 2a < n <= b - a
# F(n) = F(a + F(a + F(a + 5a + n - 4c))) = 8a + n - 7c

# When b - 3a < n <= b - 2a
# F(n) = F(a + F(a + F(a + 9a + n - 7c))) = 12a + n - 10c

# When b - ka < n <= b - (k-1)a
# F(n) = F(a + F(a + F(a + (4k-4)a + n - (3k-2)c))) = 4ka + n - (3k-1)c


def S(a, b, c):
    assert a > c*2

    n = (b + 1) // a
    ans = 4 * n * (n + 1) // 2 * a * a
    ans -= (4 * n + 3 * (n - 1) * n // 2) * c * a

    ans += (4 * (n + 1) * a - (4 + 3 * n) * c) * ((b + 1) % a)

    ans += (b + 1) * b // 2

    return ans


if __name__ == '__main__':
    print(S(21**7, 7**21, 12**7) % 10**9)
    # 291504964
