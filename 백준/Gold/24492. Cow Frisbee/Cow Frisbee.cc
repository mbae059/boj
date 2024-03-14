#include <bits/stdc++.h>
#define endl '\n'
#define p_q priority_queue
#define pbk push_back
#define double long double
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
#define int ll
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using qpii = queue<pii>;
using tiii = tuple<int, int, int>; //get<0>(t);
using tiiii = tuple<int, int, int, int>;
using vtiii = vector<tiii>;
using vtiiii = vector<tiiii>;
using spii = set<pii>;
using qtiii = queue<tiii>;
int A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
int dy[8] = { 1,-1,0,0,1,1,-1,-1 };
int dx[8] = { 0,0,1,-1,1,-1,1,-1 };
//vvi matrix(N, vector<int>(N));
//for finding the intersection of Line(x1,y1,x2,y2) and Line(x3,y3,x4,y4)
//do not solve with tenary search
// Px= (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4)
// Py= (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4)

//int to string : to_string
//string to int : stoi

//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;

//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())

// unordered_map<char,int> dx = {{'D',0},{'L',-1},{'R',1},{'U',0}};
// unordered_map<char,int> dy = {{'D',1},{'L',0},{'R',0},{'U',-1}}

//diagonal counting. l[y+x], r[y-x+N]

template<typename T, class BinaryOperation = plus<T>>
struct Segtree {
    vector<T> a;
    vector<T> s;
    int n;
    BinaryOperation op;
    Segtree(int n = 1) : n(n), op(BinaryOperation()) {
        a.resize(n + 1);
        s.resize(4 * n + 1);
    }
    T segment(int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight) {
            return s[node] = a[nodeLeft];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return s[node] = op(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
    }
    void update(int node, int nodeLeft, int nodeRight, int idx, T num) {
        if (idx < nodeLeft || nodeRight < idx) return;
        if (nodeLeft == nodeRight) {
            s[node] = num;
            return;
        }
        int mid = (nodeLeft + nodeRight) / 2;
        update(node * 2, nodeLeft, mid, idx, num);
        update(node * 2 + 1, mid + 1, nodeRight, idx, num);

        s[node] = op(s[node * 2], s[node * 2 + 1]);
    }
    T query(int node, int l, int r, int nodeLeft, int nodeRight) {
        if (nodeRight < l || r < nodeLeft) return 0; //could be 0, 1e9, -1e9
        if (l <= nodeLeft && nodeRight <= r) return s[node];
        int mid = nodeLeft + nodeRight >> 1;
        return op(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
    }
    void print(int node, int nodeLeft, int nodeRight) {
        cout << nodeLeft << " " << nodeRight << " : " << s[node] << endl;
        if (nodeLeft == nodeRight) return;

        int mid = (nodeLeft + nodeRight) >> 1;
        print(node * 2, nodeLeft, mid);
        print(node * 2 + 1, mid + 1, nodeRight);
    }
};

struct lazySegtree {
    vi a;
    vi s;
    vi lazy;
    int n;
    lazySegtree(int n) : n(n) {
        a.resize(n + 1);
        s.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }

    int merge(int a, int b) {
        return a + b;
    }
    int segment(int node, int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
        if (nodeLeft == nodeRight) {
            return s[node] = a[nodeLeft];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
    }
    void propagation(int node, int l, int r) {
        if (lazy[node]) {
            s[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void update(int node, int nodeLeft, int nodeRight, int l, int r, int dif=1) { //This is for lazy propagation
        propagation(node, nodeLeft, nodeRight);
        if (nodeRight < l || r < nodeLeft) return;
        if (l <= nodeLeft && nodeRight <= r) {
            s[node] += (nodeRight - nodeLeft + 1) * dif;
            if (nodeLeft != nodeRight) {
                lazy[node * 2] += dif;
                lazy[node * 2 + 1] += dif;
            }
            return;
        }
        int mid = (nodeLeft + nodeRight) / 2;
        update(node * 2, nodeLeft, mid, l, r, dif);
        update(node * 2 + 1, mid+1, nodeRight, l, r, dif);
        s[node] = merge(s[node * 2], s[node * 2 + 1]);
    }
    ll query(int node, int nodeLeft, int nodeRight, int l, int r) { //s should be vll
        propagation(node, nodeLeft, nodeRight);
        if (nodeRight < l || r < nodeLeft) return 0;
        if (l <= nodeLeft && nodeRight <= r) {
            return s[node];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return merge(query(node * 2, nodeLeft, mid, l, r), query(node * 2 + 1, mid+1, nodeRight, l, r));
    }
};

struct DSU {
    vi parent;
    vi depth; //tree depth (maximum distance from root node)
    vi d;
    vi sz;
    stack<tiii> rb; //rollback
    DSU(int n = 1) {
        parent = vi(n + 1);
        depth = vi(n + 1, 0);
        d = vi(n + 1, 0);
        sz = vi(n + 1, 0);
        iota(parent.begin() + 1, parent.end(), 1);
        fill(sz.begin() + 1, sz.end(), 1);
    }
    int getParent(int num) {
        if (num == parent[num]) return num;
        int p = getParent(parent[num]);
        // d[num] += d[parent[num]];
        return parent[num] = p; //path compression
    }

    //modify merge to get difference between a and b
    void merge(int a, int b, ll w = 0) { //merge to b
        // int pa = getParent(a);
        // int pb = getParent(b);

        // d[pb] = d[a] + w - d[b];
        // parent[pb] = pa;

        a = getParent(a);
        b = getParent(b);
        
        if(d[a]<d[b]) swap(a,b);
        
        bool flag = 0;
        if(d[a]==d[b]) {
            d[a]++;
            flag=1;
        }
        parent[b] = a;
        rb.push({a,b,flag});
        sz[a] += sz[b];
    }
    bool isSameParent(int a, int b) {
        return getParent(a)==getParent(b);
    }
    void rollback() {
        if(rb.empty()) return;
        auto [u,v,flag] = rb.top(); //u is root node and v is attached to u
        rb.pop();
        if(flag) d[u]--;
        parent[v] = v;
        sz[u] -= sz[v];
    }
};

void print(pii a) {
    cout << a.first << " " << a.second << endl;
}
void print(tiii a) {
    auto [x, y, z] = a;
    cout << x << " " << y << " " << z << endl;
}
template<typename T>
void print(T* a, int start, int end) {
    rep(i, start, end) cout << a[i] << " ";
    cout << endl;
}

template <typename T>
void print(const T& a) {
    cout << a << endl;
}

void print(const vector<pii>& v) {
    for (auto p : v) {
        print(p);
    }
    cout << endl;
}
void print(const vtiii& v) {
    for (auto p : v) {
        print(p);
    }
    cout << endl;
}
template <typename T>
void print(const vector<T>& v) {
    for (auto i : v) cout << i << " ";
    cout << endl;
}


bool inRange(int y, int x) {
    return 1 <= y && y <= N && 1 <= x && x <= M;
}

bool inRangeN(int y, int x) {
    return 1 <= y && y <= N && 1 <= x && x <= N;
}
vector<string> split(string input, char delimiter = ' ') {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

void yesno(bool a) {
    cout << (a ? "YES" : "NO") << endl;
}

void chmin(int& x, int y) {
    x = min(x, y);
}
void chmax(int& x, int y) {
    x = max(x, y);
}
template<int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template<typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};

template<typename T>
struct Vec<1, T> : public vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};
/*
vector<int> combination;
bool visited[1005];
void dfs(int idx, int cnt) { //implement with dfs(1, 0). N and K must be global variable
    if(cnt==K) {
        for(auto i : combination) {
            cout << i << " ";
        }
        cout << endl;
        return;
    }

    for(int i=idx;i<=N;i++) { //idx, N을 잘볼것
        if(visited[i]==1) continue;

        visited[i]=1;
        combination.push_back(i);
        dfs(i+1, cnt+1); //be careful with i+1, cnt+1
        visited[i]=0;
        combination.pop_back();
    }
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*
//two dimensional fenwick tree
#define MAX 1026
ll arr[MAX][MAX];
ll fenwick[MAX][MAX];

void update(int x, int y, ll value) {
    while(x < N+1) {
        int tempy = y;
        while(tempy < N+1) {
            fenwick[x][tempy] += value;
            tempy += (tempy & -tempy);
        }

        x += (x & -x);
    }
}

//sum(x,y) means sum of arr[1][1]~arr[x][y]
ll sum(int x, int y) {
    ll ret=0;
    while(x>0) {
        int tempy = y;
        while(tempy > 0) {
            ret += fenwick[x][tempy];
            tempy -= (tempy & -tempy);
        }
        x -= (x & -x);
    }
    return ret;
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// THIS IS TARJAN ALGORITHM FOR SCC

/*
#define MAX 10001 //when used in 2-sat, you have to double node because not only x1~x100 is required but also Nx1~Nx100
vvi SCC;
int d[MAX];
bool finished[MAX];
vi edge[MAX];
int id, SN=0; //mark sn[i]
stack<int> s;
int sn[MAX]; //sn[i] is SCC number to which it belongs to. If sn is big, then it is at the start of DAG. If small, it is at the end of DAG. If one wants to start from the beginning of DAG, start from the largest of sn.
int SCCnode[MAX] {}; //if SCCbfs is needed...
int nodeValue[MAX] {}; //if SCCbfs is needed...
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
            //SCCnode[SN] += nodeValue[t];
            if (t == x) break;
        }
        SN++;
        SCC.push_back(scc); //SCC의 SN번째 그래프랑 대응된다
    }
    return parent;
}

vi SCCedge[MAX]; //index refers to SN. Could be replaced with set if you don't want to overlap
int inDegree[MAX]; //index refers to SN
void SCCtopology_sort() {
    for(int i=1;i<=N;i++) { //id starts with 1
        for(auto next : edge[i]) {
            if(sn[next]!=sn[i]) {
                SCCedge[sn[i]].pbk(sn[next]); //SN could be overlapped. Could be solved with set but it is often not needed
                inDegree[sn[next]]+=1; //If inDegree is 0, then it is the start of the SCC graph. There could be many
            }
        }
    }
}

//If SCC sum is needed
int SCCdp[MAX] {};
void SCCbfs(int x) { //x is sn. bfs graph is not vertex graph but scc graph. scc graph is DAG so visited array is not needed
    //bfs starts with x. Function flows through SCC graph (topologically)
    qi q;
    q.push(x);
    SCCdp[x] = SCCnode[x];

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(auto next : SCCedge[cur]) {
            if(SCCdp[next] < SCCdp[cur] + nodeValue[next]) {
                SCCdp[next] = SCCdp[cur] + nodeValue[next];
                q.push(next);
            }
        }
    }
}

int oppo(int num) { //This is for 2-sat
    return num % 2 ? num + 1 : num - 1;
}

int result[MAX] {}; //For finding value of each clause (x1, x2, x3)
void sat2() { // (x1 or x2) and (Nx1 or x3) //Nx1->x2, Nx2->x1. x1->x3, Nx3->Nx1
    cin >> N >> M; // N is # of node, M is # of conditions
    for (int i = 0; i < M; i++) {
        int A, B; //If num is negative #, then it is (not) positive num
        cin >> A >> B;
        A = A > 0 ? 2 * A - 1 : -2 * A; //positive num goes 1->1, 2->3, 3->5, 4->7, 5->9... and so on
        B = B > 0 ? 2 * B - 1 : -2 * B; //negative num goes -1->2, -2->4, -3->6, -4->8... and so on
        edge[oppo(A)].push_back(B);
        edge[oppo(B)].push_back(A);
    }
    for (int i = 1; i <= 2 * N; i++) { //node is 1~2*N
       if (d[i] == 0) dfs(i);
    }
    for (int i = 1; i <= N; i++) {
        if (sn[2 * i-1] == sn[2 * i]) {
            cout << "contradiction!" << " " << sn[i] << endl;
        }
    }

    //For finding out value of each clause

    memset(result, -1, sizeof(result));
    pii p[MAX];
    for(int i=1;i<=2*N;i++) {
        p[i] = {sn[i], i};
    }
    sort(p+1, p+2*N+1);

    for(int i=2*N;i>0;i--) { //Start from the beginning of DAG
        int node = p[i].second;
        int src = (node+1)/2;

        if(result[src] == -1) result[src] = node%2 ? 0 : 1;
    }

    for(int i=1;i<=N;i++) {
        cout << result[i] << " ";
    }
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//This is SPFA 
/*
#define MAX 100001
bool inQ[MAX] {};
vpii edge[MAX];
int d[MAX];
int cycle[MAX] {};
void SPFA(int start) {
    fill(d+1, d+1+N, 1e9);
    qi q;
    d[start] =0;
    q.push(start);
    inQ[start] = 1;
    cycle[start] += 1;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        inQ[cur] = 0;
        for(auto next : edge[cur]) {
            if(d[next.first] > d[cur] + next.second) {
                d[next.first] = d[cur] + next.second;
                if(!inQ[next.first]) {
                    cycle[next.first] += 1;
                    if(cycle[next.first]>=N) {
                        cout << "CYCLE!!!!" << endl;
                        return;
                    }
                    q.push(next.first);
                    inQ[next.first] = 1;
                }
            }
        }
    }
}
*/

// This is Floyd-Warshall
/*
#define MAX 501
int dp[MAX][MAX] {}; //input should be done in dp table
void floyd_warshall() {
    rep(k, 1, N) {
        rep(i, 1, N) {
            rep(j, 1, N) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) dp[i][j] = dp[i][k] + dp[k][j];
            }
        }
    }
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//This is Network Flow with Dinic Algorithm. Time Complexity O(V^2 * E)

// 
/*
#define MAX 100 //MAX should be treated carefully since space complexity is limited. (256mb, 512mb)
vector<int> edge[MAX];
int f[MAX][MAX], c[MAX][MAX];
int level[MAX], work[MAX];
int src, sink;
int bias;

void addEdge(int s, int e, int value=1) { //Decide whether graph is directed graph or undirected graph
    edge[s].pbk(e);
    edge[e].pbk(s);
    c[s][e] = value;
}
bool bfs() { // to create level graph and decide if flow is no longer needed
    queue<int> q;
    q.push(src); //
    memset(level, -1, sizeof(level));
    level[src] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto next : edge[cur]) {
            if (level[next] == -1 && c[cur][next] - f[cur][next] > 0) {
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
    }
    if (level[sink] == -1) return false;
    else return true;
}
int dfs(int cur, int flow) { //cur node has flow to offer to the next level
    if (cur == sink) return flow;

    for (int& i = work[cur]; i < edge[cur].size(); i++) {
        int next = edge[cur][i];
        if (level[next] == level[cur] + 1 && c[cur][next] - f[cur][next] > 0) {
            int ret = dfs(next, min(flow, c[cur][next] - f[cur][next]));
            if (ret > 0) {
                f[cur][next] += ret;
                f[next][cur] -= ret; //always remember to create reverse flow
                return ret;
            }
        }
    }
    return 0;
}
int Network_Flow() {
    int totalFlow = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (true) {
            int flow = dfs(src, 1e9); //INF varies from range to range
            if (flow == 0) break;
            totalFlow += flow;
        }
    }
    return totalFlow;
}
*/


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//Network Flow with Edmonds Karp
/*
#define MAX 100
int d[MAX] {}; //keep track of parent
vi edge[MAX];
int f[MAX][MAX], c[MAX][MAX];
int maxFlow(int start, int end) {
    int result=0;
    while(1) {
        fill(d, d+MAX, -1);
        qi q;
        q.push(start);

        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            for(auto next : edge[cur]) {
                if(c[cur][next]-f[cur][next] > 0 && d[next]==-1) {
                    q.push(next);
                    d[next] = cur;
                    if(next==end) break;
                }
            }
        }

        if(d[end]==-1) break;

        int flow = 1e9;

        for(int i=end;i!=start;i=d[i]) {
            flow = min(flow, c[d[i]][i] - f[d[i]][i]);
        }

        for(int i=end;i!=start;i=d[i]) {
            f[d[i]][i] += flow;
            f[i][d[i]] -= flow;
        }
        result += flow;
    }
    return result;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//MCMF with SPFA+Edmonds-Karp

/*
#define MAX 1001
int f[MAX][MAX]; //flow
int c[MAX][MAX]; //capacity
int d[MAX][MAX]; //cost of flowing fluid. f[x][y] * d[x][y] is
int S, T;
vi edge[MAX];
int bias; //set bias in bipartite graph
//MCMF could be done with Dinic but is not effective unless it has sparse table
//https://justicehui.github.io/hard-algorithm/2020/03/24/effective-mcmf/
//but it is nonetheless more effective than SPFA+Edmonds-Karp
void MCMF() {
    //set S and T
    //input edge

    ll result =0;
    while(1) {
        int prev[MAX]{}; //record previous node
        int dist[MAX]{}; //record
        bool inQ[MAX] {};

        fill(prev, prev+MAX, -1);
        fill(dist, dist+MAX, 1e9);

        qi q;
        q.push(S);
        inQ[S] = 1;
        dist[S] = 0;
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            inQ[cur] =0;

            for(auto next : edge[cur]) {
                if(c[cur][next]-f[cur][next] > 0 && dist[next] > dist[cur] + d[cur][next]) {
                    dist[next] = dist[cur] + d[cur][next];
                    prev[next] = cur;

                    if(!inQ[next]) {
                        inQ[next] = 1;
                        q.push(next);
                    }
                }
            }
        }

        if(prev[T]==-1) break;

        int flow = 1e9;
        for(int i = T;i!=S;i=prev[i]) {
            flow = min(flow, c[prev[i]][i]-f[prev[i]][i]);
        }


        for(int i = T;i!=S;i=prev[i]) {
            result += flow * d[prev[i]][i];
            f[prev[i]][i] += flow;
            f[i][prev[i]] -= flow;
        }
    }
    cout << result;
}

*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// This is CCW

//depending on input, the value ccw could be beyond INTEGER. Even long long could be dangerous. Watch carefully on input range
/*
struct Point {
    ll x, y;
    Point(ll x, ll y) : x(x), y(y) {}
};
struct Line {
    Point p1, p2;
};
ll CCW(Point A, Point B, Point C) { //A, B, C is in order
    ll ccw = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y); //Cross product
    if(ccw>0) return 1;
    else if(ccw<0) return -1;
    else return 0;
}
//
int LineInterSection(Line l1, Line l2) {
    ll l1_l2 = CCW(l1.p1, l1.p2, l2.p1) * CCW(l1.p1, l1.p2, l2.p2);
    ll l2_l1 = CCW(l2.p1, l2.p2, l1.p1) * CCW(l2.p1, l2.p2, l1.p2);

    if(l1_l2==0 && l2_l1==0) { //l1 and l2 is on the same line. If p1 <= p4 && p3 <= p2, the line meets.
        if(l1.p1.x > l1.p2.x) swap(l1.p1, l1.p2);
        if(l2.p1.x > l2.p2.x) swap(l2.p1, l2.p2);

        return l1.p1.x <= l2.p2.x && l2.p1.x <= l1.p2.x;
    }
    return (l1_l2 <= 0) && (l2_l1 <= 0);
}
vector<Point> v;
bool cmp(const Point& a, const Point& b) {
    ll ccw = CCW(v[0], a, b);
    if(ccw) return ccw>0;
    if(a.y==b.y) return a.x < b.x;
    return a.y < b.y;
}
stack<Point> s;
//to find if X point exists within the convex polygon, do CCW(i,i+1,X point) and see if CCW value is the same for all
void Convex_Hull() {
    sort(all(v), [](Point a, Point b) {
        if(a.y==b.y) return a.x<b.x;
        return a.y<b.y;
    });

    sort(v.begin()+1, v.end(), cmp);

    s.push(v[0]);
    s.push(v[1]);

    rep(i,2,N-1) {
        while(s.size()>=2) {
            auto t2 = s.top();
            s.pop();
            auto t1 = s.top();

            if(CCW(t1, t2, v[i])>0) {
                s.push(t2);
                break;
            }
        }
        s.push(v[i]);
    }
    cout << s.size();
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// This is LCA with binary algorithm (O(logN))
/*
#define MAX 100001
vi edge[MAX];
//vpii edge[MAX] {};
//int d[MAX][18];
int parent[MAX][18]; //18 is log2(MAX)
int level[MAX];
int maxLevel;

//init -> set_tree -> LCA(a,b)
void init() {
    cin >> N; //Has N node and N-1 edges
    for(int i=0;i<N-1;i++) {
        int a, b;
        cin >> a >> b;
        edge[a].pbk(b);
        edge[b].pbk(a);
    }
    maxLevel = (int)floor(log2(MAX));
}
//maps node and depth and set 2^i parent
//use before LCA function
//set_tree(root, 0) should do it
//if node 0 exists, then this function needs to be altered
//get root node by inDegree array.
void set_tree(int node, int pnode) {
    level[node] = level[pnode]+1;
    parent[node][0] = pnode;

    for(int i=1;i<=maxLevel;i++) {
        int prev = parent[node][i-1];
        parent[node][i] = parent[prev][i-1];
        //d[node][i] = d[prev][i-1] + d[node][i-1];
    }

    for(auto child : edge[node]) {
        if(child==pnode) continue;
        //d[child.first][0] = child.second;
        set_tree(child, node);
    }
}

int LCA(int a, int b) {
    if(a==1 || b==1) return 1;

    int target = a, compare = b;
    if(level[a] < level[b]) swap(target, compare); //target is deeper

    // int answer = 0; //for length
    //set level[] equal
    if(level[target]!=level[compare]) {
        for(int i=maxLevel;i>=0;i--) {
            if(level[parent[target][i]] >= level[compare]) {
                //answer += d[target][i];
                target = parent[target][i];
            }
        }
    }

    int ret = target;

    //set target==compare
    if(target!=compare) {
        for(int i=maxLevel;i>=0;i--) {
            if(parent[target][i]!=parent[compare][i]) {
                // answer += d[target][i];
                // answer += d[compare][i];

                target = parent[target][i];
                compare = parent[compare][i];
            }
            ret = parent[target][i];
        }
    }
    //answer += d[target][0] + d[compare][0];
    return ret;
}

*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
void LIS(vi& v) { //vector v's size is N
    vi lis;
    vi dp(N);

    fill(all(dp), 1); //set all dp element to at least 1
    rep(i,0,N-1) { // N
        int cur = v[i];

        //whether it should be lower_bound or upper_bound depends on the problem
        //if non-decreasing sequence is allowed, for example 10 10 20 30... then it should be upper_bound
        //if only strictly increasing sequence is allowed, for example 10 20 40... then it should be lower_bound
        //https://www.acmicpc.net/problem/12738    this problem only allows strictly increasing order meaning one should use lower_bound
        //https://www.acmicpc.net/problem/2352     this problem also allows strictly increasing order but the element in array is never overlapped so it can use both lower_bound and upper_bound
        //to create LDS (longest decreasing sequence), simply invert sign.

        auto iter = lower_bound(all(lis), cur);
        //if found, replace the value with cur. if not, cur is the highest value of lis
        if(iter!=lis.end()) {
            *iter = cur;
            dp[i] = iter - lis.begin()+1;
        }
        else {
            lis.pbk(cur);
            dp[i] = lis.size();
        }
    }
    stack<int> s;

    int sz = *max_element(all(dp)); //LIS size
    cout << sz << endl;
    for(int i=N-1;i>=0;i--) {
        if(sz==dp[i]) {
            s.push(v[i]);
            sz--;
        }
    }

    while(!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*

//big integer addition
string add(string a, string b) {
    // Initialize variables
    string result = "";
    int carry = 0;
    int a_len = a.length();
    int b_len = b.length();

    // Loop through both strings, starting at the last character
    for (int i = a_len - 1, j = b_len - 1; i >= 0 || j >= 0 || carry; i--, j--)
    {
        // Get the current digit of each string, or 0 if we have reached the beginning
        int x = (i >= 0) ? a[i] - '0' : 0;
        int y = (j >= 0) ? b[j] - '0' : 0;

        // Add the digits and carry, and store the result
        result = char((x + y + carry) % 10 + '0') + result;

        // Calculate the new carry
        carry = (x + y + carry) / 10;
        cout << "CARRY : " << carry << endl;
    }

    return result;
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Trie
/*
#define TRIENODE 26
struct Trie {
    Trie *next[TRIENODE]; // 다음 노드를 가리키는 포인터 배열
    //map<string, Trie*> next;
    bool finish;
    Trie *fail; //for Aho-corasick
    Trie() {
        fill(next, next + TRIENODE, nullptr);
        finish = false;
    }

    ~Trie() {
        for (int i = 0; i < TRIENODE; i++) {
            if (next[i]) delete next[i];
        }
    }

    int getIdx(char c) {
        return c-'A';
    }
    void insert(const string& str, int k=0) {
        if (k==str.size()) {
            finish = true;
            return;
        }

        int curKey = getIdx(str[k]); //or 'a' or '0'

        if (next[curKey]==nullptr) next[curKey] = new Trie();

        next[curKey]->insert(str, k+1); // 다음 문자 삽입
    }

    void init() { //Aho-corasick. use when this is root
        queue<Trie*> q;
        q.push(this);

        while(!q.empty()) {
            Trie* cur = q.front();
            q.pop();

            for(int i=0;i<TRIENODE;i++) {
                Trie *nextTrie = cur->next[i];
                if(nextTrie==nullptr) continue;

                if(cur==this) {
                    nextTrie->fail = this;
                }
                else {
                    Trie *dest = cur->fail;

                    while(dest!=this && dest->next[i]==nullptr) {
                        dest = dest->fail;
                    }
                    if(dest->next[i]) dest = dest->next[i];

                    nextTrie->fail = dest;
                }
                if(nextTrie->fail->finish) nextTrie->finish = true;
                q.push(nextTrie);
            }
        }
    }

    void query(const string& str) { //for Aho-corasick
        Trie *cur = this;
        int cnt = 0;
        for(auto c : str) {
            int curKey = getIdx(c);

            while(cur!=this && cur->next[curKey]==nullptr) {
                cur = cur->fail;
            }

            if(cur->next[curKey]) cur = cur->next[curKey];

            if(cur->finish) cnt++;
        }
    }
    bool find(const string& str, int k=0) {
        if (k==str.size()) return true; // 문자열이 끝나는 위치를 반환
        int curKey = getIdx(str[k]); //or 'a' or '0'
        if (next[curKey] == nullptr) return false; // 찾는 값이 존재하지 않음
        return next[curKey]->find(str, k+1); // 다음 문자를 탐색
    }
};

*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
//KMP
vi getPi(const string& pattern) {
    int patternSize = pattern.size();

    vi pi(patternSize);

    int j = 0;
    for(int i=1;i<patternSize;i++) {
        while(j>0 && pattern[i] != pattern[j]) {
            j = pi[j-1];
        }

        if(pattern[i]==pattern[j]) {
            j+=1;
            pi[i] = j;
        }
    }
    return pi;
}

void KMP(const string& parent, const string& pattern) {
    vi pi = getPi(pattern);

    int parentSize = parent.size();
    int patternSize = pattern.size();

    int j =0;

    for(int i=0;i<parentSize;i++) {
        while(j>0 && parent[i] != pattern[j]) {
            j = pi[j-1];
        }
        if(parent[i] == pattern[j]) {
            if(j == patternSize-1) {
                cout << i-patternSize + 2 << endl; //index starts from 1
                j = pi[j];
            }
            else {
                j++;
            }
        }
    }
}

*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
//https://kangminjun.tistory.com/entry/Manacher-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
//This is manachar's algorithm for finding biggest palindrome in substring
#define MAX 200001
int A[MAX] {}; //saves the sz of palindrome each side including i itself
string preprocess(const string& str) { //to find even palindrome as well
    string temp;
    for(auto c : str) {
        temp.pbk('#');
        temp.pbk(c);
    }
    temp.pbk('#');
    return temp;
}
void manacher(string str) {
    int r = 0, p = 0; //p is the value that maximize j+A[j]
    str = preprocess(str);
    int sz = str.size();

    for (int i = 0; i < sz; i++) {
        if (i <= r) {
            A[i] = min(A[2 * p - i], r - i);
        }
        while (i-A[i]-1>=0 && i+A[i]+1<sz && str[i-A[i]-1]==str[i+A[i]+1]) {
            A[i]++;
        }
        if (r < i + A[i]) {
            r = i + A[i];
            p = i;
        }
    }
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
//typical bipartite problems can be solved with dinic as it will work in O(E * √V)
//but memory will be N*M whereas Hopcroft_Karp will use max(N,M) + E
//so use dinic when N,M <=1000 and Hopcroft_Karp when N,M>1000
//This is Hopcroft_Karp Algorithm
#define MAX 10001
vi edge[MAX];
bool used[MAX];
//matched with A/B group. Thus B[A[i]] == i
//set initial value of A, B to -1
int a[MAX] {};
int b[MAX] {};
//dist does not need to be initialized as it is set in bfs
int dist[MAX] {}; //distance between non matched vertex in A
void bfs() { //set dist array
    qi q; //push only A array not B

    for(int i=1;i<=N;i++) {
        if(used[i]==0) {
            dist[i]=0;
            q.push(i);
        }
        else {
            dist[i]=1e9;
        }
    }

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(auto next : edge[cur]) {
            if(b[next]!=-1 && dist[b[next]]==1e9) {
                dist[b[next]] = dist[cur] + 1;
                q.push(b[next]);
            }
        }
    }
}

bool dfs(int cur) {
    for(auto next : edge[cur]) {
        if(b[next]==-1 || (dist[b[next]] == dist[cur]+1 && dfs(b[next]))) {
            used[cur] = 1;
            a[cur] = next;
            b[next] = cur;
            return true;
        }
    }
    return false;
}
void Hopcroft_Karp() {
    int totalFlow = 0;
    while(true) {
        bfs();

        int flow =0;
        for(int i=1;i<=N;i++) {
            if(used[i]==0 && dfs(i)) flow++;
        }
        if(flow==0) break;
        totalFlow += flow;
    }
    cout << totalFlow << endl;
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
//bipartite matching

#define MAX 1001
vi edge[MAX];
bool done[MAX] {};
int b[MAX] {};
//for 1~N memset(done, done+MAX, 0), if(dfs(i)) cnt++;
bool dfs(int cur) {
    for(auto next : edge[cur]) {
        if(done[next]) continue;
        done[next] = 1;

        if(b[next]==0 || dfs(b[next])) {
            b[next] = cur;
            return true;
        }
    }
    return false;
}
*/
void Solve() {
    cin >> N;
    int a[N+1] {};
    rep(i,1,N) cin >> a[i];

    stack<pii> s;

    int answer=0;
    s.push({a[1], 1});
    rep(i,2,N) {
        int cnt = 0;
        int val = 0;
        while(!s.empty() && s.top().first < a[i]) {
            cnt++;
            val += s.top().second;
            int pre = s.top().second;
            s.pop();
            if(!s.empty()) answer += pre - s.top().second + 1;
        }
        s.push({a[i], i});
        answer += (i+1)*cnt - val;
    }
    while(!s.empty()) {
        int pre = s.top().second;
        s.pop();
        if(!s.empty()) answer += pre - s.top().second + 1;
    }
    print(answer);
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}