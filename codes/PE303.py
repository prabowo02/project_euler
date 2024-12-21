import functools
import itertools

def solve(N):
    ret = 0
    for n in range(1, N + 1):
        @functools.cache
        def f(pos, mod=0):
            if pos == 0:
                return mod == 0
            return any(f(pos - 1, (mod * 10 + dig) % n) for dig in range(3))

        for length in itertools.count(len(str(n))):
            if not any(f(length - 1, dig % n) for dig in range(1, 3)):
                continue

            num, mod = '', 0
            for pos in range(length, 0, -1):
                for dig in range(1 if pos == length else 0, 3):
                    if f(pos - 1, (mod * 10 + dig) % n):
                        num += str(dig)
                        mod = (mod * 10 + dig) % n
                        break

            ret += int(num) // n
            break
    return ret


if __name__ == '__main__':
    print(solve(100))
    print(solve(10000))
