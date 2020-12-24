N = 10005;

s = str(int(input()) - 1)
k = [ord(c) - ord('0') for c in s]
n = len(k)

dp = [[[[0 for i in range(2)] for i in range(4)] for i in range(10)] for i in range(2)]
for num in range(10):
    for lim in range(2):
        dp[n-1 & 1][num][3][lim] = 1
    
ans = 0
for x in range(n-2, -1, -1):
    for num in range(10):
        for mask in range(4):
            for lim in range(2):
                dp[x&1][num][mask][lim] = 0
                if (num > 0 and (lim == 0 or num-1 <= k[x+1])): 
                    dp[x&1][num][mask][lim] += dp[x+1&1][num-1][mask | (num-1 == 0) << 0][lim * (1 if k[x+1] == num-1 else 0)]
                if (num < 9 and (lim == 0 or num+1 <= k[x+1])): 
                    dp[x&1][num][mask][lim] += dp[x+1&1][num+1][mask | (num+1 == 9) << 1][lim * (1 if k[x+1] == num+1 else 0)]
                    
    
    for j in range(1, (k[0] if x == 0 else 9) + 1):
        # ans += f(i, j, (1 << 1 if j == 9 else 0), 1 if i == 0 and j == k[0] else 0);
        ans += dp[x&1][j][1 << 1 if j == 9 else 0][1 if x == 0 and j == k[0] else 0]
                   
                
"""    
def f(x, num, mask, lim):
    if (x == n-1): return 1 if mask == 3 else 0;
    if (dp[x][num][mask][lim] != -1): return dp[x][num][mask][lim];
    
    ret = 0;
    
    if (num > 0 and (lim == 0 or num-1 <= k[x+1])): 
        ret += f(x+1, num-1, mask | (num-1 == 0) << 0, lim * (1 if k[x+1] == num-1 else 0));
    if (num < 9 and (lim == 0 or num+1 <= k[x+1])): 
        ret += f(x+1, num+1, mask | (num+1 == 9) << 1, lim * (1 if k[x+1] == num+1 else 0));
    
    dp[x][num][mask][lim] = ret;
    return ret
"""
    
print(ans)
