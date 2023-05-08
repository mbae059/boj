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
/* Basic Info
A-Z is 26 char
<regex> header file is used for find patterns
*/

/* FOR COUNTING INVERSION, MERGE SORT VERSION
void merge(vector<int>& arr, int l, int mid, int r, int& ic) {
    vector<int> left, right;
    for (int i = l; i <= mid; i++) left.pbk(arr[i]);
    for (int i = mid + 1; i <= r; i++) right.pbk(arr[i]);
    int i = 0; int j = 0;
    int n1 = left.size();
    int n2 = right.size();
    int k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = (left[i++]);
        }
        else {
            arr[k++] = (right[j++]);
            ic += (n1 - i);
        }
    }
    while (i < n1) {
        arr[k++] = (left[i++]);
    }
    while (j < n2) {
        arr[k++] = (right[j++]);
    }
}
void mergesort(vector<int>& arr, int l, int r, int& ic) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergesort(arr, l, mid, ic);
    mergesort(arr, mid + 1, r, ic);
    merge(arr, l, mid, r, ic);
}
int find_inversion_count(vector<int>& arr) {
    int n = arr.size();
    int ic = 0;
    mergesort(arr, 0, n - 1, ic);
    return ic;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


// THIS IS SEGMENT TREE AND LAZY PROPOGATION
/*

#define MAX 10000
int v[MAX], s[4*MAX]; //v starts from 0, s starts from 1.
//nodeLeft and nodeRight always has to be 0 and N-1 as it is used in binary searching
int segment(int node, int nodeLeft, int nodeRight) { // use when s, v is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return s[node] = v[nodeLeft];
    }
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    return s[node] = segment(node * 2, nodeLeft, mid) + segment(node * 2 + 1, mid + 1, nodeRight);
}
void update(int node, int idx, int nodeLeft, int nodeRight, int dif) { //Before this you have to do v[idx]+=dif;
    if (idx < nodeLeft || nodeRight < idx) return;
    s[node] += dif;
    if (nodeLeft == nodeRight) return;
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    update(node * 2, idx, nodeLeft, mid, dif);
    update(node * 2 + 1, idx, mid + 1, nodeRight, dif);
}
int query(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s[node];
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    return query(node * 2, l, r, nodeLeft, mid) + query(node * 2 + 1, l, r, mid + 1, nodeRight);
}

//This is lazy propogation. Beginning starts with segment(..) used in above

void propogation(int node, int l, int r) {
    if (lazy[node]) {
        s[node] += (r - l + 1) * lazy[node];
        if (l != r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}
void update(int node, int l, int r, int nodeLeft, int nodeRight, int dif) { //This is for lazy propogation
    propogation(node, nodeLeft, nodeRight);
    if (nodeRight < l || r < nodeLeft) return;
    if (l <= nodeLeft && nodeRight <= r) {
        s[node] += (r - l + 1) * dif;
        if (nodeLeft != nodeRight) {
            lazy[node * 2] += dif;
            lazy[node * 2 + 1] += dif;
        }
        lazy[node] = 0;
    }
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    update(node * 2, l, r, nodeLeft, mid, dif);
    update(node * 2 + 1, l, r, mid + 1, nodeRight, dif);
    s[node] = s[node * 2] + s[node * 2 + 1];
}
ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //s should be vll
    propogation(node, nodeLeft, nodeRight);
    if (nodeRight < l || r < nodeLeft) return;
    if (l <= nodeLeft && nodeRight <= r) {
        return s[node];
    }
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    return query(node * 2, l, r, nodeLeft, mid)+query(node * 2+1, l, r, mid+1, nodeRight);
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
#define MAX 1000
int arr[MAX];
int fenwick[MAX];

void Update(int idx, int Value) { //For Making Fenwick Tree, for(int i=1~N) Update(i, arr[i]);
    while (idx < fenwick.size()) {
        fenwick[idx] = fenwick[idx] + Value;
        idx = idx + (idx & -idx);
    }
}
void Update(int x, int y, int v) { //For Making Fenwick Tree, for(int i=1~N) Update(i, arr[i]);
    while(x<N+1) {
        int tempy = y;
        while(tempy<N+1) {
            fenwick[x][tempy] += v;
            tempy += (tempy & -tempy);
        }
        x += (x & -x);
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
// This is Dijkstra
/*
#define MAX 1000
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
        int cur = pq.top().first;
        int dis = pq.top().second;
        pq.pop();
        if(d[cur] < dis) continue; //could be used if d[cur] has been updated more than once.
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

//This is Bellman_Ford

/*
#define MAX 20001
vpii edge[MAX];
int d[MAX];
void bellman_ford(int start) {
    fill(d + 1, d + 1 + N, INF); //Beware of INF
    bool cycle = 0;
    d[start]=0;
    rep(i, 1, N) {
        rep(j, 1, N) {
            for (auto next : edge[j]) {
                if (d[j]!=INF && d[next.first] > d[j] + next.second) { //d[j]!=INF -> in case d[j]+next.second is overflow
                    d[next.first] = d[j] + next.second;
                    if (i == N) cycle = 1;
                }
            }
        }
    }
    if (cycle) {
        cout << "CYCLE: " << endl;
    }
}
*/

///////////////////////////
///////////////////////////
//This is SPFA 

/*
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
#define MAX 10001
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

// This is Union Find
/*
#define MAX 10001
int parent[MAX]; //parent[MAX] should be 1, 2, 3...
int getParent(int num) {
    if (parent[num] == num) return num;
    return parent[num] = getParent(parent[num]);
}
void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a < b) parent[b] = a;
    else parent[a] = b;
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
        return dis < edge.dis;
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
            unionParent(nodeA, nodeB);
            sum+=dis;
        }
    }
    cout << "total distance required for executing kruskal is : " << sum << endl;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//This is Network Flow with Dinic Algorithm. Time Complexity O(V^2 * E)
//If the question is about Bipartite Matching, you should use Hopcroft-Karp Algorithm. Time Complexity O(E * sqrt(V))

/*
#define MAX 100 //MAX should be treated carefully since space complexity is limited. (256mb, 512mb)
vector<int> edge[MAX];
int f[MAX][MAX], c[MAX][MAX];
int level[MAX], work[MAX];
int start, target;
int bias;
void addEdge(int s, int e, int value=1) { //Decide whether graph is directed graph or undirected graph
    edge[s].pbk(e);
    edge[e].pbk(s);
    c[s][e] = value;
}
bool bfs() { // to create level and decide flow is no longer needed
    queue<int> q;
    q.push(start); //
    memset(level, -1, sizeof(level));
    level[start] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto next : edge[now]) {
            if (level[next] == -1 && c[now][next] - f[now][next] > 0) {
                q.push(next);
                level[next] = level[now] + 1;
            }
        }
    }
    if (level[target] == -1) return false;
    else return true;
}
int maxFlow(int now, int flow) { // dfs for dinic
    if (now == target) return flow;
    for (int& i = work[now]; i < edge[now].size(); i++) {
        int next = edge[now][i];
        if (level[next] == level[now] + 1 && c[now][next] - f[now][next] > 0) {
            int ret = maxFlow(next, min(flow, c[now][next] - f[now][next]));
            if (ret > 0) {
                f[now][next] += ret;
                f[next][now] -= ret;
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
            int flow = maxFlow(start, INF); //INF varies from range to range
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
struct Line {
    pll p1, p2;
};
int CCW(pll A, pll B, pll C) { //A, B, C is in order
    ll ccw = (B.first - A.first) * (C.second - A.second) - (C.first - A.first) * (B.second - A.second); //Cross product
    if(ccw>0) return 1;
    else if(ccw<0) return -1;
    else return 0;
}
//
int LineInterSection(Line l1, Line l2) { 
	ll l1_l2 = CCW(l1.p1, l1.p2, l2.p1) * CCW(l1.p1, l1.p2, l2.p2);
    ll l2_l1 = CCW(l2.p1, l2.p2, l1.p1) * CCW(l2.p1, l2.p2, l1.p2);
	
	if(l1_l2==0 && l2_l1==0) { //l1 and l2 is on the same line. If p1 <= p4 && p3 <= p2, the line meets.
		if(l1.p1 > l1.p2) swap(l1.p1, l1.p2);
		if(l2.p1 > l2.p2) swap(l2.p1, l2.p2);

		return l1.p1 <= l2.p2 && l2.p1 <= l1.p2;
	}
    return (l1_l2 <= 0) && (l2_l1 <= 0);
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/* This is bitmasking
void show(int& num) { // shows num in binary
    for(int i=32;i>0;i--) {
       cout << (num & (1 << i-1));
    }
}

void init(int& num) { //num becomes 000000....
    num =0;
}

void full(int& num) { // num becomes 11111111....
    num = -1;
}

void drop(int& num, int i) { // deletes i th information. Be careful in using i
    num &= ~(1<<i);
}

void set(int& num, int i) { // sets i th information to true
    num |= (1<<i);
}

bool isSet(int& num, int i) {
    return num & (1<<i);
}

void toggle(int& num, int i) {
    num ^= (1<<i);
}

*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// This is LCA with binary algorithm (O(logN))

/*
#define MAX 100001
vi adj[MAX];
int parent[MAX][18]; //18 is log2(MAX)
int level[MAX];
int maxLevel;

//maps node and depth and set 2^i parent
void set_tree(int node, int pnode) {
    level[node] = level[pnode]+1;
    parent[node][0] = pnode;
 
    for(int i=1;i<=maxLevel;i++) {
        parent[node][i] = parent[parent[node][i-1]][i-1];
    }
 
    for(int i=0;i<adj[node].size();i++) {
        int child = adj[node][i];
        if(child==pnode) continue;
        set_tree(child, node);
    }
}

void init() {
    cin >> N; //Has N node and N-1 edges
    for(int i=0;i<N-1;i++) {
        int a, b;
        cin >> a >> b;
        adj[a].pbk(b);
        adj[b].pbk(a);
    }
    maxLevel = (int)floor(log2(MAX));
}

int LCA(int a, int b) {
    if(a==1 || b==1) return 1;

    int target = a, compare = b;
    if(level[a] < level[b]) swap(target, compare); //target is deeper

    if(level[target]!=level[compare]) {
        for(int i=maxLevel;i>=0;i--) {
            if(level[parent[target][i]] >= level[compare]) {
                target = parent[target][i];
            }
        }
    }

    int ret = target;

    if(target!=compare) {
        for(int i=maxLevel;i>=0;i--) {
            if(parent[target][i]!=parent[compare][i]) {
                target = parent[target][i];
                compare = parent[compare][i];
            }
            ret = parent[target][i];
        }
    }
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
/*
//KMP
vi makeTable(const string& pattern) {
    int patternSize = pattern.size();

    vi table(patternSize);

    int j = 0;
    for(int i=1;i<patternSize;i++) {
        while(j>0 && pattern[i] != pattern[j]) {
            j = table[j-1];
        }

        if(pattern[i]==pattern[j]) {
            j+=1;
            table[i] = j;
        }
    }
    return table;
}

void KMP(const string& parent, const string& pattern) {
    vi table = makeTable(pattern);

    int parentSize = parent.size();
    int patternSize = pattern.size();

    int j =0;

    for(int i=0;i<parentSize;i++) {
        while(j>0 && parent[i] != pattern[j]) {
            j = table[j-1];
        }
        if(parent[i] == pattern[j]) {
            if(j == patternSize-1) {
                cout << i-patternSize + 2 << endl; //index starts from 1
                j = table[j];
            }
            else {
                j++;
            }
        }
    }
}

*/

/*
*
*
*
*
*
*
*
*
*
*
*
*
*
*/
#define MAX 1003
char matrix[MAX][MAX] {};
bool visited[MAX][MAX] {};
int df[MAX][MAX] {};
int dj[MAX][MAX] {};
pii J;
vpii F;

void print() {
    rep(i,1,N) {
        rep(j,1,M) {
            cout << dj[i][j] << " ";
        }
        cout << endl;
    }
}
void Solve() {
    cin >> N >> M;
    rep(i,1,N) {
        rep(j,1,M) {
            cin >> matrix[i][j];
            if(matrix[i][j]=='J') J = {i,j};
            if(matrix[i][j]=='F') F.pbk({i,j});
        }
    }
    
    queue<pii> q;
    for(auto p : F) {
        q.push(p);
        visited[p.first][p.second] = 1;
        df[p.first][p.second] = 1;
    }

    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        rep(i,0,3) {
            int nexty = y + dir[i][0];
            int nextx = x + dir[i][1];
            if(!inRange(nexty, nextx)) continue;
            if(visited[nexty][nextx]) continue;
            if(matrix[nexty][nextx]=='#') continue;

            q.push({nexty, nextx});
            visited[nexty][nextx] = 1;
            df[nexty][nextx] = df[y][x] + 1;
        }
    }

    memset(visited, 0, sizeof(visited));

    q.push(J);
    visited[J.first][J.second] = 1;
    dj[J.first][J.second] = 1;
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        rep(i,0,3) {
            int nexty = y + dir[i][0];
            int nextx = x + dir[i][1];
            if(!inRange(nexty, nextx)) {
                cout << dj[y][x];
                return;
            }
            if(visited[nexty][nextx]) continue;
            if(matrix[nexty][nextx]=='#') continue;
            if(dj[y][x]+1 >= df[nexty][nextx] && df[nexty][nextx]) continue;
            q.push({nexty, nextx});
            visited[nexty][nextx] = 1;
            dj[nexty][nextx] = dj[y][x] + 1;
        }
    }
    cout << "IMPOSSIBLE";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}