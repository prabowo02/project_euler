""" The generator
from numpy import *

def solve (n):
  
  mul = [1 for i in range(40)]
  CC = [2, 17, 33]
  CH = [7, 22, 36]
  mul[30] = 0
  for cc in CC: mul[cc] = 14 / 16
  for ch in CH: mul[ch] = 6 / 16
  
  A = []
  for i in range(40):
    ls = [0 for i in range(40)]
    for dice1 in range(n):
      for dice2 in range(n):
        prev = (i - (dice1 + dice2 + 2) + 80) % 40
        ls[prev] += 1 / (n * n) * mul[prev]
        
    ls[i] -= 1
    A.append(ls)
    
  # From G2J to Jail
  A[10][30] += 1
    
  for cc in CC:
    A[0][cc] += 1 / 16 # From CC to GO
    A[10][cc] += 1 / 16 # From CC to Jail
    
  for ch in CH:
    A[0][ch] += 1 / 16
    A[10][ch] += 1 / 16
    A[11][ch] += 1 / 16
    A[24][ch] += 1 / 16
    A[39][ch] += 1 / 16
    A[5][ch] += 1 / 16
    A[ch-3][ch] += 1 / 16
    
  # Railway from CH
  A[5][36] += 2 / 16
  A[15][7] += 2 / 16
  A[25][22] += 2 / 16
  
  # Utility from CH
  A[12][7] += 1 / 16
  A[12][36] += 1 / 16
  A[28][22] += 1 / 16
    
  Board = ["GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3", 
  "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3", 
  'FP', 'E1', 'CH1', 'E2', 'E3', 'R3', 'F1', 'F2', 'U2', 'F3', 
  'G2J', 'G1', 'G2', 'CC3', 'G3', 'R4', 'CH3', 'H1', 'T2', 'H2']
    
  A.append(mul)
  
  AI = matrix(A).getI()
  
  ans = []
  for i in range(40): ans.append([AI.item(i, 40) * mul[i], Board[i]])
  
  ans.sort(reverse = True)
  
  sum = 0
  for i in range(40): sum += ans[i][0]
  print(sum)
  
  #for i in range(40): print(ans[i])
  ret = []
  for i in range(40): ret.append(ans[i][1])
  return ret
  
ans = []
for i in range(4, 40):
  ans.append(solve(i))
print(ans)
    
"""

ans = [['JAIL', 'R2', 'E3', 'D1', 'R3', 'D3', 'R1', 'E1', 'E2', 'FP', 'D2', 'U2', 'GO', 'G1', 'C3', 'F3', 'F1', 'CC2', 'G2', 'C1', 'F2', 'H2', 'C2', 'U1', 'T1', 'G3', 'CC3', 'B2', 'B3', 'B1', 'H1', 'T2', 'A2', 'R4', 'A1', 'CC1', 'CH1', 'CH1', 'CH3', 'G2J'], ['JAIL', 'E3', 'R3', 'R2', 'D3', 'GO', 'D1', 'D2', 'R1', 'E2', 'FP', 'E1', 'G1', 'U2', 'F1', 'G2', 'C1', 'F3', 'F2', 'CC2', 'H2', 'C3', 'U1', 'G3', 'C2', 'CC3', 'T1', 'B1', 'B2', 'B3', 'R4', 'H1', 'T2', 'A1', 'A2', 'CC1', 'CH1', 'CH1', 'CH3', 'G2J'], ['JAIL', 'E3', 'GO', 'D3', 'R3', 'R1', 'R2', 'D2', 'FP', 'E1', 'U2', 'D1', 'E2', 'C1', 'F1', 'G1', 'F2', 'H2', 'G2', 'U1', 'F3', 'CC2', 'G3', 'C3', 'R4', 'C2', 'CC3', 'T1', 'B2', 'B3', 'B1', 'H1', 'T2', 'A2', 'A1', 'CC1', 'CH1', 'CH1', 'CH3', 'G2J'], ['JAIL', 'E3', 'GO', 'R1', 'D3', 'R3', 'D2', 'FP', 'E1', 'U2', 'R2', 'C1', 'E2', 'H2', 'U1', 'F2', 'F1', 'G1', 'D1', 'F3', 'G2', 'G3', 'R4', 'C3', 'C2', 'CC2', 'CC3', 'B2', 'H1', 'T1', 'B3', 'B1', 'T2', 'A2', 'A1', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'E3', 'GO', 'R3', 'R1', 'D3', 'FP', 'E1', 'R2', 'C1', 'U2', 'E2', 'H2', 'D2', 'U1', 'F1', 'F3', 'F2', 'G1', 'G2', 'G3', 'D1', 'R4', 'C3', 'C2', 'H1', 'CC3', 'T1', 'B2', 'B3', 'T2', 'CC2', 'B1', 'A2', 'A1', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'E3', 'R3', 'R1', 'D3', 'C1', 'R2', 'H2', 'U2', 'E1', 'FP', 'E2', 'U1', 'F1', 'F2', 'D2', 'G1', 'F3', 'G2', 'G3', 'D1', 'R4', 'C3', 'H1', 'C2', 'T1', 'T2', 'B3', 'CC3', 'B2', 'A1', 'B1', 'A2', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'E3', 'R1', 'R3', 'C1', 'H2', 'U2', 'D3', 'R2', 'E1', 'E2', 'U1', 'FP', 'F1', 'F2', 'F3', 'D2', 'G1', 'G2', 'D1', 'G3', 'R4', 'H1', 'C3', 'T2', 'T1', 'C2', 'B3', 'CC3', 'B2', 'A2', 'A1', 'B1', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'E3', 'R1', 'R3', 'H2', 'C1', 'U2', 'R2', 'D3', 'E2', 'U1', 'E1', 'F1', 'F2', 'FP', 'F3', 'G1', 'D2', 'G2', 'D1', 'R4', 'G3', 'H1', 'C3', 'T1', 'T2', 'C2', 'A1', 'CC3', 'B3', 'A2', 'B2', 'B1', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'E3', 'R1', 'R3', 'H2', 'C1', 'U2', 'R2', 'D3', 'E2', 'U1', 'F1', 'F2', 'E1', 'F3', 'G1', 'FP', 'G2', 'D2', 'G3', 'D1', 'H1', 'T1', 'R4', 'C3', 'T2', 'C2', 'A1', 'CC3', 'B2', 'B1', 'A2', 'B3', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'E3', 'R1', 'R3', 'H2', 'C1', 'U2', 'R2', 'D3', 'U1', 'E2', 'F1', 'F2', 'F3', 'G1', 'E1', 'G2', 'FP', 'D2', 'G3', 'R4', 'D1', 'T1', 'H1', 'T2', 'C3', 'C2', 'A1', 'CC3', 'A2', 'B2', 'B3', 'B1', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'R3', 'H2', 'C1', 'U2', 'R2', 'D3', 'U1', 'F1', 'F2', 'E2', 'F3', 'G1', 'G2', 'E1', 'FP', 'G3', 'D2', 'R4', 'T1', 'H1', 'D1', 'T2', 'C3', 'A1', 'C2', 'CC3', 'A2', 'B2', 'B3', 'B1', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'R3', 'H2', 'C1', 'U2', 'R2', 'D3', 'U1', 'F1', 'F2', 'F3', 'G1', 'E2', 'G2', 'E1', 'FP', 'G3', 'R4', 'T1', 'D2', 'H1', 'T2', 'D1', 'C3', 'A1', 'C2', 'A2', 'CC3', 'B2', 'B3', 'B1', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'R3', 'H2', 'C1', 'U2', 'R2', 'U1', 'D3', 'F2', 'F3', 'F1', 'G1', 'G2', 'E2', 'G3', 'E1', 'R4', 'T1', 'FP', 'H1', 'D2', 'T2', 'D1', 'A1', 'C3', 'A2', 'C2', 'CC3', 'B1', 'B3', 'B2', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'H2', 'R3', 'C1', 'U2', 'R2', 'U1', 'D3', 'F3', 'G1', 'F2', 'F1', 'G2', 'E2', 'G3', 'T1', 'R4', 'E1', 'FP', 'H1', 'D2', 'T2', 'D1', 'A1', 'A2', 'C3', 'CC3', 'C2', 'B1', 'B3', 'B2', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'H2', 'R3', 'C1', 'U2', 'R2', 'U1', 'D3', 'F3', 'G1', 'G2', 'F2', 'F1', 'T1', 'G3', 'E2', 'R4', 'E1', 'H1', 'FP', 'T2', 'D2', 'A1', 'D1', 'A2', 'C3', 'CC3', 'B1', 'C2', 'B2', 'B3', 'CC2', 'CC1', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'H2', 'R3', 'C1', 'U2', 'R2', 'U1', 'D3', 'G1', 'F3', 'G2', 'T1', 'G3', 'F2', 'R4', 'F1', 'E2', 'H1', 'E1', 'T2', 'FP', 'D2', 'A1', 'A2', 'D1', 'B1', 'CC3', 'C3', 'B2', 'C2', 'B3', 'CC2', 'CC1', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'H2', 'R3', 'C1', 'U2', 'R2', 'U1', 'D3', 'G1', 'G2', 'T1', 'F3', 'G3', 'R4', 'F2', 'F1', 'H1', 'E2', 'T2', 'E1', 'FP', 'A1', 'D2', 'A2', 'B1', 'D1', 'B2', 'CC3', 'C3', 'B3', 'C2', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'E3', 'H2', 'C1', 'R3', 'U2', 'R2', 'U1', 'D3', 'G2', 'T1', 'G1', 'G3', 'R4', 'F3', 'F2', 'H1', 'F1', 'T2', 'E2', 'E1', 'A1', 'FP', 'A2', 'D2', 'B1', 'B2', 'D1', 'CC3', 'B3', 'C3', 'C2', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'R3', 'U1', 'U2', 'R2', 'T1', 'D3', 'G3', 'G2', 'R4', 'G1', 'F3', 'H1', 'F2', 'T2', 'F1', 'E2', 'A1', 'E1', 'A2', 'FP', 'B1', 'D2', 'B2', 'B3', 'D1', 'CC3', 'C3', 'C2', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'R3', 'U1', 'R2', 'U2', 'T1', 'D3', 'G3', 'R4', 'G2', 'H1', 'G1', 'F3', 'T2', 'F2', 'F1', 'A1', 'E2', 'A2', 'E1', 'FP', 'B1', 'B2', 'B3', 'D2', 'D1', 'C2', 'C3', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'R3', 'U1', 'R2', 'U2', 'T1', 'D3', 'R4', 'G3', 'H1', 'G1', 'G2', 'T2', 'F3', 'F2', 'A1', 'F1', 'A2', 'E2', 'B1', 'E1', 'B2', 'FP', 'B3', 'D2', 'D1', 'C2', 'C3', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'R3', 'U1', 'R2', 'U2', 'T1', 'D3', 'H1', 'R4', 'G3', 'T2', 'G2', 'G1', 'F3', 'A1', 'F2', 'F1', 'A2', 'B1', 'E2', 'B2', 'B3', 'E1', 'FP', 'D2', 'C2', 'C3', 'D1', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'R3', 'U1', 'R2', 'U2', 'T1', 'D3', 'H1', 'T2', 'R4', 'G3', 'G2', 'G1', 'A1', 'F3', 'A2', 'F2', 'F1', 'B1', 'B2', 'B3', 'E2', 'E1', 'FP', 'C2', 'C3', 'D2', 'D1', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'R3', 'U1', 'R2', 'T1', 'U2', 'D3', 'T2', 'H1', 'R4', 'G3', 'A1', 'G2', 'G1', 'A2', 'F3', 'B1', 'F2', 'B2', 'F1', 'B3', 'E2', 'E1', 'C2', 'FP', 'C3', 'D1', 'D2', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'E3', 'C1', 'U1', 'R3', 'R2', 'T1', 'U2', 'D3', 'T2', 'H1', 'A1', 'R4', 'G3', 'A2', 'G2', 'G1', 'B1', 'F3', 'B2', 'B3', 'F2', 'F1', 'E2', 'C2', 'C3', 'E1', 'D1', 'FP', 'D2', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'U2', 'D3', 'A1', 'T2', 'H1', 'A2', 'R4', 'G3', 'G2', 'B1', 'G1', 'B2', 'B3', 'F3', 'F2', 'F1', 'C2', 'C3', 'D1', 'E2', 'D2', 'E1', 'FP', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'U2', 'D3', 'A1', 'A2', 'T2', 'H1', 'R4', 'B1', 'G3', 'G2', 'B2', 'G1', 'B3', 'F3', 'C2', 'C3', 'F2', 'D1', 'F1', 'D2', 'E2', 'FP', 'E1', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'U2', 'D3', 'A2', 'A1', 'T2', 'B1', 'H1', 'R4', 'B2', 'G3', 'G2', 'B3', 'G1', 'F3', 'C2', 'C3', 'D1', 'D2', 'F2', 'F1', 'FP', 'E1', 'E2', 'CC3', 'CC1', 'CC2', 'CH3', 'CH1', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'D3', 'U2', 'A2', 'B1', 'A1', 'B2', 'T2', 'H1', 'B3', 'G3', 'R4', 'G2', 'G1', 'C2', 'C3', 'D1', 'D2', 'F3', 'FP', 'E1', 'F2', 'F1', 'E2', 'CC3', 'CC1', 'CC2', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'D3', 'U2', 'A2', 'B1', 'B2', 'B3', 'A1', 'T2', 'G3', 'R4', 'H1', 'G2', 'G1', 'C2', 'D2', 'C3', 'D1', 'FP', 'E1', 'F3', 'E2', 'F2', 'F1', 'CC3', 'CC1', 'CC2', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'D3', 'U2', 'B1', 'B2', 'A2', 'B3', 'H1', 'R4', 'A1', 'T2', 'G3', 'FP', 'C2', 'G2', 'D2', 'C3', 'E1', 'D1', 'G1', 'E2', 'F3', 'F2', 'F1', 'CC3', 'CC1', 'CC2', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'D3', 'U2', 'B1', 'B2', 'B3', 'H1', 'T2', 'R4', 'A2', 'E1', 'C2', 'G3', 'A1', 'FP', 'C3', 'E2', 'D1', 'D2', 'G2', 'G1', 'F3', 'F2', 'F1', 'CC3', 'CC1', 'CC2', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R2', 'R3', 'T1', 'D3', 'U2', 'B2', 'B3', 'B1', 'H1', 'T2', 'E2', 'A1', 'R4', 'C2', 'E1', 'C3', 'D1', 'A2', 'FP', 'G3', 'G1', 'D2', 'G2', 'F3', 'F1', 'F2', 'CC3', 'CC1', 'CC2', 'CH1', 'CH3', 'CH1', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'U1', 'R3', 'R2', 'T1', 'D3', 'U2', 'B2', 'B3', 'T2', 'H1', 'E2', 'A2', 'C2', 'A1', 'B1', 'C3', 'D1', 'G1', 'D2', 'E1', 'G2', 'F1', 'R4', 'FP', 'G3', 'F2', 'F3', 'CC3', 'CC1', 'CC2', 'CH1', 'CH1', 'CH3', 'G2J'], ['JAIL', 'GO', 'R1', 'H2', 'C1', 'E3', 'R3', 'U1', 'R2', 'T1', 'D3', 'U2', 'B3', 'B2', 'T2', 'E2', 'A2', 'C3', 'H1', 'C2', 'D2', 'F2', 'F1', 'G1', 'G2', 'A1', 'D1', 'FP', 'G3', 'B1', 'E1', 'R4', 'F3', 'CC3', 'CC1', 'CC2', 'CH1', 'CH1', 'CH3', 'G2J'], ['JAIL', 'GO', 'R1', 'C1', 'H2', 'E3', 'R3', 'U1', 'R2', 'U2', 'D3', 'T1', 'B2', 'T2', 'C3', 'F1', 'F2', 'D1', 'G1', 'B3', 'C2', 'H1', 'FP', 'F3', 'R4', 'G2', 'B1', 'E1', 'A2', 'G3', 'E2', 'D2', 'A1', 'CC3', 'CC1', 'CC2', 'CH1', 'CH3', 'CH1', 'G2J']]

n, k = map(int, input().split())
for i in range(k): print(ans[n-4][i], end = " ")
