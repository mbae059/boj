import java.util.*;


class Solution {
    List<Pii>[] edge;
    int N;
    class Pii {
        int a;
        int b;
        Pii() {
            a = b = 0;
        }
        Pii(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
    
    void dijkstra(int _cur, int[] dp) {
        for(int i=0;i<N;i++) {
            dp[i] = (int)1e9;
        }
        PriorityQueue<Pii> pq = new PriorityQueue<>((l,r) -> l.b-r.b);
        pq.add(new Pii(_cur, 0));
        dp[_cur] = 0;
        while(!pq.isEmpty()) {
            Pii top = pq.poll();
            int cur = top.a;
            int distance = top.b;
            
            if(dp[cur]!=distance) continue;
            
            for(Pii nextP : edge[cur]) {
                int next = nextP.a;
                int nextDistance = distance + nextP.b;
                if(dp[next]>nextDistance) {
                    dp[next] = nextDistance;
                    pq.add(new Pii(next, nextDistance));
                }
            }
        }
        // for(int i=0;i<N;i++) {
        //     System.out.print(dp[i]+" ");
        // }
        System.out.println();
    }
    public int solution(int n, int s, int a, int b, int[][] fares) {
        edge = new ArrayList[n];
        N = n;
        int[] dpS = new int[n];
        int[] dpA = new int[n];
        int[] dpB = new int[n];
        
        for(int i=0;i<n;i++) {
            edge[i] = new ArrayList<>();
        }
        for(int i=0;i<fares.length;i++) {
            int u = fares[i][0];
            int v = fares[i][1];
            u--;
            v--;
            int cost = fares[i][2];
            edge[u].add(new Pii(v, cost));
            edge[v].add(new Pii(u, cost));
        }
        s--;
        a--;
        b--;
        dijkstra(s, dpS);
        dijkstra(a, dpA);
        dijkstra(b, dpB);
        
        int maxValue = (int)1e9;
        int answer = (int)1e9;
        for(int i=0;i<n;i++) {
            if(dpS[i]==maxValue || dpA[i]==maxValue || dpB[i]==maxValue) continue;
            answer = Math.min(answer, dpS[i]+dpA[i]+dpB[i]);
        }
        return answer;
    }
}