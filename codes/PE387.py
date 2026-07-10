import functools


def solve(N):
    def digit_sum(n):
        return sum([int(s) for s in str(n)])

    def is_prime(n):
        if n <= 1:
            return False
        i = 2
        while i*i <= n:
            if n % i == 0:
                return False
            i += 1
        return True

    # Right truncatable Harshad numbers
    rharshad = list(range(1, 10))
    for num in rharshad:
        for i in range(10):
            nnum = num * 10 + i
            if nnum >= N:
                break
            if nnum % digit_sum(nnum) == 0:
                rharshad.append(nnum)

    # Strong, right truncatable Harshad
    sharshad = [num for num in rharshad if is_prime(num // digit_sum(num))]

    ret = 0
    for num in sharshad:
        for i in range(10):
            t = num * 10 + i
            if t < N and is_prime(t):
                ret += t
    return ret


if __name__ == '__main__':
    print(solve(10000))
    print(solve(10**14))
