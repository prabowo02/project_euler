from fractions import Fraction

primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263]
phi = []
prod = []

def precomp():
    current_phi, current_prod = 1, 1
    for p in primes:
        current_phi *= Fraction(p-1, p)
        current_prod *= p

        phi.append(current_phi)
        prod.append(current_prod)


def solve(a, b):
    q = Fraction(a, b)

    l, r = 0, len(primes) - 1
    idx = -1
    while l <= r:
        mid = (l + r) // 2

        if phi[mid] < q:
            idx = mid
            r = mid-1
        else:
            l = mid+1

    # phi * k*prod / (k*prod-1) < a/b
    # phi * k*prod < k*prod * a/b - a/b
    # 
    # We know: phi < a/b
    # a/b < k*prod*(a/b - phi)

    k = (q / (prod[idx] * (q - phi[idx]))).__floor__() + 1
    if k < primes[idx+1]:
        return prod[idx] * k

    return prod[idx+1]


if __name__ == '__main__':
    precomp()
    for tc in range(int(input())):
        a, b = [int(i) for i in input().split()]
        print(solve(a, b))
