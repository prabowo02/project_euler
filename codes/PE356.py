# The roots are: two of them near zero, and one near 2^n
# Let a, b, c be the roots

# From Vieta's
# a + b + c = 2^n
# ab + ac + bc = 0
# abc = -n

# floor(a_n^k) must be a^k + b^k + c^k - 1, because b^k + c^k is near zero, and a^k + b^k + c^k is an integer

# a^{k+1} + b^{k+1} + c^{k+1} 
# = (a^k + b^k + c^k)(a + b + c) - (a^{k-1} + b^{k-1} + c^{k-1})(ab + ac + bc) + (a^{k-2} + b^{k-2} + c^{k-2})(abc)
# = (a^k + b^k + c^k) 2^n - n (a^{k-2} + b^{k-2} + c^{k-2})

# a^2 + b^2 + c^2 = (a + b + c)^2 - 2(ab + ac + bc)

# floor(a_n^k)
def solve(n, k, mod=10**8):
    mat = [
      [pow(2, n, mod), 0, -n % mod],
      [1, 0, 0],
      [0, 1, 0],
    ]

    def multiply(A, B):
        C = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        for i in range(3):
            for j in range(3):
                for k in range(3):
                    C[i][j] += A[i][k] * B[k][j]
                C[i][j] %= mod
        return C

    def power(A, n):
        res = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
        while n > 0:
            if n & 1:
                res = multiply(res, A)
            n >>= 1
            A = multiply(A, A)
        return res

    mat = power(mat, k - 2)
    return (mat[0][0] * pow(2, n * 2, mod) + mat[0][1] * pow(2, n, mod) + mat[0][2] * 3 - 1) % mod


if __name__ == '__main__':
    print(sum(solve(n, 987654321) for n in range(1, 31)) % 10**8)
