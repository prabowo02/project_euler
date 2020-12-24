sudoku = []
for i in range(9): sudoku.append(list(map(int, list(input()))))
    
r = [[0] * 9 for i in range(9)]
c = [[0] * 9 for i in range(9)]
b = [[0] * 9 for i in range(9)]

for i in range(9):
    for j in range(9):
        num = sudoku[i][j]
        if (num == 0): continue                
        
        r[i][num - 1] += 1
        c[j][num - 1] += 1
        b[i // 3 * 3 + j // 3][num - 1] += 1        
    
def solve(i, j):
    if (i == 9):
        for row in sudoku:
            print(''.join(map(str, row)))
        exit(0)
    
    if (j == 9):
        solve(i+1, 0)
        return
        
    if (sudoku[i][j] == 0):
        for num in range(1, 10):
            if (r[i][num-1] == 0) and (c[j][num-1] == 0) and (b[i // 3 * 3 + j // 3][num - 1] == 0):                
                r[i][num - 1] += 1
                c[j][num - 1] += 1
                b[i // 3 * 3 + j // 3][num - 1] += 1                                
                
                sudoku[i][j] = num
                solve(i, j + 1)
                sudoku[i][j] = 0
                
                r[i][num - 1] -= 1
                c[j][num - 1] -= 1
                b[i // 3 * 3 + j // 3][num - 1] -= 1                
    else:
        solve(i, j+1)
        
solve(0, 0)
