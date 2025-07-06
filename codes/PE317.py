# Let theta be the angle w.r.t. ground

# Speed function
# v(t) = v0 - gt

# Integrate from 0 to x / vsin(th):
# tan(th) x - 1/2 g x^2 / v^2 sec^2(th)

# Differentiate w.r.t. theta (find optimal angle for a fixed x)
# x sec^2(th) - g x^2 / v^2 sec^2(th) tan(th) = 0
# sec^2 (th) (x - g x^2 / v^2 tan(th)) = 0
# tan(th) = v^2 / gx
# sec(th) = sqrt(v^4 + g^2 x^2) / gx

# Substitute theta
# y = v^2 / g - 1/(2g v^2) (v^4 + g^2 x^2)
# y = v^2 / 2g - gx^2 / 2v^2

# Invert x and y
# x^2 = v^4 / g^2 - y 2v^2 / g

# Volume integrate from -h to v^2 / 2g
# V = int pi f(y)^2 dy
# V = pi [v^4 / g^2 y - v^2 / g y^2]_
# V = pi [v^6 / 4g^3 + v^4 / g^2 h + v^2 / g h^2]


import math


def solve(g, h, v):
    return math.pi * (v**6 / (4 * g**3) + v**4 / g**2 * h + v**2 / g * h**2)


if __name__ == '__main__':
    print('{:.4f}'.format(solve(g=9.81, h=100, v=20)))