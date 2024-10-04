class Solution {
    int[] s = new int[1_000_000 * 4];
    int N;    
    public int solution(int[] a) {
        N = a.length;
        segment(1,0,N-1,a);
            
        if(N==1 || N==2) return N;
        int answer = 2;
        for(int i=1;i+1<N;i++) {
            int m1 = query(1, 0, i-1, 0, N-1);
            int m2 = query(1, i+1, N-1, 0, N-1);
            if(a[i]<m1 || a[i]<m2) answer++;
        }
        return answer;
    }
    
    void segment(int node, int nodeLeft, int nodeRight, int[] a) {
        if(nodeLeft==nodeRight) {
            s[node] = a[nodeLeft];
            return;
        }
        int mid = nodeLeft + nodeRight >> 1;
        segment(node*2, nodeLeft, mid, a);
        segment(node*2+1, mid+1, nodeRight, a);
        s[node] = Math.min(s[node*2],s[node*2+1]);
    }
    
    int query(int node, int l, int r, int nodeLeft, int nodeRight) {
        if(l<=nodeLeft && nodeRight<=r) return s[node];
        if(nodeRight<l || r<nodeLeft) return (int)1e9;
        
        int mid = nodeLeft+nodeRight>>1;
        
        return Math.min(query(node*2, l, r, nodeLeft, mid), query(node*2+1, l, r, mid+1, nodeRight));
    }
}