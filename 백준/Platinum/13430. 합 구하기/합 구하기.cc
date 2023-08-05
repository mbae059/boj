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
#define int ll
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
using tlll = tuple<ll, ll, ll> ; //get<0>(t);
using vtiii = vector<tiii>;
using vtlll = vector<tlll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using spii = set<pii>;
using qtiii = queue<tiii>;
int A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z;
int dy[8] = {1,-1,0,0,1,1,-1,-1};
int dx[8] = {0,0,1,-1,1,-1,1,-1};
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

//supports negative modular operation
ll modular(ll num, ll mod) {
    num%=mod;
    return num < 0 ? num+mod : num;
}
void print(pii a) {
    cout << a.first << " " << a.second << endl;
}
template<typename T>
void print(T *a, int start, int end) {
    rep(i,start,end) cout << a[i] << " ";
    cout << endl;
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
    for(auto i : v) cout << i << " ";
    cout << endl;
}
bool inRange(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=M;
}
bool inRangeN(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=N;
}
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

// This is segment tree
/*
#define MAX 100001
ll a[MAX], s[4*MAX];

ll merge(ll a, ll b) { //for operation of the segment tree
    return a+b;
}
ll segment(int node, int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return s[node] = a[nodeLeft];
    }
	int mid = (nodeLeft+nodeRight)/2;
    return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
}
void update(int node, int idx, int nodeLeft, int nodeRight, ll num) {
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s[node] = num;
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update(node * 2, idx, nodeLeft, mid, num);
    update(node * 2 + 1, idx, mid + 1, nodeRight, num);

    s[node] = merge(s[node * 2], s[node * 2 + 1]);
}
ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s[node];
	int mid = (nodeLeft+nodeRight)/2;
    return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
}
void print(int node, int nodeLeft, int nodeRight) {
    cout << nodeLeft << " " << nodeRight << " : " << s[node] << endl;
    if(nodeLeft==nodeRight) return;

    int mid = (nodeLeft + nodeRight) >> 1;
    print(node*2, nodeLeft, mid);
    print(node*2+1, mid+1, nodeRight);
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
//This is lazy propagation. Beginning starts with segment(..) used in above
#define MAX 100001
ll a[MAX], s[4*MAX];
ll merge(ll a, ll b) { //for operation of the segment tree
    return a+b;
}
ll segment(int node, int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return s[node] = a[nodeLeft];
    }
	int mid = (nodeLeft+nodeRight)/2;
    return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
}
ll lazy[4*MAX] {};
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
void update(int node, int l, int r, int nodeLeft, int nodeRight, int dif) { //This is for lazy propagation
    propagation(node, nodeLeft, nodeRight);
    if (nodeRight < l || r < nodeLeft) return;
    if (l <= nodeLeft && nodeRight <= r) {
        s[node] += (nodeRight-nodeLeft + 1) * dif;
        if (nodeLeft != nodeRight) {
            lazy[node * 2] += dif;
            lazy[node * 2 + 1] += dif;
        }
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update(node * 2, l, r, nodeLeft, mid, dif);
    update(node * 2 + 1, l, r, mid + 1, nodeRight, dif);
    s[node] = merge(s[node * 2], s[node * 2 + 1]);
}
ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //s should be vll
    propagation(node, nodeLeft, nodeRight);
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) {
        return s[node];
    }
    int mid = (nodeLeft+nodeRight)/2;
    return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2+1, l, r, mid+1, nodeRight));
}

*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//This is persistent segment tree (PST)

/*
struct Node {
    Node *l, *r;
    ll v;

    Node() {
        l = r = NULL;
        v = 0;
    }  
};

#define MAX 1000
//When using MAX, root MAX and arr MAX is DIFFERENT!!!! KEEP IN MIND!!! 
Node* root[MAX];
int arr[MAX];

void build(Node *node, int nodeLeft, int nodeRight) {
    if(nodeLeft == nodeRight) {
        node->v = arr[nodeLeft];
        return;
    }
    int m = nodeLeft + (nodeRight-nodeLeft)/2;

    node->l = new Node();
    node->r = new Node();
   
    build(node->l, nodeLeft, m);
    build(node->r, m+1, nodeRight);

    node->v = node->l->v + node->r->v;
}

//doesn't update origin segment tree but updates new segment tree and connects it into a existing tree
void update(Node* prev, Node* now, int nodeLeft, int nodeRight, int idx, int value) { 
    if(nodeLeft == nodeRight) {
        now->v = value;
        return;
    }

    int middle = nodeLeft + (nodeRight-nodeLeft)/2;

    if(idx <= middle) { //update left node
        now->l = new Node(); now->r = prev->r;
        update(prev->l, now->l, nodeLeft, middle, idx, value);
    }
    else { //update right node
        now->l = prev->l; now->r = new Node();
        update(prev->r, now->r, middle+1, nodeRight, idx, value);
    }
    now->v = now->l->v + now->r->v;
}

ll query(Node *node, int nodeLeft, int nodeRight, int l, int r) { //want to know the addition of l~r
    if(nodeRight < l || r < nodeLeft) return 0;
    if(l <= nodeLeft && nodeRight <= r) return node->v;

    int middle = nodeLeft + (nodeRight-nodeLeft)/2;

    return query(node->l, nodeLeft, middle, l, r) + query(node->r, middle+1, nodeRight, l, r);
}

*/

/* could help if above update isn't appliable
Node* update(Node* now, int nodeLeft, int nodeRight, int idx, int value) {
    if (nodeRight < idx || idx < nodeLeft) return now;
    
    if (nodeLeft == nodeRight) {
        Node* leaf = new Node();
        leaf->v = now->v + value;
        return leaf;
    }

    int middle = nodeLeft + (nodeRight - nodeLeft) / 2;
    Node* leaf = new Node();
    leaf -> l = update(now->l, nodeLeft, middle, idx, value);
    leaf -> r = update(now->r, middle + 1, nodeRight, idx, value);


    leaf->v = leaf->l->v + leaf->r->v;
    return leaf;
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*

//THIS IS FENWICK_TREE
//Fenwic_tree starts from index 1. 
#define MAX 500001
int arr[MAX];
int fenwick[MAX];

//update function reflects the change of arr value, not the absolute value
//if arr value, say arr[3] changes into 3 to 5, then update(3,2) should be used.
//update(idx, c-arr[idx]); arr[idx] = c;
void update(int idx, int Value) { //For Making Fenwick Tree, for(int i=1~N) Update(i, arr[i]);
    while (idx <= N) {
        fenwick[idx] = fenwick[idx] + Value;
        idx = idx + (idx & -idx);
    }
}

int sum(int idx) { //IF 3~5 sum is required it should be sum(5)-sum(2);
    int result = 0; //BE CAREFUL ON RANGE (Long Long could be used)
    while (idx > 0) {
        result += fenwick[idx];
        idx = idx - (idx & -idx);
    }
    return result;
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
int id, SN; //mark sn[i]
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
// This is Dijkstra, Time Complexity O((V+E)logV)
/*
#define MAX 100001
vpii edge[MAX]; // first is idx, second is weight of edge
int d[MAX];
struct cmp { //pii
    bool operator() (const pii& i, const pii& j) {
        return i.second > j.second;
    }
};
void Dijkstra(int num) {
    p_q<pii, vpii, cmp> pq;
    pq.push({ num, 0 });
    fill(d + 1, d + 1 + N, INF); //INF could be larger, varying from problem to problem
    d[num] = 0;
    while (!pq.empty()) {
        auto [cur, dis] = pq.top();
        pq.pop();
        if(d[cur]<dis) continue;
        for (auto next : edge[cur]) {
            if(d[next.first] > d[cur] + next.second) {
                d[next.first] = d[cur]+next.second;
                pq.push({next.first, d[next.first]});
            }
        }
    }
    for(int i = 1; i <= N; i++) {
        cout << d[i] << " ";
    }
    cout << endl;
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
    fill(d+1, d+1+N, INF);
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
int dp[MAX][MAX]; //input should be done in dp table
void floyd_warshall() {
    rep(i, 1, N) {
        rep(j, 1, N) if (dp[i][j] == 0) dp[i][j] = INF;
    }
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

// This is Union Find, DSU
/*
#define MAX 10001
int parent[MAX]; //parent[MAX] should be 1, 2, 3...
int getParent(int num) {
    if (parent[num] == num) return num;
    // int p = getParent(parent[num]);
    // dist[num] += dist[parent[num]];
    return parent[num] = getParent(parent[num]);
}
void merge(int a, int b) {
    int pa = getParent(a);
    int pb = getParent(b);

    // if(pa==pb) return;
    // dist[pb] = w + dist[pa];
    // dist[pb] = pa;
    if (pa < pb) parent[pb] = pa;
    else parent[pa] = pb;
}

bool isSameParent(int a, int b) {
    return getParent(a) == getParent(b);
}
//This is Kruskal with union find
//When using Kruskal vector Edge is a little bit different
class Edge {
public:
    int node[2];
    int dis;
    Edge(int a, int b, int _dis) {
        node[0] = a;
        node[1] = b;
        dis = _dis;
    }
    bool operator < (const Edge& edge) { 
        return dis > edge.dis; //watch out for inequality sign
    }
};
vector<Edge> edge;
void Kruskal() { //MST
    cin >> N >> M; //N is node, M is edge, Node starts from 1 to N
    for (int i = 0; i < M; i++) {
        int s, e, dis;
        cin >> s >> e >> dis;
        edge.push_back(Edge(s, e, dis));
    }
    sort(all(edge));
    for (int i = 1; i <= N; i++) { //setting nodes
        parent[i] = i;
    }
    int sum = 0;
    for (int i = 0; i < edge.size() ; i++) {
        int nodeA = edge[i].node[0];
        int nodeB = edge[i].node[1];
        int dis = edge[i].dis;
        if (!isSameParent(nodeA, nodeB)) {
            merge(nodeA, nodeB);
            sum+=dis;
        }
    }
    cout << "total distance required for executing kruskal is : " << sum << endl;
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
            int flow = dfs(src, INF); //INF varies from range to range
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
     
        int flow = INF;
     
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
        fill(dist, dist+MAX, INF);

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

        int flow = INF;
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
//rotate matrix by 90 degrees

/*
void rotate() { //rotating N*N matrix by 90 degrees clockwise
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            temp_arr[i][j] = arr[N - j -1][i]; //N-j+1 if 1~N
        }
    }
    memmove(arr, temp_arr, sizeof(arr));
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
//extended euclidian
// to find modular inverse
// Find modular inverse of a in MOD N
// if gcd(a,N)!=1, then modular inverse does not exist
// s*a + t*N = 1
// s is the modular inverse
ll exEuclid(ll a, ll b, ll &s, ll &t) { //s*a + t*b = gcd(a,b)
	if (b == 0) {
		s = 1; t = 0;
		return a;
	}
	ll gcd = exEuclid(b, a%b, s, t);
	ll temp = t;
	t = s - (a / b)*t;
	s = temp;

	if (s <= 0) {
		s += b;
		t -= a;
	}
	return gcd;
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
/* 	Articulation Points
#define MAX 10001
vi edge[MAX];
int visited[MAX] {};
int num=1;
bool isCut[MAX] {};
//for 1~N, if visited[i]==0, dfs(i,1);
int dfs(int cur, bool isRoot) {
    visited[cur] = num;
    num++;
    int ret = visited[cur];

    int child = 0;
    for(auto next : edge[cur]) {
        if(visited[next]) {
            ret = min(ret, visited[next]);
            continue;
        }
        child++;
        int prev = dfs(next, 0);

        if(isRoot==0 && prev>=visited[cur]) isCut[cur] = 1;
        
        ret = min(ret, prev);
    }
    if(isRoot && child>=2) isCut[cur] = 1;
    return ret;
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/* 	Articulation Bridges
#define MAX 100001
int visited[MAX] {};
vi edge[MAX];
vpii isCut;
int num = 1;
//for 1~N if visited[i]==0, dfs(i,-1)
int dfs(int cur, int parent) {
    visited[cur] = num;
    num++;
    int ret = visited[cur];

    for(auto next : edge[cur]) {
        if(next==parent) continue;

        if(visited[next]!=0) {
            ret = min(ret, visited[next]);
            continue;
        }

        int prev = dfs(next, cur);

        if(prev>visited[cur]) {
            isCut.pbk({min(next, cur), max(next, cur)});
        }
        ret = min(ret, prev);
    }
    return ret;
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
int A[MAX] {};
int B[MAX] {};
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
			dist[i]=INF;
		}
	}

	while(!q.empty()) {
		int cur = q.front();
		q.pop();

		for(auto next : edge[cur]) {
			if(B[next]!=-1 && dist[B[next]]==INF) {
				dist[B[next]] = dist[cur] + 1;
				q.push(B[next]);
			}
		}
	}
}

bool dfs(int cur) {
	for(auto next : edge[cur]) {
		if(B[next]==-1 || (dist[B[next]] == dist[cur]+1 && dfs(B[next]))) {
			used[cur] = 1;
			A[cur] = next;
			B[next] = cur;
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
#define MAX 1001
vi edge[MAX];
bool done[MAX] {};
int B[MAX] {};
//for 1~N memset(done, done+MAX, 0), if(dfs(i)) cnt++;
bool dfs(int cur) {
    for(auto next : edge[cur]) {
        if(done[next]) continue;
        done[next] = 1;
        
        if(B[next]==0 || dfs(B[next])) {
            B[next] = cur;
            return true;
        }
    }
    return false;
}
*/
const int mod = 1000000007;
using lint = long long;
lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		lint t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, lint n){
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	lint ret = 0;
	for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}
int guess_nth_term(vector<int> x, lint n){
	if(n < x.size()) return x[n];
	vector<int> v = berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v, x, n);
}
struct elem{int x, y, v;}; // A_(x, y) <- v, 0-based. no duplicate please..
vector<int> get_min_poly(int n, vector<elem> M){
	// smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
	vector<int> rnd1, rnd2;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub){
		return uniform_int_distribution<int>(lb, ub)(rng);
	};
	for(int i=0; i<n; i++){
		rnd1.push_back(randint(1, mod - 1));
		rnd2.push_back(randint(1, mod - 1));
	}
	vector<int> gobs;
	for(int i=0; i<2*n+2; i++){
		int tmp = 0;
		for(int j=0; j<n; j++){
			tmp += 1ll * rnd2[j] * rnd1[j] % mod;
			if(tmp >= mod) tmp -= mod;
		}
		gobs.push_back(tmp);
		vector<int> nxt(n);
		for(auto &i : M){
			nxt[i.x] += 1ll * i.v * rnd1[i.y] % mod;
			if(nxt[i.x] >= mod) nxt[i.x] -= mod;
		}
		rnd1 = nxt;
	}
	auto sol = berlekamp_massey(gobs);
	reverse(sol.begin(), sol.end());
	return sol;
}
lint det(int n, vector<elem> M){
	vector<int> rnd;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub){
		return uniform_int_distribution<int>(lb, ub)(rng);
	};
	for(int i=0; i<n; i++) rnd.push_back(randint(1, mod - 1));
	for(auto &i : M){
		i.v = 1ll * i.v * rnd[i.y] % mod;
	}
	auto sol = get_min_poly(n, M)[0];
	if(n % 2 == 0) sol = mod - sol;
	for(auto &i : rnd) sol = 1ll * sol * ipow(i, mod - 2) % mod;
	return sol;
}
ll dp[55][6666] {};
void Solve() {
    cin >> K >> N;
    vll v;
    rep(i,0,K) {
        rep(j,1,5555) {
            if(i==0) dp[i][j] = j;
            else dp[i][j] = dp[i-1][j] + dp[i][j-1];
            dp[i][j] %= mod;
        }
    }
    rep(i,0,555) v.pbk(dp[K][i]);
    cout << guess_nth_term(v, N);
}
int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}