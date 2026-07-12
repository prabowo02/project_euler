# f(x) = 1 + 1/x * int_F^x 2(x-y)/x f(y) dy
# f(x) = 1 + 2/x^2 [ x int_F^x f(y) dy - int_F^x yf(y) dy ]

# d/dx xF(x) = F(x) + xf(x)
# xF(x) = int F(x) + int xf(x)
# int F(x) = xF(x) - int xf(x)

# Rewrite f(x) --> f''(x)
# And assume f'(F) = f(F) = 0

# f''(x) = 1 + 2f(x)/x^2
# x^2 f''(x) - 2f(x) - x^2 = 0

# This is second-order ODE, or Euler-Cauchy equation, to be exact.
# Solving it, you get f(x) = Ax^2 + B/x + x^2 log(x)/3
# f'(x) = Ax + B/x^2 + 2/3 xlog(x) (note, here, A and B absorbs whatever constants there are)
# f(x) = A+2/3 - 2B/x^3 + 2/3 log(x)

# We know:
# f'(F) = AF + B/F^2 + 2/3 F log(F) = 0; and
# f(F) = A+2/3 - 2B/F^3 + 2/3 log(F) = 1

# From f'(R): B/F^2 = -2/3 F log(F) - AF
# subs into f(R): A+2/3 = 1 - 4/3 log(F) - 2A - 2/3 log(F)
# A = 1/9 - 2/3 log(F)
# B = -2/3 F^3 log(F) - F^3 (1/9 - 2/3 log(F)) = 1/9 F^3

# We want:
# f(1) = A+2/3 - 2B = 7/9 - 2/3 log(F) + 2/9F^3
# So E(x) = 7/9 + 2/3 log(x) + 2/(9x^3)

import math


def solve(x):
    return 7/9 + 2/3 * math.log(x) + 2/(9*x**3)


if __name__ == '__main__':
    print(solve(1))
    print(solve(2))
    print(solve(7.5))
    print('{:.10f}'.format(solve(40)))
