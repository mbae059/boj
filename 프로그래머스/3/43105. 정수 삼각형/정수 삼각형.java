class Solution {
    int N;
    public int solution(int[][] triangle) {
        N = triangle.length;
        int[][] dp = new int[N][N];
        boolean[][] visited = new boolean[N][N];
        
        return dfs(0, 0, triangle, dp, visited);
    }
    
    int dfs(int row, int column, int[][] triangle, int[][] dp, boolean[][] visited) {
        if(row==N-1) return triangle[row][column];
        if(visited[row][column]) return dp[row][column];
        visited[row][column] = true;
        dp[row][column] = Math.max(dfs(row+1, column, triangle, dp, visited), dfs(row+1, column+1, triangle, dp, visited))+triangle[row][column];
        return dp[row][column]; 
    }
}