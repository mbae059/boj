class Solution {
    int[][] dp;
    public int solution(int[][] matrix_sizes) {
        int N = matrix_sizes.length;
        dp = new int[N][N];
        
        return go(0,N-1, matrix_sizes);
    }
    
    int go(int l, int r, int[][] matrix) {
        if(l==r) return 0;
        if(l+1==r) return matrix[l][0] * matrix[l][1] * matrix[r][1];
        if(dp[l][r]>0) return dp[l][r];
        
        dp[l][r] = (int)1e9;
        
        for(int i=l;i<r;i++) {
            dp[l][r] = Math.min(dp[l][r], go(l,i, matrix) + go(i+1,r,matrix) + matrix[l][0]*matrix[i][1]*matrix[r][1]);
        }
        return dp[l][r];
    }
}