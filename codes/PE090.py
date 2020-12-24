"""
Generator for M = 3
###################

from __future__ import print_function
import sys

cubes = [[j for j in range(10) if i >> j & 1] for i in range(1<<10) if bin(i).count("1") == 6]
ans = [0 for i in range(32)]

def eprint(*args, **kwargs):
  print(*args, file=sys.stderr, **kwargs)

def check(sqr, i, j, k):
  if (sqr // 100 not in cubes[i]): return False
  if (sqr // 10 % 10 not in cubes[j]): return False
  if (sqr % 10 not in cubes[k]): return False
  return True
  
candidate = [[i, j, k] for i in range(len(cubes)) for j in range(i, len(cubes)) for k in range(j, len(cubes))]
for i in range(len(cubes)):
  if (6 in cubes[i]) == (9 in cubes[i]): continue
  if (6 in cubes[i]): cubes[i].append(9)
  if (9 in cubes[i]): cubes[i].append(6)
  
for i in range(1, 32):
  eprint(i)
  sqr = i * i
  
  newCandidate = [] 
  for c in candidate:       
    if (check(sqr, c[0], c[1], c[2])): 
      newCandidate.append(c)
      continue
    if (check(sqr, c[0], c[2], c[1])): 
      newCandidate.append(c)
      continue
    if (check(sqr, c[1], c[0], c[2])): 
      newCandidate.append(c)
      continue
    if (check(sqr, c[1], c[2], c[0])): 
      newCandidate.append(c)
      continue
    if (check(sqr, c[2], c[0], c[1])): 
      newCandidate.append(c)
      continue
    if (check(sqr, c[2], c[1], c[0])): 
      newCandidate.append(c)
      continue
  
  candidate = newCandidate
  ans[i] = len(candidate)
      
print(ans)
"""

ans = [[0],
[0, 126, 70, 55],
[0, 13461, 9450, 8630, 8150, 3946, 2579, 2365, 2365, 1217], 
[0, 758576, 561470, 519805, 518050, 387665, 344021, 342579, 342579, 294197, 294197, 153684, 82867, 66354, 66354, 31613, 31613, 30828, 28954, 28954, 28954, 28954, 20204, 20204, 12716, 12716, 10376, 10376, 9600, 9600, 9600, 9600]]

n, m = map(int, input().split())
print(ans[m][n])