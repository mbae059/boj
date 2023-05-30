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
int dir[4][2] = {{1,0},{-1,0}, {0,1}, {0,-1}};
//ofstream out("temp.txt");
//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;
//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())

//diagonal counting. l[y+x], r[y-x+N]
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


// THIS IS SEGMENT TREE AND LAZY PROPOGATION
/*

#define MAX 100001
ll v[MAX], s[4*MAX]; //v starts from 0, s starts from 1.
//nodeLeft and nodeRight always has to be 0 and N-1 as it is used in binary searching
ll segment(int node, int nodeLeft, int nodeRight) { // use when s, v is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return s[node] = v[nodeLeft];
    }
	int mid = (nodeLeft+nodeRight)/2;
    return s[node] = segment(node * 2, nodeLeft, mid) + segment(node * 2 + 1, mid + 1, nodeRight);
}
void update(int node, int idx, int nodeLeft, int nodeRight, ll num) { v[idx]=num;
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s[node] = num;
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update(node * 2, idx, nodeLeft, mid, num);
    update(node * 2 + 1, idx, mid + 1, nodeRight, num);

    s[node] = s[node * 2] + s[node * 2 + 1];
}
ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s[node];
	int mid = (nodeLeft+nodeRight)/2;
    return query(node * 2, l, r, nodeLeft, mid) + query(node * 2 + 1, l, r, mid + 1, nodeRight);
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
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
int ptoi(pii a) {
    return (a.first-1)*M+a.second;
}
// This is Union Find
#define MAX 2253333
int parent[MAX]; //parent[MAX] should be 1, 2, 3...
int getParent(int num) {
    if (parent[num] == num) return num;
    return parent[num] = getParent(parent[num]);
}
void unionParent(pii a, pii b) {
    int ap = getParent(ptoi(a));
    int bp = getParent(ptoi(b));
    if (ap < bp) parent[bp] = ap;
    else parent[ap] = bp;
}

bool isSameParent(pii a, pii b) {
    return getParent(ptoi(a)) == getParent(ptoi(b));
}
char matrix[1501][1501] {};
bool visited[1501][1501] {};
vpii L;

bool chk() {
    return isSameParent(L[0], L[1]);
}

bool isAdjacent(int y, int x) {
    rep(i,0,3) {
        int nexty = y+dir[i][0];
        int nextx = x+dir[i][1];
        if(matrix[nexty][nextx]=='.' || matrix[nexty][nextx]=='L') return true;
    }
    return false;
}

void print() {
    cout << endl;
    rep(i,1,N) {
        rep(j,1,M) {
            cout << matrix[i][j] << " " ;
        }
        cout << endl;
    }
}
void Solve() {
    cin >> N >> M;
    qpii q;
    rep(i,1,N) {
        rep(j,1,M) {
            cin >> matrix[i][j];
            if(matrix[i][j]=='L') L.pbk({i,j});
        }
    }
    rep(i,1,N*M) parent[i] = i;
    rep(i,1,N) {
        rep(j,1,M) {
            if(matrix[i][j]=='X' && isAdjacent(i,j)) {
                visited[i][j]= 1;
                q.push({i,j});
            }
            if((matrix[i][j]=='.' || matrix[i][j]=='L') && (matrix[i+1][j]=='.' || matrix[i+1][j]=='L')) {
                unionParent({i,j},{i+1,j});
            }
            if((matrix[i][j]=='.' || matrix[i][j]=='L') && (matrix[i][j+1]=='.' || matrix[i][j+1]=='L')) {
                unionParent({i,j},{i,j+1});
            }
        }
    }
    int answer = 1;
    while(true) {
        int sz = q.size();
        while(sz--) {
            int y = q.front().first;
            int x = q.front().second;
            matrix[y][x] = '.';
            q.pop();

            rep(i,0,3) {
                int nexty = y+dir[i][0];
                int nextx = x+dir[i][1];
                if(!inRange(nexty, nextx)) continue;
                char c = matrix[nexty][nextx];
                if(c=='.' || c=='L') {
                    unionParent({y,x}, {nexty,nextx});
                    continue;
                }
                if(visited[nexty][nextx]) continue;
                q.push({nexty, nextx});
                visited[nexty][nextx] = 1;
            }
        }
        
        if(chk()) {
            cout << answer;
            return;
        }
        answer++;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}