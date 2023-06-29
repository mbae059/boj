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
int dy[9] = {0,-1,-1,0,1,1,1,0,-1};
int dx[9] = {0,0,-1,-1,-1,0,1,1,1};
//ofstream out("temp.txt");
//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;
//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())
// unordered_map<char,int> dx = {{'D',0},{'L',-1},{'R',1},{'U',0}};
// unordered_map<char,int> dy = {{'D',1},{'L',0},{'R',0},{'U',-1}}
//diagonal counting. l[y+x], r[y-x+N]
bool inRangeN(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=N;
}

struct Shark {
    int y, x;
    int dir;
    int point;

    Shark(int y, int x, int dir, int point) : y(y), x(x), dir(dir), point(point) {}
    Shark() : Shark(0,0,0,0) {}
    void eat(int point) {
        this->point += point;
    }
    void setDir(int dir) {
        this->dir = dir;
    }
    void setPlace(int y, int x) {
        this->y = y;
        this->x = x;
    }
};
struct Fish {
    int num;
    int dir;

    Fish(int num, int dir) : num(num), dir(dir) {}
    Fish() {
        Fish(0,0);
    }
    Fish(const Fish& other) {
        num = other.num;
        dir = other.dir;
    }
    void turnDirection() {
        dir++;
        if(dir==9) dir = 1;
    }
    void die() {
        num = -1;
        dir = -1;
    }
    bool empty() {
        return num==-1 && dir==-1;
    }

    void move(int y, int x, array<array<Fish, 5>, 5>& matrix, const Shark& shark) {
        for(int i=1;i<=8;i++) {
            int nexty = y+dy[dir];
            int nextx = x+dx[dir];
            
            if(!inRangeN(nexty, nextx) || nexty==shark.y && nextx==shark.x) {
                turnDirection();
                continue;
            }
                
            if(matrix[nexty][nextx].empty()) {
                matrix[nexty][nextx] = *this;
                die();
                return;
            }
            Fish temp = matrix[nexty][nextx];
            matrix[nexty][nextx] = *this;
            matrix[y][x] = temp;
            return;
        }
    }
    void operator = (const Fish& fish) {
        num = fish.num;
        dir = fish.dir;
    }
};

int answer =0;

void print(array<array<Fish, 5>,5>& matrix) {
    rep(i,1,N) {
        rep(j,1,N) cout << matrix[i][j].num << " ";
        cout << endl;
    }
    cout << endl;
}
void dfs(int y, int x, array<array<Fish, 5>,5> matrix, Shark shark) {
    shark.eat(matrix[y][x].num);
    shark.setDir(matrix[y][x].dir);
    shark.setPlace(y,x);
    matrix[y][x].die();
    vector<Fish> v;
    rep(idx, 1, 16) {
        [&] () {
            rep(i,1,N) {
                rep(j,1,N) {
                    if(idx==matrix[i][j].num) {
                        matrix[i][j].move(i, j, matrix, shark);
                        return;
                    }
                }
            } 
        } ();
    }
    answer = max(answer, shark.point);
    for(int i=1;;i++) {
        int nexty = y+dy[shark.dir]*i;
        int nextx = x+dx[shark.dir]*i;
        if(!inRangeN(nexty, nextx)) break;
        if(matrix[nexty][nextx].empty()) continue;
        dfs(nexty, nextx, matrix, shark);
    }
}
void Solve() {
    N = 4;
    array<array<Fish, 5>, 5> matrix;
    Shark shark = Shark();
    rep(i,1,4) {
        rep(j,1,4) {
            cin >> matrix[i][j].num >> matrix[i][j].dir;
        }
    }
    dfs(1,1, matrix, shark);
    cout << answer;
}
int main() {
    Solve();
}