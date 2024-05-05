#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
 
int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};
 
 
void Solve() {
    int N,M,TG,TB, X, B; cin >> N >> M >> TG >> TB >> X >> B;
 
    char matrix[N+1][M+1] {};
    bool visited[N+1][M+1] {};
    bool virus[N+1][M+1] {};
    queue<tuple<int,int,int>> q; //y,x,t
    queue<tuple<int,int,int>> bq; //building queue
 
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            cin >> matrix[i][j];
            if(matrix[i][j]=='*') {
                q.push({i,j,0});
                visited[i][j] = 1;
            }
        }
    }
 
    auto inRange = [&N, &M](int y, int x) {
        return 1<=y && y<=N && 1<=x && x<=M;
    };
 
    auto getQ = [&](queue<tuple<int,int,int>> &q1, queue<tuple<int,int,int>> &q2) {
        if(q1.empty()) {
            auto ret = q2.front();
            q2.pop();
            return ret;
        }
        
        if(q2.empty()) {
            auto ret = q1.front();
            q1.pop();
            return ret;
        }
 
        auto [y1,x1,t1] = q1.front();
        auto [y2,x2,t2] = q2.front();
 
        if(t1<t2) {
            auto ret = q1.front();
            q1.pop();
            return ret;
        }
        else {
            auto ret = q2.front();
            q2.pop();
            return ret;
        } 
    };
    while(!q.empty() || !bq.empty()) {
        auto [y,x,t] = getQ(q,bq);
        if(t>TG) break;
 
        virus[y][x] = 1;
        for(int i=0;i<4;i++) {
            int ny = y+dy[i];
            int nx = x+dx[i];
            if(!inRange(ny,nx)) continue;
            if(visited[ny][nx]) continue;
 
            visited[ny][nx] = 1;
            //when encountered with building
            if(matrix[ny][nx]=='#') bq.push({ny,nx,t+TB+1});
            //normal place
            else q.push({ny,nx,t+1});
        }
    }
    
    vector<pair<int,int>> answer;
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            if(!virus[i][j]) answer.push_back({i,j});
        }
    }
    if(answer.empty()) cout << -1;
    else for(auto [y,x] : answer) cout << y << " " << x << endl;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}
