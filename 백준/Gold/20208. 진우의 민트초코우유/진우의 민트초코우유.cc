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
using tiii = tuple<int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
int T, N, K, M, S, H, W, Q; // S is for MCMF, network flow
int dir[4][2] = {{1,0},{-1,0}, {0,1}, {0,-1}};
//ofstream out("temp.txt");
//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;
//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())
bool inRange(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=M;
}
bool inRangeN(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=N;
}
void print(pii a) {
    cout << a.first << " " << a.second << endl;
}

template <typename T>
void print(const T& a) {
    cout << a << endl;
}

template <typename T>
void print(vector<T>& v) {
    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}
vector<int> combination;
bool visited[1005];
#define MAX 12
int matrix[MAX][MAX] {};
pii src;
int mx = 0;
vpii mint;
vi v;

int d[MAX][MAX] {};

int getManhattanDistance(pii a, pii b) {
    return abs(a.first-b.first)+abs(a.second-b.second);
}
void chk() {
    int h = M;
    h -= getManhattanDistance(src, mint[v[0]]);
    if(h<0) return;
    h += K;

    for(int i=0;i<v.size()-1;i++) {
        if(getManhattanDistance(mint[v[i]], src) <= h) {
            mx = max(i+1, mx);
        }
        h -= getManhattanDistance(mint[v[i]], mint[v[i+1]]);
        if(h<0) return;
        h += K;
    }

    h -= getManhattanDistance(mint[v.back()], src);
    if(h<0) return;
    
    cout << v.size();
    exit(0);
}
void Solve() {
    cin >> N >> M >> K;
    rep(i,1,N) {
        rep(j,1,N) {
            cin >> matrix[i][j];
            if(matrix[i][j]==1) {
                src = {i,j};
            }
            if(matrix[i][j]==2) {
                mint.pbk({i,j});
            }
        }
    }
    if(mint.empty()) {
        cout << 0;
        return;
    }
    for(int i=0;i<mint.size();i++) {
        v.pbk(i);
    }
    do {
        chk();
    } while(next_permutation(all(v)));

    cout << mx;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}