import java.util.*;

class Solution {
    List<Integer>[] edge;
    int N;
    public int solution(int[] info, int[][] edges) {
        N = info.length;
        edge = new ArrayList[N];

        for(int i=0;i<N;i++) {
            edge[i] = new ArrayList<>();
        }
        for(int i=0;i<edges.length;i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            edge[u].add(v);
        }
        return dfs(0, 1, 0, info, edge, new TreeSet<Integer>());
    }
    
    int dfs(int cur, int sheep, int wolf, int[] info, List<Integer>[] edge, TreeSet<Integer> set) {
        int ret = sheep;
        set.addAll(edge[cur]);
        for(Integer next : set) {
            TreeSet<Integer> nextSet = new TreeSet<>();
            nextSet.addAll(set);
            nextSet.remove(next);
            
            if(info[next]==0) {
                ret = Math.max(ret, dfs(next, sheep+1, wolf, info, edge, nextSet));
            }
            else if(info[next]==1 && sheep!=wolf+1) {
                ret = Math.max(ret, dfs(next, sheep, wolf+1, info, edge, nextSet));
            }
        }
        return ret;
    }
    void print(int... args) {
        for(int i : args) {
            System.out.print(i+" ");
        }
        System.out.println();
    }
}