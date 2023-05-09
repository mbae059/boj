import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))

cnt = 0
d = [1,-1]
idx = 0
while True:
    num = arr[idx]
    arr[idx] = 0
    print(idx+1, end=' ')
    cnt+=1
    if cnt==N:
        break
    if num>=0 :
        while num :
            idx+=1
            if idx==N:
                idx = 0
            if arr[idx]!=0:
                num-=1
            
    else :
        while num:
            idx-=1
            if idx==-1:
                idx=N-1
            if arr[idx]!=0:
                num+=1

