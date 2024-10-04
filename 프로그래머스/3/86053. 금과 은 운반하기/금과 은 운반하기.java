class Solution {
    public long solution(int a, int b, int[] g, int[] s, int[] w, int[] t) {
        long l = 1;
        long r =(long)1e17;
        long N = g.length;
        long answer = -1;
        while(l<=r) {
            long mid = l+r>>1;
            
            long tg = 0;
            long ts = 0;
            long tgs = 0;
            for(int i=0;i<N;i++) {
                long mul = mid / (2*t[i]) + ((mid % (2*t[i])) >= t[i] ? 1 : 0);
                tg += Math.min(g[i], mul * w[i]);
                ts += Math.min(s[i], mul * w[i]);
                tgs += Math.min(g[i]+s[i], mul * w[i]);
            }
            if(a<=tg && b<=ts && a+b<=tgs) {
                answer = mid;
                r = mid-1;
            }
            else {
                l = mid+1;
            }
        }
        return answer;
    }
}