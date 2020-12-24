n = int(input())
d = dict()
for i in range(1, 4000000):
    s = str(i**2)
    if (len(s) == n):
        s = ''.join(sorted(s))
        if s in d:
            d[s].append(i)
        else:
            d[s] = [i]
            
maks = 0
ans = 0
for key in d:
    if (len(d[key]) > maks):
        maks = len(d[key])
        ans = d[key][-1]
    elif (len(d[key]) == maks):
        ans = max(ans, d[key][-1])
        
print(ans**2)
