import sys,heapq

input = sys.stdin.readline

N, M, R = map(int, input().split())

matrix = [[0]*(M+1) for _ in range(N+1)]
for i in range(1,N+1):
    num = list(map(int, input().split()))
    for j in range(1,M+1):
        matrix[i][j] = [num[j-1], 'S']

dir = {}

dir['E'] = [0,1]
dir['W'] = [0,-1]
dir['S'] = [1,0]
dir['N'] = [-1,0]

attackPoint = 0

def attack():
    global attackPoint
    x, y, d = input().split()
    x = int(x)
    y = int(y)

    if matrix[x][y][1]=='F':
        return
    
    cnt = matrix[x][y][0]

    while cnt:
        if not (1<=x<=N and 1<=y<=M):
            break
        if matrix[x][y][1] == 'S':
            matrix[x][y][1] = 'F'
            attackPoint += 1
            cnt = max(cnt, matrix[x][y][0])

        cnt-=1
        x += dir[d][0]
        y += dir[d][1]
def defence():
    x, y = map(int, input().split())

    matrix[x][y][1] = 'S'

for _ in range(R):
    attack()
    defence()

print(attackPoint)

for i in range(1,N+1):
    for j in range(1,M+1):
        print(matrix[i][j][1], end=' ')
    print()