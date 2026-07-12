# Derivative of sqrt(1 - x^2) = -x / sqrt(1 - x^2)
# Derivative of x sqrt(1 - x^2) = (1 - 2x^2) / sqrt(1 - x^2)

# f(x_{k-1}) = (x_k - x_{k-1}) * sqrt(1 - x_{k-1}^2) + f(x_k)
# f(x_{k-1}) = (x_k - x_{k-1}) * sqrt(1 - x_{k-1}^2) + (x_{k+1} - x_k) * sqrt(1 - x_k^2) + f(x_{k+1})

# Partial derivative wrt x_k and set to 0:
# sqrt(1 - x_{k-1}^2) - x_{k+1} x_k / sqrt(1 - x_k^2) - (1 - 2x_k^2) / sqrt(1 - x_k^2) = 0
# x_{k+1} = sqrt(1 - x_k^2) / x_k * (sqrt(1 - x_{k-1}^2) - (1 - 2x_k^2) / sqrt(1 - x_k^2))
import math


def solve(n):
    n = n // 2 + 1

    def nextX(x0, x1):
        y0, y1 = math.sqrt(1 - x0**2), math.sqrt(1 - x1**2)
        return y1/x1 * (y0 - (1 - 2*x1**2) / y1)

    l, r = 0, 1
    for _ in range(50):
        x = (l + r) / 2

        x0, x1 = 0, x
        for i in range(n - 1):
            x0, x1 = x1, nextX(x0, x1)
            if x1 + 1e-15 >= 1:
                break

        if x1 + 1e-15 >= 1:
            r = x
        else:
            l = x

    ret = 0
    x0, x1 = 0, l
    for i in range(n):
        ret += (x1 - x0) * math.sqrt(1 - x0**2)
        x0, x1 = x1, nextX(x0, x1)

    return ret * 4

if __name__ == '__main__':
    print(solve(10))
    print('{:.10f}'.format(solve(400)))
