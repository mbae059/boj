import sys
input = sys.stdin.readline
N, M = map(int, input().split())

matrix = [list(map(int, input().split())) for _ in range(N)]

from collections import deque

dq = deque()

def inRange(y,x):
    return (0<=y<N) and (0<=x<M)

dir = [[0,1],[0,-1],[1,0],[-1,0]]

time = 0
cnt=0
while True:
    dq.append([0,0])
    visited = [[0] * M for _ in range(N)]
    visited[0][0] = 1

    meltdown =[]
    while dq:
        y = dq[0][0]
        x = dq[0][1]
        dq.popleft()

        for d in dir:
            nexty = y + d[0]
            nextx = x + d[1]
            if (not inRange(nexty, nextx)) or (visited[nexty][nextx]):
                continue
            visited[nexty][nextx] = 1
            if matrix[nexty][nextx]==1:
                meltdown.append([nexty,nextx])
                continue
            else :
                dq.append([nexty,nextx])

    if meltdown :
        cnt = len(meltdown)
        time+=1
    else :
        break
    for melt in meltdown:
        y = melt[0]
        x = melt[1]
        matrix[y][x] = 0
print(time)
print(cnt)