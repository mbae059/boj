#include <bits/stdc++.h>

using namespace std;

int N, M;
bool inRange(int y, int x) {
    return 0<=y && y<N && 0<=x && x<M;
}
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

int solution(vector<vector<int>> land) {
    N = land.size();
    M = land.front().size();
    
    vector<vector<int>> dp(N, vector<int>(M));
    vector<vector<int>> visited(N, vector<int>(M));
    
    int idx = 1;
    using pii = pair<int,int>;
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(land[i][j]==0) continue;
            if(visited[i][j]) continue;
            queue<pii> q;
            q.push({i,j});
            visited[i][j] = 1;
            vector<pii> v;
            while(!q.empty()) {
                auto [y, x] = q.front();
                q.pop();
                v.push_back({y,x});
                for(int i=0;i<4;i++) {
                    auto ny = y+dy[i];
                    auto nx = x+dx[i];
                    if(!inRange(ny,nx)) continue;
                    if(visited[ny][nx]) continue;
                    if(land[ny][nx]==0) continue;
                    visited[ny][nx] = 1;
                    q.push({ny,nx});
                }
            }
            
            for(auto [y, x] : v) {
                dp[y][x] = v.size();
                visited[y][x] = idx;
            }
            idx++;
        }
    }
    int answer = 0;
    for(int j=0;j<M;j++) {
        int val = 0;
        set<int> s;
        for(int i=0;i<N;i++) {
            if(visited[i][j]!=0 && s.find(visited[i][j])==s.end()) {
                val += dp[i][j];
                s.insert(visited[i][j]);
            }
        }
        answer = max(answer, val);
    }
    
    return answer;
}