import sys
import heapq
input = sys.stdin.readline


L = [10001]
R = [10001]

for _ in range(int(input())):
    N = int(input())
    
    if -L[0] < N:
        heapq.heappush(R, N)
    else :
        heapq.heappush(L, -N)
    
    while len(L) < len(R):
        heapq.heappush(L, -heapq.heappop(R))
    while len(L)>len(R)+1:
        heapq.heappush(R, -heapq.heappop(L))
    
    print(-L[0])