import math
def solution(r1, r2):
    answer = 0
    
    for i in range(1,r2) :
        num2 = int(math.sqrt(r2**2-i**2))
        if i >=r1 :
            answer += 4*(num2+1)
        else :
            num1 = int(math.sqrt(r1**2-i**2))
            if num1**2 + i**2 == r1**2:
                answer += 4*(num2-num1+1)
            else :
                answer += 4*(num2-num1)
    
    answer += 4
    return answer