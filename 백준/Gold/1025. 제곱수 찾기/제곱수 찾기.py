import sys
from collections import deque
import math
input = sys.stdin.readline

N, M = map(int, input().split())

matrix = [input().rstrip() for _ in range(N)]

squareNumber = {}

root = 0
while True:
    squareNumber[root*root] = 1
    if root*root >= 999999999:
        break
    root += 1

def isSquare(num):
    if num in squareNumber:
        return num
    return -1
answer= -1
for i in range(N):
    for j in range(M):
        for di in range(-N+1,N):
            for dj in range(-M+1, M):
                if di==0 and dj==0:
                    continue
                
                a = i
                b = j
                val =""
                while (0<=a<N and 0<=b<M):
                    val += matrix[a][b]
                    a+=di
                    b+=dj
                    answer= max(answer, isSquare(int(val)))

if N==1 and M==1:
    answer = max(answer, isSquare(int(matrix[0][0])))
print(answer)