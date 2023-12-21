import itertools

def main(N):
    def is_prime(n):
        for p in range(2, n):
            if n % p == 0:
                return False
        return True

    def is_square(n):
        return int(n**0.5)**2 == n

    def prime_sum_2_squares(p):
        for i in range(1, p):
            if is_square(p - i*i):
                return (i, int((p - i*i)**0.5))

    primes = [p for p in range(2, N) if p % 4 == 1 and is_prime(p)]
    squares = [prime_sum_2_squares(p) for p in primes]

    def get_sum_a(squares):
        sols = [(0, 1)]
        for a, b in squares:
            nsols = []
            for c, d in sols:
                s1, s2 = (abs(a*c - b*d), abs(a*d + b*c)), (abs(a*c + b*d), abs(a*d - b*c))
                if s1[0] > s1[1]:
                    s1 = s1[1], s1[0]
                if s2[0] > s2[1]:
                    s2 = s2[1], s2[0]
                nsols.extend([s1, s2])
            sols = nsols
        return sum([a for a, b in sols]) // 2

    ans = 0
    for mask in range(1, 2**len(primes)):
        subset = [s for i, s in enumerate(squares) if (mask >> i) & 1]
        ans += get_sum_a(subset)

    return ans


if __name__ == '__main__':
    # N = int(input())
    print(main(150))