MOD = 10000000000

def power (x, y) :
  if (y) :
    if (y & 1) : return x * power (x * x % MOD, y >> 1) % MOD
    else : return power (x * x % MOD, y >> 1)
  else : return 1

n = int(input())

ans = 0
for i in range(n) : 
  ans += power (i + 1, i + 1)
  ans %= MOD
  
print(ans)
