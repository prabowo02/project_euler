# Rearrange the inequality, then for a fixed i, we want:
# - (x_i)^{1/i} < (x_j + 1)^{1/j}, for all j

# Suppose that k is the minimum integer such that (x_k)^{1/k} = max((x_i)^{1/i})
# Then if we already know the value of (x_k)^{1/k}, then the value of x_i for i > k are uniquely determined
# i.e. find an x_i such that (x_k)^{1/k} is in [(x_i)^{1/i}, (x_i + 1)^{1/i})
# Similarly, for i < k, the value x_i may uniquely exist, or not exist.
# It doesn't exist if (x_k)^{i/k} is an integer, because then, k will not be the minimum integer.

# Since x_1 = 2, then we know that x_i must lie in between [2^i, 3^i)
# Suppose we fix x_k (and (x_k)^{1/k} is the max of all (x_i)^{1/i}), then x_{2k} can't use (x_k)^2 as its "maximum bound",
# and so does all the multiple of k (i.e. x_jk cant use (x_k)^{jk})
# Hence, we can compute the contribution of each i as seen from the function `test`

# Now, we observe that the function `test` actually computes mobius transform.
# Let a_n = 3^n - 2^n, and b_n = sum_{d|n} mu(d)*a_{n/d}. Our answer is then sum(b_n)

# We will use the Dirichlet hyperbola method to compute sum of b_n.
# Let B(n) = sum_{i <= n} b_i
# Let A(n) = sum_{i <= n} a_i; Note that A(n) has a closed form and is easy to compute
# Since b is Dirichlet convolution of a and mobius, then it follows that a is Dirichlet convolution of b and "1" (i.e. 1(x) = 1)
# 
# By the hyperbola method:
# A(n) = sum_{ij <= n} b_j
#      = sum_{i <= sqrt(n)} B_{n/i} + sum_{j <= sqrt(n)} (b_j * n/j) - sqrt(n) * B(sqrt(n))
# Rearranging them:
# B(n) = A(n) + sqrt(n) B(sqrt(n)) - sum_{j <= sqrt(n)} (b_j * n/j) - sum_{2 <= i <= sqrt(n)} B_{n/i}

# If we precompute B(n) for n <= sqrt(N), then the above can be computed using DP in O(N^{3/4})

import functools
import math


def test(n):
    n += 1
    ls = [3**i - 2**i for i in range(n)]
    for i in range(1, n):
        for j in range(i+i, n, i):
            ls[j] -= ls[i]
    return sum(ls)


def solve(n):
    mod = 10**9
    sn = math.isqrt(n) + 1

    b = [(pow(3, i, mod) - pow(2, i, mod)) % mod for i in range(sn)]
    for i in range(1, sn):
        b[i] %= mod
        for j in range(i+i, sn, i):
            b[j] -= b[i]
    preB = b[:]
    for i in range(1, len(preB)):
        preB[i] = (preB[i] + preB[i - 1]) % mod

    # Sum 3^1 + ... + 3^n
    @functools.cache
    def three(n):
        if n == 0:
            return 0
        n2 = n // 2
        ret = three(n2) * (1 + pow(3, n2, mod)) % mod
        if n % 2 == 1:
            ret = (ret + pow(3, n, mod)) % mod
        return ret

    @functools.cache
    def A(n):
        return (three(n) - (pow(2, n + 1, mod) - 2)) % mod

    @functools.cache
    def B(n):
        if n == 0:
            return 0
        if n < len(b):
            return preB[n]

        sn = math.isqrt(n)

        ret = A(n) + sn * B(sn)
        for i in range(1, sn + 1):
            ret -= b[i] * (n // i)
        for i in range(2, sn + 1):
            ret -= B(n // i)
        return ret % mod

    return B(n)


if __name__ == '__main__':
    print(solve(10))
    print(solve(20))
    print(solve(10**10))
