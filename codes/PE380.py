# Number of spanning trees is 1/n * prod(eigenvalues)
# Eigenvalues of a grid graph n*m is (4 - 2 cos(i pi/n) - 2 cos(j pi/n))

import math


def C(n, m):
    ret = -math.log10(n*m) + sum(
        math.log10(4 - 2*math.cos(math.pi*i/n) - 2*math.cos(math.pi*j/m))
        for i in range(n) for j in range(m) if (i, j) != (0, 0)
    )
    return '{:.4f}e{}'.format(10**(ret - int(ret)), int(ret))


if __name__ == '__main__':
    print(C(1, 1))
    print(C(2, 2))
    print(C(3, 4))
    print(C(9, 12))
    print(C(100, 500))
