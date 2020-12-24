def converge (n): 
    for i in range(60):
        if (str(n) == str(n)[::-1]): return n
        n = n + int(str(n)[::-1])
    return 0

n = int(input())

lychrel = dict()
for i in range(n):
    num = converge(i + 1)
    if (num in lychrel): lychrel[num] += 1
    else: lychrel[num] = 1
    
lychrel[0] = 0
ans = 0
for num in lychrel:
    if (lychrel[num] >= lychrel[ans]):
        ans = num
        
print(ans, lychrel[ans])
