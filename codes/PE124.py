primeFactor = [[] for i in range(200001)]

for i in range(2, 200001):
    if (len(primeFactor[i]) == 0):
        for j in range(i, 200001, i):
            primeFactor[j].append(i)

def rad(n):    
    ret = 1
    for num in primeFactor[n]:
        ret *= num
    return ret
         
L, k = 0, 0
ans = []
def sergio(cur, num, n):
    if (cur == len(primeFactor[n])): 
        ans.append(num)
        return
        
    tmp = 1
    while (num * tmp <= L):
        sergio(cur + 1, num * tmp, n)
        tmp *= primeFactor[n][cur]
        
t = int(input())
if (t > 20):
    BIT = [0 for i in range(200001)]
    
    def update(x, val):
        while (x <= 200000):
            BIT[x] += val
            x += x & -x
            
    def query(x):
        ret = 0
        while (x):
            ret += BIT[x]
            x -= x & -x
        return ret
    
    q = []
    for i in range(t):
        q.append(list(map(int, input().split())) + [i])
    q.sort()
    
    res = [0 for i in range(200001)]
    ls = [[] for i in range(200001)]
    
    cur = 1
    for i in range(t):
        while (cur <= q[i][0]):
            update(rad(cur), 1)
            ls[rad(cur)].append(cur)
            cur += 1        
            
        l = 1
        r = q[i][0]
        ans = -1
        while (l <= r):
            mid = (l + r) // 2
            if (query(mid) < q[i][1]): l = mid + 1
            else: 
                ans = mid
                r = mid - 1
                        
        res[q[i][2]] = ls[ans][q[i][1] - query(ans) - 1]
                
    for i in range(t): print(res[i])
    
    exit(0)

for tc in range(t):
    L, k = map(int, input().split())
    
    cur = 0
    num = 0
    while (cur < k):
        num += 1
        if (rad(num) != num): continue       
            
        ans = []
        sergio(0, num, num)
        cur += len(ans)
            
    print (sorted(ans)[k - cur - 1])
