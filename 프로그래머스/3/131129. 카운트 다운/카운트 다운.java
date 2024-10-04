import java.util.*;


class Solution {
    class Tiii {
        int cur;
        int a;
        int b;
        Tiii() {
            cur=a=b=0;
        }
        Tiii(int cur, int a, int b) {
            this.cur=cur;
            this.a=a;
            this.b=b;
        }
    }
    class Pii {
        int a;
        int b;
        Pii() {
            a=b=0;
        }
        Pii(int a, int b) {
            this.a=a;
            this.b=b;
        }
    }
    int[][] dp = new int[100_001][2];
    
    public int[] solution(int target) {
        for(int i=0;i<=100_000;i++) {
            dp[i][0] = dp[i][1] = (int)1e9;
        }
        dp[0][0] = 0;
        dp[0][1] = 0;
        
        for(int i=1;i<=target;i++) {
            for(int j=1;j<=20;j++) {
                if(i-j>=0) {
                    if(dp[i][0]>dp[i-j][0]+1) {
                        dp[i][0] = dp[i-j][0] + 1;
                        dp[i][1] = dp[i-j][1] + 1;
                    }
                    else if(dp[i][0]==dp[i-j][0]+1 && dp[i][1]<dp[i-j][1]+1) {
                        dp[i][1] = dp[i-j][1]+1;
                    }
                }
            }
            for(int j=2;j<=40;j+=2) {
                if(i-j>=0) {
                    if(dp[i][0]>dp[i-j][0]+1) {
                        dp[i][0] = dp[i-j][0]+1;
                        dp[i][1] = dp[i-j][1];
                    }
                    else if(dp[i][0]==dp[i-j][0]+1 && dp[i][1]<dp[i-j][1]) {
                        dp[i][1] = dp[i-j][1];
                    }
                }
            }
            for(int j=3;j<=60;j+=3) {
                if(i-j>=0) {
                    if(dp[i][0]>dp[i-j][0]+1) {
                        dp[i][0] = dp[i-j][0]+1;
                        dp[i][1] = dp[i-j][1];
                    }
                    else if(dp[i][0]==dp[i-j][0]+1 && dp[i][1]<dp[i-j][1]) {
                        dp[i][1] = dp[i-j][1];
                    }
                }
            }
            if(i-50>=0) {
                if(dp[i][0]>dp[i-50][0]+1) {
                    dp[i][0] = dp[i-50][0] + 1;
                    dp[i][1] = dp[i-50][1] + 1;
                }
                else if(dp[i][0]==dp[i-50][0]+1 && dp[i][1] < dp[i-50][1]+1) {
                    dp[i][1] = dp[i-50][1]+1;
                }
            }
        }
        return dp[target];
    }
}