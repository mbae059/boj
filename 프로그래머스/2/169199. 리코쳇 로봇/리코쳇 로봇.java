import java.util.*;

class Solution {
    int N;
    int M;
    
    int[] dy={1,0,-1,0};
    int[] dx={0,1,0,-1};
    
    void print(int... args) {
        for(int i : args) {
            System.out.print(i+" ");
        }
        System.out.println();
    }
    
    class Tiii {
        int y;
        int x;
        int cnt;
        Tiii() {
            cnt=y=x=0;
        }
        Tiii (int y, int x, int cnt) {
            this.y = y;
            this.x = x;
            this.cnt = cnt;
        }
    }
    
    boolean inRange(int y, int x) {
        return 0<=y && y<N && 0<=x && x<M;
    }
    
    public int solution(String[] board) {
        N = board.length;
        M = board[0].length();
        
        char[][] matrix = new char[N][M];
        boolean[][] visited = new boolean[N][M];
        
        Tiii start = new Tiii();
        for(int i=0;i<N;i++) {
            for(int j=0;j<M;j++) {
                matrix[i][j] = board[i].charAt(j);
                if(matrix[i][j]=='R') {
                    start.y = i;
                    start.x = j;
                    start.cnt = 0;
                    visited[i][j] = true;
                }
            }
        }
        
        Queue<Tiii> q = new LinkedList<>();
        q.add(start);
        
        while(!q.isEmpty()) {
            Tiii cur = q.poll();
            int y = cur.y;
            int x = cur.x;
            int cnt = cur.cnt;
            if(matrix[y][x]=='G') {
                return cnt;
            }
            for(int i=0;i<4;i++) {
                int ny = y;
                int nx = x;
                
                while(inRange(ny+dy[i],nx+dx[i]) && matrix[ny+dy[i]][nx+dx[i]]!='D') {
                    ny += dy[i];
                    nx += dx[i];
                }
                if(visited[ny][nx]) continue;
                visited[ny][nx] = true;
                q.add(new Tiii(ny,nx, cnt+1));
            }
        }
        
        return -1;
    }
}