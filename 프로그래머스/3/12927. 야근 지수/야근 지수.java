import java.util.*;

class Solution {
    public long solution(int n, int[] works) {
        PriorityQueue<Integer> pq = new PriorityQueue<>((a,b)->b-a);
        for(int i=0;i<works.length;i++) {
            pq.add(works[i]);
        }
        while(!pq.isEmpty() && n>0) {
            int cur = pq.poll();
            cur-=1;
            n--;
            if(cur!=0) pq.add(cur);
        }
        
        long answer = 0;
        while(!pq.isEmpty()) {
            int cur = pq.poll();
            answer += cur * cur;
        }
        return answer;
    }
    
    void print(int... array) {
        for(int i : array) {
            System.out.print(i+" ");
        }
        System.out.println();
    }
}