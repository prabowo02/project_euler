for tc in range(int(input())):
    a, b, n = input().split()
    n = int(n) - 1
    
    if n < len(a):
        print(a[n])
        continue
        
    if n < len(b):
        print(b[n])
        continue
    
    ls = [len(a), len(b)]
    while ls[-1] <= n:
        ls.append(ls[-1] + ls[-2])
                
    while len(ls) > 2:
        ls.pop()
        
        if n < ls[-2]:
            ls.pop()
        else:
            n -= ls[-2]
    
    if len(ls) == 1:
        print(a[n])
    else:
        print(b[n])
