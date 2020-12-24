SZ = 701

dp = [[0 for j in range(SZ)] for i in range(SZ)]
C = [[0 for j in range(SZ)] for i in range(SZ)]

dp[0][0] = 1
C[0][0] = 1
for i in range(1, SZ):
    for j in range(i+1):
        C[i][j] = C[i-1][j-1] + C[i-1][j]
        dp[i][j] = dp[i-1][j-1] * (i - j) + dp[i-1][j] * (j + 1)
        
N, q = map(int, input().split())
m = list(map(int, input().split()))

ans = 0
for mi in m:
    maks = 0
    for n in range(1, N+1):
        maks = max(maks, dp[n][mi] * C[N][n])
    ans += maks
    
print(ans)
