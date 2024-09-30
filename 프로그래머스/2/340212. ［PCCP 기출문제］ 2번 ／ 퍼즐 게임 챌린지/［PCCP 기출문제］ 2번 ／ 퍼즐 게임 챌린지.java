import java.util.*;

class Solution {
    public int solution(int[] diffs, int[] times, long limit) {
        long l = 1l;
        long maxValue = (long)1e5;
        long r = maxValue;
        int N = diffs.length;
        long answer=0l;
        while(l<=r) {
            long mid = l+r>>1l;
            long t = times[0];
            for(int i=1;i<N;i++) {
                if(diffs[i]<=mid) t += times[i];
                else {
                    t += (diffs[i] - mid) * (times[i]+times[i-1]) + times[i];
                }
            }
            if(t <=limit) {
                r = mid-1;
                answer = mid;
            }
            else {
                l = mid+1;
            }
        }
        return (int)answer;
    }
    
    void print(int x) {
        System.out.println(x);
    }
}