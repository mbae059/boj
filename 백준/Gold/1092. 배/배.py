import sys,heapq

input = sys.stdin.readline

N = int(input())
cranes = list(map(int, input().split()))
M = int(input())
boxes = list(map(int, input().split()))
cranes.sort()
cranes.reverse()
boxes.sort()
boxes.reverse()

if cranes[0] < boxes[0]:
    print(-1)
    sys.exit(0)

l = 1
r = 10000

visited = [0]*M

answer = 0
while l <= r:
    mid = (l+r)//2

    idx = 0
    for crane in cranes:
        for _ in range(mid):
            if idx>=M:
                break
            if crane < boxes[idx]:
                break
            idx+=1
            
    if idx==M:
        answer = mid
        r = mid-1
    else :
        l = mid+1
print(answer)


