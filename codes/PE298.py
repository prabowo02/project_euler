import functools

def solve(n):
    def hit(mem, x):
        nmem = list(mem)[:x] + list(mem)[x+1:]
        nmem = [0 if m in (0, 5) else m + 1 for m in nmem]
        return tuple(nmem + [1])

    # mem is a tuple representing Robin's memory.
    # Element zero represents a number not in Larry's mem,
    # while positive means how old it is in Larry's mem
    @functools.cache
    def f(n, mem, s):
        if n == 0:
            return abs(s)

        ret = 0
        for i in range(len(mem)):
            if mem[i] == 0:
                ret += f(n - 1, hit(mem, i), s - 1)
            else:
                ret += f(n - 1, tuple(list(mem)[:i] + list(mem)[i+1:] + [mem[i]]), s)

        cnt = len(mem)
        for i in range(len(mem)):
            if i + 1 not in mem:
                ret += f(n - 1, tuple(list(mem)[1:] + [i + 1]), s + 1)
                cnt += 1

        if len(mem) < 5:
            ret += f(n - 1, hit(mem, len(mem)), s) * (10 - cnt)
        else:
            ret += f(n - 1, hit(mem, 0), s) * (10 - cnt)

        return ret / 10

    return f(n, (), 0)


if __name__ == '__main__':
    print(solve(50))
