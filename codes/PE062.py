n, k = map(int, input().split())

cubic = dict()
ans = dict()
for i in range(1, n):
    s = ''.join(sorted(str(i * i * i)))
    if s in cubic:
        cubic[s] += 1
    else:
        cubic[s] = 1
        ans[s] = i
        
res = []
for key in cubic:
    if cubic[key] == k: res.append(ans[key])

res.sort()
for num in res: print(num * num * num)
