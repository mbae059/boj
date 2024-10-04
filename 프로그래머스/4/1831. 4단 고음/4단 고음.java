import java.util.*;

class Solution {
    int getRemain(int n) {
        return (int)(Math.log(n)/Math.log(3));
    }
    public int solution(int n) {
        int x = getRemain(n);
        return dfs(n-2, x, 2*x-2);
    }
    
    int dfs(int n, int a, int b) {
        if(a*2<b) return 0;
        if(n==3 && a==1 && b==0) return 1;
        if(n==4 && a==1 && b==1) return 1;
        if(n==5 && a==1 && b==2) return 1;
            
        int ret = 0;
        for(int i=0;i<=b;i++) {
            if(n-i>0 && (n-i)%3==0) {
                ret += dfs((n-i)/3, a-1, b-i);
            }
        }
        return ret;
    }
}