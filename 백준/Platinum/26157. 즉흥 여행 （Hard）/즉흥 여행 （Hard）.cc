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
#define MAX 200003 //when used in 2-sat, you have to double node because not only x1~x100 is required but also Nx1~Nx100
vvi SCC;
int d[MAX] {};
bool finished[MAX] {};
vi edge[MAX];
int id=0, SN=0; //mark sn[i]
stack<int> s;
int sn[MAX] {}; //sn[i] is SCC number to which it belongs to. If sn is big, then it is at the start of DAG. If small, it is at the end of DAG. If one wants to start from the beginning of DAG, start from the largest of sn.
int dfs(int x) {
    d[x] = ++id; //노드마다 고유한 아이디 부여
    s.push(x); //스택에 자기 자신을 삽입
    int parent = d[x];
    for (auto i : edge[x]) {
        if (d[i] == 0) { //방문 안 한 이웃
            parent = min(parent, dfs(i));
        }
        else if (finished[i] == 0) { //처리 중인 이웃
            parent = min(parent, d[i]);
        }
    }
    if (parent == d[x]) {
        vector<int> scc;
        while (true) {
            int t = s.top();
            s.pop();
            scc.push_back(t);
            finished[t] = 1;
            sn[t] = SN;
            //d[t] = x; //to make scc recognizable with d
            if (t == x) break;
        }
        SN++;
        SCC.push_back(scc); //SCC의 SN번째 그래프랑 대응된다
    }
    return parent;
}

si SCCedge[MAX]; //index refers to SN. Could be replaced with set if you don't want to overlap
int inDegree[MAX] {}; //index refers to SN
void SCCtopology_sort() {
    for(int i=1;i<=N;i++) { //id starts with 1
        for(auto next : edge[i]) {
            if(sn[next]!=sn[i] && SCCedge[sn[i]].find(sn[next])==SCCedge[sn[i]].end()) {
                SCCedge[sn[i]].insert(sn[next]);
                inDegree[sn[next]]+=1; //If inDegree is 0, then it is the start of the SCC graph. There could be many
            }
        }
    }
}
bool bfs(int num) {
    qi q;
    int cnt = 0;
    q.push(num);
    while(!q.empty()) {
        if(q.size()>1) return false;
        int cur = q.front();
        q.pop();
        cnt++;
        for(auto next : SCCedge[cur]) {
            inDegree[next]-=1;
            if(inDegree[next]==0) {
                q.push(next);
            }
        }
    }
    return cnt==SN;
}
void Solve() {
    cin >> N >> M;
    rep(i,1,M) {
        int a, b; cin >> a >> b;
        edge[a].pbk(b);
    }
    rep(i,1,N) {
        if(d[i]==0) dfs(i);
    }
    SCCtopology_sort();

    vi v;
    rep(i,1,N) {
        if(inDegree[sn[i]]==0) {
            v.pbk(i);
        }
    }
    
    if(bfs(sn[v.front()])) {
        cout << v.size() << endl;
        for(auto i : v) cout << i << " ";
    }
    else {
        cout << 0;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}