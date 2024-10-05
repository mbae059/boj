import java.util.*;


class Solution {
    
    TreeSet<Integer> set = new TreeSet<>();
    public int[] solution(String[] operations) {
        for(int i=0;i<operations.length;i++) {
            char op = operations[i].charAt(0);
            int val = Integer.parseInt(operations[i].substring(2));
            
            if(op=='I') {
                set.add(val);
            }
            else if(val==1) {
                if(!set.isEmpty()) {
                    set.remove(set.last());
                }
            }
            else {
                if(!set.isEmpty()) {
                    set.remove(set.first());
                }
            }
        }
        if(set.isEmpty()) return new int[]{0,0};
        else return new int[]{set.last(), set.first()};
    }
}