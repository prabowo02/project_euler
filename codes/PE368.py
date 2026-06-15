# dp[k][n][d][s] --> sum of all 1/x^k such that the decimal representation of x
#  is of length n ending with d, and the last digit has occured consecutively for s times

# Transition by "appending" a digit:
# sum_x(1 / (10x + d)^k) = sum_x((10x)^{-k} (1 + d/(10x))^{-k})
# sum_x((10x)^{-k} sum_i (-1)^i C(k+i-1, i) (d/10x)^i)
# sum_i sum_x 10^{-k} C(k+i-1, i) (-d/10)^i 1/x^{i+k}

import math


def solve():
    K = 15

    dp1 = [[0 for d in range(10)] for k in range(K)]
    dp2 = [[0 for d in range(10)] for k in range(K)]

    ans = sum([1 / i for i in range(1, 100)])
    for i in range(10, 100):
        if i // 10 == i % 10:
            for k in range(1, K):
                dp2[k][i % 10] += 1 / i**k
        else:
            for k in range(1, K):
                dp1[k][i % 10] += 1 / i**k

    for n in range(3, 20000):
        ndp1 = [[0 for d in range(10)] for k in range(K)]
        ndp2 = [[0 for d in range(10)] for k in range(K)]
        for nd in range(10):
            for d in range(10):
                if d == nd:
                    for k in range(1, K):
                        ndp2[k][nd] += 10**-k * sum(math.comb(k+i-1, i) * (-nd/10)**i * dp1[i+k][d] for i in range(K-k))
                else:
                    for k in range(1, K):
                        ndp1[k][nd] += 10**-k * sum(math.comb(k+i-1, i) * (-nd/10)**i * (dp1[i+k][d] + dp2[i+k][d]) for i in range(K-k))
        dp1, dp2 = ndp1, ndp2
        # print(sum(dp1[1]) + sum(dp2[1]))
        ans += sum(dp1[1]) + sum(dp2[1])

    return ans

if __name__ == '__main__':
    print('{:.10f}'.format(solve()))
