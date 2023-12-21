# Note that the modulo 1234567891 is a prime
# There are two kinds of supernatural triangles: (a, b, b+1) and (a, a+1, b)

# For the first kind, it's actually coming from tree of primitive pythagorean by repeatedly following a particular branch/transition.
# It can be proven by induction that such transition always gives b, b+1
# The side length for this case is a = 2k+1, b = 2k^2 + 2k, (for k >= 1) hence perimiter = 4k^2 + 6k + 2
# The number of such triangles is 10^(5 * 10^9) / 2 - 1
# The formula for the perimeter sum is: 4/3 k^3 + 5k^2 + 17/3k

# For the second kind, it's also coming from the same tree, but following other particular transition.
# It can be found that the transition the sum of the perpendicular (say a) and the hypothenuse (b) will be updated as: a, b := 3a + 4b, 2a + 3b
# Hence, the kth iteration can be written as the matrix form [[3 4][2 3]]^n * [7 5] (assume the base is the triple (3, 4, 5)).
# Find the eigendecomposition of the square matrix.
# The eigenvectors are [sqrt(2) 1], with eigenvalue 2sqrt(2)+3 and [-sqrt(2) 1] with eigenvalue -2sqrt(2)+3
# After some algebra, we found that the perimeter of the nth transition is:
# (6 + 17/4 sqrt(2))(3 + 2sqrt(2))^n + (6 - 17/4 sqrt(2))(3 - 2sqrt(2))^n

# The number of such triangles is 13062480692, and the perimeters can be computed within minutes, by doing the naive recursion 3a+4b, 2a+3b (or in log time using matrix expo)

import math

MOD = 1234567891
K = 10**10  # Compute up to perim 10^K

k1 = (pow(10, K // 2 % (MOD - 1), MOD) * pow(2, MOD - 2, MOD) - 1) % MOD
first = (k1**3 * 4 + k1**2 * 15 + k1 * 17) * pow(3, MOD - 2, MOD) % MOD

k2 = math.floor((K * math.log(10) - math.log(6 + 17/4*math.sqrt(2))) / math.log(3 + 2*math.sqrt(2)))
second = 0
a, b = 7, 5
for i in range(k2):
  a, b = (3*a + 4*b) % MOD, (2*a + 3*b) % MOD
  second = (second + a + b) % MOD
# second = 101648491 should be the result

print((first + second) % MOD)
