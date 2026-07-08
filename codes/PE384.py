# b(4n) and b(4n+1) will have the same value
# b(4n+2) and b(4n+3) will cancel each other
# Furthermore, b(4n) = b(4n+1) = b(n)

# So we have s(4n+3) = s(4n+1) = 2s(n)
# And s(4n+2) = s(4n) = s(n) +/- 1

# Let count(n, m, b, t), where 0 <= m < 4, be the number i <= n, 
#   s.t. s(4i + m) = t and b(4i+m) = (-1)^b
# Find the transition based on t % 2

import functools


@functools.cache
def count(n, m, b, t):
    if n < 0:
        return 0
    if n < 2:
        ls = [1, 2, 3, 2, 3, 4, 3, 4]
        ret = 0
        for i in range(m, n*4 + m + 1, 4):
            if ls[i] == t and bin(i & (i >> 1)).count('1') % 2 == b:
                ret += 1
        return ret
    if t == 1:
        return 1 if (m, b) == (0, 0) else 0
    if t == 2:
        return 1 if (m, b) in ((1, 0), (3, 1)) else 0
    if t == 3:
        return 1 if (m, b) in ((2, 0), (2, 1), (0, 0)) else 0
    if t % 2 == 0:
        if m == 3:
            return count(n // 4, 0, b ^ 1, t // 2) + \
                count((n - 1) // 4, 1, b, t // 2) + \
                count((n - 2) // 4, 2, b ^ 1, t // 2) + \
                count((n - 3) // 4, 3, b, t // 2)
        if m == 1:
            return sum(count((n - i) // 4, i, b, t//2) for i in range(4))
        return 0

    if m == 2:
        return count(n // 4, 0, b, (t - (-1)**b) // 2) + \
            count((n - 1) // 4, 1, b ^ 1, (t - (-1)**b) // 2) + \
            count((n - 2) // 4, 2, b, (t - (-1)**b) // 2) + \
            count((n - 3) // 4, 3, b ^ 1, (t - (-1)**b) // 2)
    if m == 0:
        return sum(count((n - i) // 4, i, b, (t + (-1)**b) // 2) for i in range(4))
    return 0


# Count number of s(i) = t, for i <= n
def f(n, t):
    return sum(count((n - i) // 4, i, 0, t) + \
            count((n - i) // 4, i, 1, t) for i in range(4))


def g(t, c):
    r = 1
    while f(r, t) < c:
        r *= 2
    l = r // 2

    ret = None
    while l <= r:
        mid = (l + r) // 2
        if f(mid, t) < c:
            l = mid + 1
        else:
            r = mid - 1
            ret = mid

    return ret


if __name__ == '__main__':
    print(g(3, 3))
    print(g(4, 2))
    print(g(54321, 12345))
    fib = [1, 1]
    while len(fib) < 46:
        fib.append(fib[-1] + fib[-2])
    print(sum(g(fib[i], fib[i - 1]) for i in range(2, 46)))
