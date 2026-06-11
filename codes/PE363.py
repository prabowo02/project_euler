# Cubic Bezier curves

# B(t) = (1-t)^3 P0 + 3(1-t)^2 t P1 + 3(1-t) t^2 P2 + t^3 P3
# B'(t) = 3(1-t)^2 (P1 - P0) + 6(1-t)t (P2 - P1) + 3t^2 (P3 - P2)

# P0 = (1, 0)
# P1 = (1, v)
# P2 = (v, 1)
# P3 = (0, 1)

# t=0 --> x=1
# t=1 --> x=0

# x(t) = (1-t)^3 + 3(1-t)^2 t + 3(1-t) t^2 v
# x'(t) = 6(1-t)t (v-1) + 3t^2 (-v)

# y(t) = 3(1-t)^2 tv + 3(1-t)t^2 + t^3
# y'(t) = 3(1-t)^2 v + 6(1-t) (1-v)

# Area = int y dx
# = int (3v (1-t)^2 t + 3(1-t) t^2 + t^3)(6(v-1) (1-t)t - 3v t^2) dt
# = int (18v(v-1) (1-t)^3 t^2 + (18(v-1) - 9v^2) (1-t)^2 t^3 + (6(v-1) - 9v) (1-t) t^4 - 3v t^5) dt
# = int ((18v^2-18v)(-t^5+3t^4-3^t+t^2) + (-9v^2+18v-18)(t^5-2t^4+t^3) + (-3v-6)(-t^5+t^4) - 3v t^5) dt
# = int (-27v^2 + 36v - 12) t^5 + (72v^2 - 93v + 30) t^4 + (-63v^2 + 72v - 18) t^3 + (18v^2 - 18v) t^2 dt
# = -[ (-27v^2 + 36 - 12) / 6 + (72v^2 - 93v + 30) / 5 + (-63v^2 + 72v - 18) / 4 + (18v^2 - 18v) / 3 ]
# = -3/20 v^2 + 3/5 v + 1/2

# Solving pi/4 = -3/20 v^2 + 3/5 v + 1/2
# v = 2 - sqrt(66 - 15pi) / 3

# Arc length:
# int sqrt(x'(t)^2 + y'(t)^2) dt
# = int sqrt( (6(1-t)t (v-1) - 3v t^2)^2 + (3v (1-t)^2 + 6(1-v)(1-t))^2 ) dt

import math


def solve():
    v = 2 - (66 - math.pi*15)**0.5 / 3
    ans = 0

    ITER = 10**6
    for i in range(ITER):
        t = i / ITER
        dx = 6 * (v - 1) * (1 - t) * t - 3 * v * t**2
        dy = 3 * v * (1 - t)**2 + 6 * (1 - v) * (1 - t) * t
        ans += (dx*dx + dy*dy)**0.5

    L = ans / ITER

    return (L - math.pi/2) / (math.pi/2) * 100


if __name__ == '__main__':
    print('{:.12f}'.format(solve()))
