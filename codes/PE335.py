def M(n):
    ls = [1 for _ in range(n)]
    cur = 0
    ones = n
    ret = 0
    while True:
        if ls[cur] == 1:
            ones -= 1

        k = ls[cur]
        ls[cur] = 0

        for i in range(k):
            cur += 1
            cur %= n

            if ls[cur] == 1:
                ones -= 1
            ls[cur] += 1
            if ls[cur] == 1:
                ones += 1

        ret += 1
        if ones == n:
            break

    return ret


if __name__ == '__main__':
    print(M(5))
    print(M(100))

    # Intuition: the pointer will go around for n times, and most of the time will only carry 1 bean
    # So I'm trying to find patterns for n^2 - M(n);
    # For n = 2^k + 1, apparently n^2 - M(n) = 3^k + 1; M(n) = 4^k + 2^(k+1) - 3^k

    # for i in range(15):
    #     n = 2**i + 1
    #     res = M(n)
    #     print(n, res, n**2 - res)

    mod = 7**9
    N = 10**18
    ans = (pow(4, N+1, mod) - 1) * pow(3, -1, mod) + 2 * (pow(2, N+1, mod) - 1) - (pow(3, N+1, mod) - 1) * pow(2, -1, mod)
    print(ans % mod)
