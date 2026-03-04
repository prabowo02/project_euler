# A single cut:
# (k+1)a / kb <--> ka / (k+1)b

# when (k+1)a < kb, we are doing cut in one direction
# when (k+1)a > kb, we are doing it in other directions
# So we just count how many (k, a, b) such that (k+1)a < n and kb < n
  # floor(n/k) * floor(n/(k+1)) for k = 1 .. n
# The double-count comes from when a'g = (b'+1)g (where g is gcd(a, b)), because then 
#   is possibly handled by:
#   - (k+1)a'g * kb'g is handled by a'(k+1)g * b'kg, so we subtract those for a < k+1
#   - kb'g * (k+1)a'g is handled by b'kg * a'(k+1)g, so we subtract those for a >= k+1
# Double count also happens when a=b, so need to subtract floor(n/(k+1)) as well

# Example cuts:
# k=1, a=2, b=3
# (4, 3) --> (2, 6)
# k=2, a=1, b=2
# (3, 4) --> (2, 6)
# k=2, a=2, b=1
# (4, 1) --> (2, 2)


import functools
import math


def cubic_G(n):
    ans = 0
    cut = collections.defaultdict(list)
    for k in range(1, n):
        for a in range(1, n//(k+1) + 1):
            for b in range(1, n//k + 1):
                g = math.gcd(a, b)
                if a // g == b // g + 1:
                    continue
                if a == b:
                    continue

                prv = (k+1) * a, k * b
                nxt = k*a, (k+1)*b
                prv, nxt = tuple(sorted(prv)), tuple(sorted(nxt))
                cut[prv].append(nxt)
                ans += 1

    # for k, v in cut.items():
    #     print(k, v)
    return ans


def linear_G(n):
    @functools.cache
    def sum_floor(n):
        return sum(n // i - 1 for i in range(1, n+1))

    ans = 0
    for k in range(1, n):
        ans += (n // (k + 1)) * (n // k)
        ans -= n // (k + 1) # Exclude a = b
        ans -= sum_floor(n // (k + 1)) # Exclude a' = b' + 1

    return ans


def G(n):
    # return x when floor(n/x) and floor(n/(x+1)) may be different, 1 <= x <= n
    # It returns such O(sqrt(n)) number of points
    def floor_points(n):
        i, ret = 1, set()
        while i*i <= n:
            ret.add(i)
            ret.add(n // i)
            i += 1
        return ret

    # n/1 + n/2 + ...
    @functools.cache
    def floor_sum(n):
        points = sorted(floor_points(n) | {0}, reverse=True)
        ret = 0
        for i in range(1, len(points)):
            ret += n // points[i - 1] * (points[i - 1] - points[i])
        return ret

    # sum(n/(k+1) * n/k)
    def pair_floor_sum(n):
        points = floor_points(n)
        points = points | {p-1 for p in points}
        points = sorted(points, reverse=True)

        ret = 0
        for i in range(1, len(points)):
            ret += (n // (points[i - 1] + 1)) * (n // points[i - 1]) * (points[i - 1] - points[i])
        return ret

    # sum(floor_sum(n/k) - n/k)
    def floor_sum_sum(n):
        points = sorted(floor_points(n) | {0}, reverse=True)
        ret = 0
        for i in range(1, len(points)):
            ret += (floor_sum(n // points[i - 1]) - (n // points[i - 1])) * (points[i - 1] - points[i])
        return ret

    ans = pair_floor_sum(n)
    # ans -= floor_sum(n) - n  # Exclude a = b
    # ans -= floor_sum_sum(n) - (floor_sum(n) - n) # Exclude a' = b' + 1
    # The above two can be simplified to:
    ans -= floor_sum_sum(n)

    return ans


if __name__ == '__main__':
    # print(cubic_G(10))
    # print(cubic_G(1000))

    # print(linear_G(10))
    # print(linear_G(1000))
    # print(linear_G(10**5))

    print(G(10))
    print(G(1000))
    print(G(10**5))
    print(G(10**8))
    print(G(10**12)) # Takes minutes
