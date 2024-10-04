import java.util.*;

class Solution {
    int answer=0;
    Set<String> set = new HashSet<>();
    public int solution(String[] user_id, String[] banned_id) {
        boolean[] visited = new boolean[user_id.length];
        dfs(0, user_id, banned_id, visited);
        return answer;
    }
    
    void dfs(int idx, String[] user_id, String[] banned_id, boolean[] visited) {
        if(idx==banned_id.length) {
            StringBuilder sb = new StringBuilder();
            for(int i=0;i<visited.length;i++) {
                sb.append(visited[i] ? '1' : '0');
            }
            String str = sb.toString();
            if(!set.contains(str)) {
                answer++;
                set.add(str);
                System.out.println();
            }
            return;
        }
        
        for(int i=0;i<user_id.length;i++) {
            if(visited[i]) continue;
            if(cmp(banned_id[idx], user_id[i])) {
                visited[i] = true;
                dfs(idx+1, user_id, banned_id, visited);
                visited[i] = false;
            }
        }
    }
    void print(int... args) {
        for(int i : args) {
            System.out.print(i+" ");
        }
        System.out.println();
    }
    //첫 번째는 banned
    boolean cmp(String str1, String str2) {
        if(str1.length()!=str2.length()) return false;
        
        for(int i=0;i<str1.length();i++) {
            if(str1.charAt(i)=='*') continue;
            if(str1.charAt(i)!=str2.charAt(i)) return false;
        }
        return true;
    }
}
