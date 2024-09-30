class Solution {
    int n = 1;
    int m = 1;
    int answer = (int)1e9;
    int maxValue = (int)1e9;
    int[] dy = {1,0,-1,0};
    int[] dx = {0,1,0,-1};
    
    class Pii {
        int y, x;
        Pii(int y, int x) {
            this.y=y;
            this.x=x;
        }
        
        Pii(Pii p) {
            y = p.y;
            x = p.x;
        }
        
        boolean isSame(int y, int x) {
            return this.y==y && this.x==x;
        }
        boolean isSame(Pii p) {
            return this.y==p.y && this.x==p.x;
        }
    }
    
    void print(Pii p) {
        print(p.y, p.x);
    }
    boolean inRange(int y, int x) {
        return 0<=y && y<n && 0<=x && x<m;
    }
    public int solution(int[][] maze) {
        n = maze.length;
        m = maze[0].length;
        boolean[][] visited1 = new boolean[n][m];
        boolean[][] visited2 = new boolean[n][m];
        Pii p1 = getLocation(maze, 1);
        Pii p2 = getLocation(maze, 2);
        dfs(p1, p2, maze, visited1, visited2, 0);
        return answer==maxValue ? 0 : answer;
    }
    
    void dfs(Pii p1, Pii p2, int[][] maze, boolean[][] visited1, boolean[][] visited2, int second) {
        if(p1==new Pii(3,2) && p2==new Pii(3,1)) {
            print(1);
        }
        if(second>=answer) return;
        visited1[p1.y][p1.x] = true;
        visited2[p2.y][p2.x] = true;
        boolean flag1 = maze[p1.y][p1.x]==3 ? true : false;
        boolean flag2 = maze[p2.y][p2.x]==4 ? true : false;
        
        if(flag1==false && flag2==false) {        
            for(int i=0;i<4;i++) {
                int ny1 = p1.y + dy[i];
                int nx1 = p1.x + dx[i];
                if(!inRange(ny1,nx1)) continue;
                if(visited1[ny1][nx1]) continue;
                if(maze[ny1][nx1]==5) continue;
                for(int j=0;j<4;j++) {
                    int ny2 = p2.y + dy[j];
                    int nx2 = p2.x + dx[j];
                    if(!inRange(ny2,nx2)) continue;
                    if(visited2[ny2][nx2]) continue;
                    if(maze[ny2][nx2]==5) continue;

                    Pii np1 = new Pii(ny1, nx1);
                    Pii np2 = new Pii(ny2, nx2);

                    if(p2.isSame(np1) && p1.isSame(np2)) continue;
                    if(np2.isSame(np1)) continue;
                    dfs(np1, np2, maze, visited1, visited2, second+1);
                }
            }
        }
        else if(flag1==false) {
            for(int i=0;i<4;i++) {
                int ny1 = p1.y + dy[i];
                int nx1 = p1.x + dx[i];
                if(!inRange(ny1,nx1)) continue;
                if(visited1[ny1][nx1]) continue;
                Pii np1 = new Pii(ny1, nx1);
                if(p2.isSame(np1)) continue;
                if(maze[ny1][nx1]==5) continue;
                dfs(np1, p2, maze, visited1, visited2, second+1);
            }
        }
        else if(flag2==false) {
            for(int i=0;i<4;i++) {
                int ny2 = p2.y + dy[i];
                int nx2 = p2.x + dx[i];
                if(!inRange(ny2,nx2)) continue;
                if(visited2[ny2][nx2]) continue;
                Pii np2 = new Pii(ny2, nx2);
                if(p1.isSame(np2)) continue;
                if(maze[ny2][nx2]==5) continue;
                
                dfs(p1, np2, maze, visited1, visited2, second+1);
            }
        }
        else {
            answer = Math.min(answer, second);
        }
        visited1[p1.y][p1.x] = false;
        visited2[p2.y][p2.x] = false;
    }
    Pii getLocation(int[][] maze, int cur) {
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(maze[i][j]==cur) return new Pii(i,j);
            }
        }
        return null;
    }
    void print(int... args) {
        for(int i : args) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}