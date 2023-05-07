T = int(input())

def solve() :
    x1, y1, x2, y2, x3, y3, x4, y4 = map(int, input().split())

    area = (x2-x1) * (y2-y1)
    if y1 > y3:
        x1, y1, x2, y2, x3, y3, x4, y4 = x3, y3, x4, y4, x1, y1, x2, y2
    
    if y2 <= y3 or x1 >= x4 or x2 <= x3:
        print(area)
        return
    
    tx1 = max(x1, x3)
    tx2 = min(x2, x4)

    ty1 = y3
    ty2 = min(y2,y4)
    overlappedarea = (tx2-tx1) * (ty2-ty1)
    print(area-overlappedarea)
    return
while T:
    solve()
    T-=1