def modified_collatz(n):
    ret = ''
    while n > 1:
        if n % 3 == 0:
            ret += 'D'
            n //= 3
        elif n % 3 == 1:
            ret += 'U'
            n = (4 * n + 2) // 3
        elif n % 3 == 2:
            ret += 'd'
            n = (2 * n - 1) // 3
    return ret

def main():
    s, lim = 'UDDDUdddDDUDDddDdDddDDUDDdUUDd', 10**15

    rem, mod = 0, 1
    for c in s[::-1]:
        rem, mod = rem * 3, mod * 3
        if c == 'D':
            # Do nothing
            pass
        elif c == 'U':
            rem = (rem - 2) * pow(4, -1, mod) % mod
        elif c == 'd':
            rem = (rem + 1) * pow(2, -1, mod) % mod

    ans = rem + (lim - rem + mod) // mod * mod
    assert modified_collatz(ans).startswith(s)
    print(ans)


if __name__ == '__main__':
    main()
