import sys, bisect
from collections import deque

N = int(input())

li = deque([])
for _ in range(N):
    num, s, b = map(int, input().split())
    li.append([num,s,b])

def getStrikeBall(cmp, num):
    cmpStr = str(cmp)
    numStr = str(num)
    S=0
    B=0
    for i in range(3):
        if cmpStr[i]==numStr[i]:
            S+=1
        elif cmpStr[i] in numStr:
            B+=1
    return S,B
answer = 0


for i in range(123,1000,1):
    a = i//100
    b = i//10 % 10
    c = i%10
    
    if a==b or b==c or a==c or a==0 or b==0 or c==0:
        continue
    for j in range(N):
        num, s, b = li[j]
        cntStrike, cntBall = getStrikeBall(num, i)
        if s!=cntStrike or b!=cntBall:
            break
        if j==N-1:
            answer+=1
print(answer)
  
        
    