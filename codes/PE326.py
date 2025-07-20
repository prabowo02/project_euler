# From OEIS: a(n) has a pattern of period 6
# It can also be proven that the sum has period 6M

def a(n):
    m = n % 6
    if m == 0:
        return n // 2
    elif m == 1:
        return n // 6 * 4 + 1
    elif m == 2:
        return n // 2
    elif m == 3:
        return n // 6
    elif m == 4:
        return n - 1
    elif m == 5:
        return n // 6


def solve(N, M):
    counter = [0 for _ in range(M)]
    counter[0] = 1
    s = 0
    for i in range(M * 6):
        s += a(i + 1)
        s %= M
        counter[s] += (N + 1) // (M * 6) + (i + 1 < (N + 1) % (M * 6))
    assert s == 0

    return sum(c * (c - 1) // 2 for c in counter)



if __name__ == '__main__':
    print(solve(10, 10))
    print(solve(10**4, 10**3))
    print(solve(10**12, 10**6))
