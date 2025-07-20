import decimal
import math


def quadratic(n):
    E = [0]
    while len(E) <= n:
        two = 2**len(E)
        E.append((two + sum(math.comb(len(E), k) * E[k] for k in range(len(E)))) / (two - 1))
    return E[-1]


# E.G.F. is P(x) = (exp(x) - 1) + (exp(x/2) P(x/2))
# = sum_k(exp(x) - exp(x - x/2^k))
# = exp(x) sum_k(1 - exp(-x/2^k))
def linear(n):
    return sum([math.comb(n, k) / (1 - decimal.Decimal(1)/2**k) * (-1 if k % 2 == 0 else 1) for k in range(1, n + 1)])


if __name__ == '__main__':
      print('{:.10f}'.format(quadratic(10)))
      print('{:.10f}'.format(linear(10)))
      print('{:.10f}'.format(quadratic(20)))
      print('{:.10f}'.format(linear(20)))
      print('{:.10f}'.format(quadratic(32)))
      print('{:.10f}'.format(linear(32)))
