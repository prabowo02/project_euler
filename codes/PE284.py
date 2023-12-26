# x^2 = x mod 14^n
# x(x - 1) = 0 mod 14^n

# x = 0 (mod 2^n)
# x = 1 (mod 2^n)

# x = 0 (mod 7^n)
# x = 1 (mod 7^n)

# x = 0, 1 are trivial sols, and not n-digit

# As n decreases, you only need to remove the n-th digit of base 14-rep of x 


def solve(N):
    def to_base14(n):
        ret = []
        while n > 0:
            ret.append(n % 14)
            n //= 14
        return ret[::-1]

    ans = 1  # 1 is 1-digit steady square
    for x in [7**N * pow(7**N, -1, 2**N) % 14**N, 2**N * pow(2**N, -1, 7**N) % 14**N]:
        x = to_base14(x)
        x = (N - len(x)) * [0] + x  # Ensure length is n

        nonzero_count = 0
        for dig in x:
            if dig != 0:
                nonzero_count += 1
            ans += dig * nonzero_count

    print(ans)
    print(''.join(['0123456789abcd'[dig] for dig in to_base14(ans)]))


if __name__ == '__main__':
    solve(10000)    
