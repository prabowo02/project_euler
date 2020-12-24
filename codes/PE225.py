def hasZero(t1, t2, t3, n):
    T0 = (t1 % n, t2 % n, t3 % n)
    if 0 in T0:
        return True
    

    Ti = (T0[1], T0[2], sum(T0) % n)
    while Ti != T0:
        if Ti[-1] == 0:
            return True
        
        Ti = (Ti[1], Ti[2], sum(Ti) % n)
        
    return False
    

def solve(t1, t2, t3, k):
    i = 3
    check = [False for i in range(20000)]
    while k > 0:
        if check[i] or not hasZero(t1, t2, t3, i):
            for j in range(i, 20000, i):
                check[j] = True
            k -= 1
        i += 2
        
    return i - 2


def main():
    t1, t2, t3, k = [int(i) for i in input().split()]
    print(solve(t1, t2, t3, k))


if __name__ == '__main__':
    main()
