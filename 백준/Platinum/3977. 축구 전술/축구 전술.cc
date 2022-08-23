#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define FOR(i, n) for(int i=0;i<(n);++i)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef map<int, int> mii;
typedef set<int> si;
typedef queue<int> qi;

int T, N, K, M;
//ofstream out("temp.txt");

void print(int a, int b) {
	cout << a << " " << b << endl;
}

void print(const string& str) {
	cout << str << endl;
}
void print(pii a) {
	cout << a.first << " " << a.second << endl;
}

void print(int a) {
	cout << a << endl;
}

void print(vi& v) {
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

/* Basic Info
A-Z is 26 char
<regex> header file is used for find patterns
*/

/* FOR COUNTING INVERSION, MERGE SORT VERSION
void merge(vector<int>& arr, int l, int mid, int r, int& ic) {
	vector<int> left, right;
	for (int i = l; i <= mid; i++) left.pb(arr[i]);
	for (int i = mid + 1; i <= r; i++) right.pb(arr[i]);
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
int v[MAX], s[4*MAX];
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
int query(int node, int l, int r, int nodeLeft, int nodeRight) {
	if (nodeRight < l || r < nodeLeft) return 0;
	if (l <= nodeLeft && nodeRight <= r) return s[node];
	int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
	return query(node * 2, l, r, nodeLeft, mid) + query(node * 2 + 1, l, r, mid + 1, nodeRight);
}
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

/* THIS IS FENWICK_TREE

#define MAX 1000
int Arr[MAX];
vi Fenwick_Tree(MAX);

void Update(int Idx, int Value) { //For Making Fenwick Tree, for(int i=1~N) Update(i, Arr[i]);
	while (Idx < Fenwick_Tree.size()) {
		Fenwick_Tree[Idx] = Fenwick_Tree[idx] + Value;
		Idx = Idx + (Idx & -Idx);
	}
}
int sum(int idx) { //IF 3~5 sum is required it should be sum(5)-sum(2);
	int result = 0; //BE CAREFUL ON RANGE (Long Long could be used)
	while (idx > 0) {
		result += Fenwick_Tree[idx];
		idx = idx - (idx & -idx);
	}
	return result;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// THIS IS TARJAN ALGORITHM FOR SCC

#define MAX 100001 //when used in 2-sat, you have to double node because not only x1~x100 is required but also Nx1~Nx100
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
void Solve() {
    cin >> N >> M;
    id=0, SN=0;
    memset(d, 0, sizeof(d));
    memset(finished, 0, sizeof(finished));
    memset(sn, 0, sizeof(sn));
    memset(inDegree, 0, sizeof(inDegree));
    SCC.clear();
    for(int i=0;i<MAX;i++) edge[i].clear();


    for(int i=0;i<M;i++) {
        int a, b;
        cin >> a >> b;
        edge[a+1].pbk(b+1);
    }

    for(int i=1;i<=N;i++) {
        if(d[i]==0) dfs(i);
        //cout << "SN : " << sn[i] << endl;
    }

    SCCtopology_sort();

    int SCCstart=-1;

    for(int i=0;i<SN;i++) {
        if(inDegree[i]==0) {
            if(SCCstart==-1) SCCstart = i;
            else {
                cout << "Confused" << endl << endl;
                return;
            }
        }
    }
    sort(SCC[SCCstart].begin(), SCC[SCCstart].end());
    for(auto i : SCC[SCCstart]) cout << i-1 << endl;
    cout << endl;
}
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
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
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

// This is Floyd-Warshall
/*
#define MAX 10000
int dp[MAX][MAX]; //input should be done in dp table
void floyd_warshall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) if (dp[i][j] == 0) dp[i][j] = INF;
	}
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
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
	else parent[b] = a;
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
	bool operator < (Edge& edge) {
		return dis < edge.dis;
	}
};
vector<Edge> edge;
void Kruskal() {
	cin >> N >> M; //N is node, M is edge, Node starts from 1 to N
	for (int i = 0; i < M; i++) {
		int s, e, dis;
		cin >> s >> e >> dis;
		edge.push_back(Edge(s, e, dis));
	}
	sort(edge.begin(), edge.end());
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
void addEdge(int s, int e, int value=1) {
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

// This is CCW
/*
struct Point {
	int x, y;
};
struct Line {
	Point p1, p2;
};
int CCW(Point A, Point B, Point C) { //A, B, C is in order
	int ccw = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y); //Cross product
	if(ccw>0) return 1;
	else if(ccw<0) return -1;
	else return 0;
}
//
int LineInterSection(Line l1, Line l2) { //If l1, l2 is on the same line, then this isn't the one to use
	int l1_l2 = CCW(l1.p1, l1.p2, l2.p1) * CCW(l1.p1, l1.p2, l2.p2);
	int l2_l1 = CCW(l2.p1, l2.p2, l1.p1) * CCW(l2.p1, l2.p2, l1.p2);
	int ret = (l1_l2 <= 0) && (l2_l1 <= 0);
	return ret;
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

/* This is LCA with binary algorithm (O(logN))

#define MAX 100001
vi adj[MAX];
int parent[MAX][18]; //18 is log2(MAX)
int level[MAX];
int maxLevel;

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
	cin >> N;
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
	if(level[a] < level[b]) swap(target, compare);

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin >> T;
    while(T--) {
        Solve();
    }
}