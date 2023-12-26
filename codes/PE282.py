import functools


mod = 14**8

def tetration():
    cur, vis = 1, {}
    while cur not in vis:
        vis[cur] = len(vis)
        cur = pow(2, cur, mod)
    print(len(vis) - vis[cur])

def pentation()


def hyper(n, a, b):
    if n == 0:
        return b + 1
    if n == 1:
        return (a + b) % mod
    if n == 2:
        return a * b % mod
    if n == 3:
        return pow(a, b, mod)




@functools.cache
def find_cycle(n, a):
    assert n > 3
    cur, cycle = 1, {}
    while cur not in cycle:
        cycle[cur] = len(cycle)
        cur = hyper(n - 1, a, cur)
    return len(cycle) - cycle[cur], cycle


tetration()