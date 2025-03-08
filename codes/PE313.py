# S(m, n) is
# - m + n + 6n + 5(m - n - 1) = 6m + 2n - 5; if m > n
# - 2n + 3(2n - 1) = 8n - 3; if m = n

# When m = n, S(m, n) = 5 (mod 8), which is not a quadratic residue
#   so we consider only the case when m > n

# Fix p^2:
# n = (p^2 - 6m + 5) / 2; p must be odd
# n > 0 ==> m < (p^2 + 5) / 6
# n < m ==> m > (p^2 + 5) / 8

def solve(n):
    def odd_primes():
        is_primes = [not (i % 2 == 0) for i in range(n)]
        for p in range(3, n, 2):
            if not is_primes[p]:
                continue
            yield p
            for i in range(p * 2, n, p):
                is_primes[i] = False

    ans = 0
    for p in odd_primes():
        p2 = p**2 + 5
        ans += p2 // 6 - p2 // 8
        if p2 % 6 == 0:
            ans -= 1

    return ans * 2


if __name__ == '__main__':
    print(solve(100))
    print(solve(10**6))
