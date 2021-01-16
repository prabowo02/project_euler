# sum_{i=0}^m (k-i)^2 = sum_{i=1}^m (k-i + x)^2
# k^2 = sum_{i=1}^m (2(k-i)x) + mx^2
# k^2 = (2k-m-1)mx + mx^2
# (k - mx)^2 = mx^2 - m^2x - mx + m^2x^2
# (k - mx) = sqrt(mx(x - m - 1 + mx))
# k = sqrt(mx(m + 1)(x - 1)) + mx

# brute for m,
# x > m

# m(m + 1)x(x - 1) is a square

# x(x - 1) D is a square

# 4x(x - 1)D is a square
# ((2x - 1)^2 - 1)D is a square
# Dy^2 - D = x^2
# x^2 - Dy^2 = -D

# if D is squarefree, then the only fundamental solution is (0, 1)

# Pell: x_{k+1} = x1xk + dy1yk; y_{k+1} = x1yk + y1xk
# Generalized: X = ux + dyv; Y = xv + uy


# Returns the fundamental sol to x^2 - Dy^2 = 1
def pell(d):
    p0, q0, p1, q1 = 0, 1, 1, 0
    a = d**0.5

    while True:
        ia = int(a)
        p0, q0, p1, q1, a = p1, q1, p1*ia + p0, q1*ia + q0, 1 / (a - ia)

        if p1**2 - d*q1**2 == 1:
            return p1, q1
        

# Generate sols for x^2 - Dy^2 = -D, D squarefree
def dio(d):
    u, v = pell(d)
    x, y = 0, 1

    while True:
        x, y = x*u + d*y*v, x*v + y*u
        yield x, y


def square_free(n):
    i, squares = 2, 1
    while i*i <= n:
        while n % (i*i) == 0:
            n //= i*i
            squares *= i
        i += 1
    return n, squares


def solve(n):
    m, sm1 = 1, square_free(1)
    ans = set()
    while m*m*2 <= n:
        sm, sm1 = sm1, square_free(m + 1)
        square_free_d, squares_d = sm[0] * sm1[0], sm[1] * sm1[1]
        for s, x in dio(square_free_d):
            if s % 2 == 1 or x % 2 == 0:
                continue
            s, x = s // 2, (x + 1) // 2
            if x <= m:
                continue
            k = s * squares_d + m * x
            if k > n:
                break
            ans.add(k)
        m += 1

    return sum(ans)


if __name__ == '__main__':
    n = int(input())
    print(solve(n))
