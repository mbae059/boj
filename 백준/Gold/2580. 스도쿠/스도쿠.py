import sys

input = sys.stdin.readline
sudoku = [list(map(int, input().split())) for _ in range(9)]

def isRow(y,x, num):
    for j in range(9):
        if sudoku[y][j]==num:
            return False
    return True

def isColumn(y,x, num):
    for i in range(9):
        if sudoku[i][x]==num:
            return False
    return True

def isSquare(y,x, num):
    for i in range((y//3)*3, (y//3)*3+3):
        for j in range((x//3)*3, (x//3)*3+3):
            if sudoku[i][j]==num:
                return False
    return True

def condition(y,x, num):
    return isRow(y,x, num) and isColumn(y,x, num) and isSquare(y,x,num)

def dfs(y, x):
    if y==9:
        for i in range(9):
            for j in range(9):
                print(sudoku[i][j], end=' ')
            print()
        sys.exit(0)

    if x==9:
        dfs(y+1,0)
        return
    elif sudoku[y][x]:
        dfs(y, x+1)
        return
    
    for i in range(1,10,1):
        if condition(y,x, i):
            sudoku[y][x] = i
            dfs(y, x+1)
        sudoku[y][x] = 0
dfs(0,0)