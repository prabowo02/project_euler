n = int(input())

ans = 0
for a in range(n):
    for b in range(n):
        ans = max(ans, sum(list(map(int, list(str((a+1)**(b+1)))))))
print (ans)
