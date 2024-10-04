class Solution {
    int N;
    
    void dfs_root(int cur, int[][] links, int[] dp) {
        if(dp[cur]!=0) return;
        int l = links[cur][0];
        int r = links[cur][1];
        dp[cur]++;
        if(l!=-1) {
            dfs_root(l, links, dp);
            dp[cur] += dp[l];
        }
        
        if(r!=-1) {
            dfs_root(r, links, dp);
            dp[cur] += dp[r];
        }
        
    }
    int getRoot(int[][] links) {
        int[] dp = new int[N];
        for(int i=0;i<N;i++) {
            dfs_root(i, links, dp);
            if(dp[i]==N) return i;
        }
        return -1;
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
    public int solution(int k, int[] num, int[][] links) {
        N = links.length;
        int l = 1;
        int r = (int)1e9;
        int root = getRoot(links);
        int answer = 0;
        while(l<=r) {
            int mid = l+r>>1;
            Pii p = dfs(root, mid, num, links);
            if(p.b+1<=k) {
                r = mid-1;
                answer = mid;
            }
            else {
                l = mid+1;
            }
        }
        return answer;
    }
    
    Pii dfs(int cur, int limit, int[] num, int[][] links) {
        int sum = 0;
        Pii l = new Pii();
        Pii r = new Pii();
        if(links[cur][0]!=-1) {
            l = dfs(links[cur][0], limit, num, links);
        }
        if(links[cur][1]!=-1) {
            r = dfs(links[cur][1], limit, num, links);
        }
        if(l.a+r.a+num[cur]<=limit) return new Pii(l.a+r.a+num[cur], l.b+r.b);
        else if(l.a+num[cur]<=limit || r.a+num[cur]<=limit) {
            if(l.a<r.a) return new Pii(l.a+num[cur], l.b+r.b+1);
            else return new Pii(r.a+num[cur], l.b+r.b+1);
        } 
        else if(l.a+num[cur]<=limit) return new Pii(l.a+num[cur], l.b+r.b+1);
        else if(r.a+num[cur]<=limit) return new Pii(r.a+num[cur], l.b+r.b+1);
        else if(num[cur]<=limit) return new Pii(num[cur], l.b+r.b+2);
        else return new Pii(1, (int)1e4+1);
    }
    void print(int... args) {
        for(int i : args) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}