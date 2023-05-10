import sys
input = sys.stdin.readline

T = int(input())
parent = [0] * 200001
group = [0] * 200001

def getParent(num):
    if parent[num]==num:
        return num
    else :
        return getParent(parent[num])
    
def unionParent(a, b):
    a = getParent(a)
    b = getParent(b)
    
    if a>b:
        parent[a] = b
    else :
        parent[b] = a

def isSameParent(a, b):
    return getParent(a)==getParent(b)

def Solve():
    N = int(input())
    cnt = 1
    d = {}
    for i in range(1,2*N+1):
        parent[i] = i
        group[i] = 1
    for _ in range(N):
        strA, strB = input().split()
        a = d.get(strA)
        if a == None:
            d[strA] = cnt
            a = cnt
            cnt+=1
        
        b = d.get(strB)
        if b == None:
            d[strB] = cnt
            b = cnt
            cnt+=1
        
        a = getParent(a)
        b = getParent(b)
        
        if a==b:
            print(group[a])
        else :
            sum = group[a] + group[b]
            print(sum)
            group[a] = group[b] = sum
            unionParent(a,b)
            
for _ in range(T):
    Solve()