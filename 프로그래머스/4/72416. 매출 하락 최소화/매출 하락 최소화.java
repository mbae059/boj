import java.util.*;

class Solution {
    int N;
    int[][] dp;
    List<Integer>[] edge;
    public int solution(int[] sales, int[][] links) {
        N = sales.length;
        dp = new int[N][2];
        edge = new ArrayList[N];
        for(int i=0;i<N;i++) {
            edge[i] = new ArrayList<Integer>();
        }
        
        for(int i=0;i<links.length;i++) {
            int u = links[i][0]-1;
            int v = links[i][1]-1;
            edge[u].add(v);
        }
        
        dfs(0, sales, edge);
        
        return Math.min(dp[0][0], dp[0][1]);
    }
    
    void print(int... args) {
        for(int i : args) {
            System.out.print(i+ " ");
        }
        System.out.println();
    }
    void dfs(int cur, int[] sales, List<Integer>[] edge) {
        int extra = (int)1e9;
        dp[cur][1] += sales[cur];
        if(edge[cur].isEmpty()) return;
        for(int next : edge[cur]) {
            dfs(next, sales, edge);
            
            if(dp[next][0] < dp[next][1]) {
                dp[cur][0] += dp[next][0];
                dp[cur][1] += dp[next][0];
                extra = Math.min(extra, dp[next][1]-dp[next][0]);
            }
            else {
                dp[cur][0] += dp[next][1];
                dp[cur][1] += dp[next][1];
                extra = 0;
            }
        }
        dp[cur][0] += extra;
        
    }
}