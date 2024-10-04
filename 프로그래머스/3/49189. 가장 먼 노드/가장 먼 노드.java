import java.util.*;

class Solution {
    class Pii {
        int cur;
        int distance;
        
        Pii() {
            cur = distance = 0;
        }
        Pii(int cur, int distance) {
            this.cur = cur;
            this.distance = distance;
        }
    }
    public int solution(int n, int[][] edge) {
        List<Integer>[] graph = new List[n];
        boolean[] visited = new boolean[n];
        int[] dp = new int[n];
        for(int i=0;i<n;i++) {
            graph[i] = new ArrayList<>();
        }
        
        for(int i=0;i<edge.length;i++) {
            int u = edge[i][0];
            int v = edge[i][1];
            u--;
            v--;
            graph[u].add(v);
            graph[v].add(u);
        }

        Queue<Pii> q = new LinkedList<>();
        q.add(new Pii(0, 0));
        visited[0] = true;
        int mx = 0;
        while(!q.isEmpty()) {
            Pii top = q.poll();
            int cur = top.cur;
            int distance = top.distance;
            dp[cur] = distance;
            mx = Math.max(mx, distance);
            for(int next : graph[cur]) {
                if(visited[next]) continue;
                visited[next] = true;
                q.add(new Pii(next, distance+1));
            }
        }
        int answer = 0;
        for(int i=0;i<n;i++) {
            if(dp[i]==mx) answer++;
            // System.out.println(i + " " + dp[i]);
        }
        return answer;
    }
}