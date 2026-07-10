# Heron: A = 1/4 sqrt(4 a^2 b^2 - (a^2 + b^2 - c^2)^2)

# A = 1/4 sqrt(4(1+b^2)(1+c^2) - 4) = 1/2 sqrt(b^2 + c^2 + b^2c^2)
# 4A^2 = b^2 + c^2 + b^2 c^2

# It must be that b and c are even
# So we can rewrite: A^2 = x^2 + y^2 + 4x^2 y^2
# A^2 - (4x^2 + 1) y^2 = x^2

# Fix x, and we solve the Pell equation
# A solution for A^2 - (4x^2 + 1) y^2 = 1
#   is A = 8x^2 + 1 and y = 4x
# Meaning for a solution to the original (A, y), we can
#   find the next solution by ((8x^2 + 1) * A + (4x^2 + 1) * 4x * y, 4x * A + (8x^2 + 1) * y)

# Since x and y are "symmetry", we generate next step by swapping and sign flipping them
# I don't know why this is exhaustive

import math

def S(N):
    def dfs(x, y, A):
        A0, y0 = 8*x*x + 1, 4*x
        D = 4*x*x + 1

        nA, ny = A0*A + D*y0*y, y0*A + A0*y
        if nA > N:
            return 0

        return nA + dfs(x, ny, nA) + dfs(ny, x, nA) + dfs(ny, -x, nA)

    return sum(dfs(x, 0, x) for x in range(1, math.isqrt(N)))

if __name__ == "__main__":
    print(S(10**6))
    print(S(10**10))
