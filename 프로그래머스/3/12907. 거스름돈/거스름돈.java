class Solution {
    public int solution(int n, int[] money) {
        int[][] dp = new int[money.length+1][n+1];
        int[] prefix = new int[n+1];
        prefix[0] = 1;
        dp[0][0] = 1;
        
        for(int i=0;i<money.length;i++) {
            for(int j=1;j<=n;j++) {
                if(j-money[i]>=0) {
                    dp[i+1][j] += prefix[j-money[i]];
                }
                prefix[j] += dp[i+1][j];
            }
        }
        return prefix[n];
    }
}