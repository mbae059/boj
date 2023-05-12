import sys,heapq

input = sys.stdin.readline

N, M = map(int, input().split())

day = []

l = 0
r = 0
for _ in range(N):
    day.append(int(input()))
    l = max(l, day[-1])
    r += day[-1]


answer= 0
while l<=r:
    mid = (l+r)//2
    cnt = 0
    money = 0
    for i in range(N):
        if money<day[i]:
            money = mid
            cnt+=1
        money -= day[i]
        
    
    if cnt<=M:
        answer = mid
        r = mid-1
    else :
        l = mid+1
print(answer)