#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()

using namespace std;
using pii = pair<int, int>;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vull = vector<ull>;
using vvi = vector<vi>;
using vpii = vector<pii> ;
using vll = vector<ll>;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using qpii = queue<pii>;
using tiii = tuple<int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using spii = set<pii>;
int T, N, K, M, S, H, W, Q; // S is for MCMF, network flow
int dir[8][2] = {{-1,0},{0,1}, {1,0}, {0,-1}, {1,1},{1,-1},{-1,1},{-1,-1}};
void print(pii a) {
    cout << a.first << " " << a.second << endl;
}

template <typename T>
void print(const T& a) {
    cout << a << endl;
}

void print(const vector<pii>& v) {
    for(auto p : v) {
        print(p);
    }
    cout << endl;
}
template <typename T>
void print(const vector<T>& v) {
    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}
bool inRange(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=M;
}
bool inRangeN(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=N;
}

bool visited[55][55] {};
char matrix[55][55] {};

struct Robot {
    int y, x;
    int d;

    Robot(int y, int x, int d) : y(y), x(x), d(d) {}
    Robot() {
        y=x=d=0;
    }
    void turn() {
        d = (d+3)%4;
    }

    void backup() {
        int bd;
        switch(d) {
            case 0:
            bd = 2;
            break;

            case 1:
            bd = 3;
            break;

            case 2:
            bd = 0;
            break;

            case 3:
            bd = 1;
            break;
        }
        y += dir[bd][0];
        x += dir[bd][1];
    }

    void clean() {
        visited[y][x] = 1;
    }
    bool search() {
        bool flag = 0;
        rep(i,0,3) {
            int nexty = y+dir[i][0];
            int nextx = x+dir[i][1];
            if(visited[nexty][nextx]) continue;
            if(matrix[nexty][nextx]=='1') continue;
            return true;
        }
        return false;
    }
    void dust() {
        rep(i,0,3) {
            turn();
            int nexty = y+dir[d][0];
            int nextx = x+dir[d][1];
            if(visited[nexty][nextx]) continue;
            if(matrix[nexty][nextx]=='1') continue;
            
            y = nexty;
            x = nextx;
            clean();
            break;
        }
    }
    void print() {
        cout << y << " " << x << endl;
        rep(i,1,N) {
            rep(j,1,M) cout << visited[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
};

void Solve() {
    cin >> N >> M;
    Robot robot = Robot();
    cin >> robot.y >> robot.x >> robot.d;
    robot.y++;
    robot.x++;

    robot.clean();
    rep(i,1,N) {
        rep(j,1,M) {
            cin >> matrix[i][j];
        }
    }
    int answer = 1;
    while(true) {
        if(robot.search()) {
            answer++;
            robot.dust();
        }
        else {
            robot.backup();
            if(matrix[robot.y][robot.x]=='1') break;
        }
    }
    cout << answer;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}