#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pb push_back
#define FOR(i, n) for(int i=0;i<(n);++i)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<vi> vii;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef map<int, int> mii;
typedef set<int> si;
int T, N, K, M;
//ofstream out("temp.txt");

void print(int a, int b) {
	cout << a << " " << b << endl;
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



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


/* THIS IS SEGMENT TREE AND LAZY PROPOGATION
int segment(int node, int nodeLeft, int nodeRight) { // use when s, v is available and segment tree is about sum
	if (nodeLeft == nodeRight) {
		return s[node] = v[nodeLeft];
	}

	int mid = nodeLeft + (nodeRight - nodeLeft) / 2;

	return s[node] = segment(node * 2, nodeLeft, mid) + segment(node * 2 + 1, mid + 1, nodeRight);
}

int update(int node, int idx, int nodeLeft, int nodeRight, int dif) { //Before this you have to do v[idx]+=dif;
	if (idx < nodeLeft || nodeRight < idx) return 0;

	if (nodeLeft == nodeRight) return s[node] += dif;

	int mid = nodeLeft + (nodeRight - nodeLeft) / 2;

	return s[node] = update(node * 2, idx, nodeLeft, mid, dif) + update(node * 2 + 1, idx, mid + 1, nodeRight, dif);
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
// THIS IS TARJAN ALGORITHM FOR SCC

/*
#define MAX 10001
vii SCC;
int d[MAX];
bool finished[MAX];
vi edge[MAX];
int id, SN; //mark sn[i]
stack<int> s;
int sn[MAX]; //sn[i] is SCC number to which it belongs to
int dfs(int x) {
	d[x] = ++id;
	s.push(x);
	int parent = d[x];
	for (auto i : edge[x]) {
		if (d[i] == 0) {
			parent = min(parent, dfs(i));
		}
		else if (finished[i] == 0) {
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
		SCC.push_back(scc);
	}
	return parent;
}

int oppo(int num) { //This is for 2-sat
	return num % 2 ? num + 1 : num - 1;
}

void sat2() {
	cin >> N >> M; // N is # of node, M is # of conditions

	for (int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;

		A = A > 0 ? 2 * A - 1 : -2 * A; //positive num goes 1->1, 2->3, 3->5, 4->7, 5->9... and so on
		B = B > 0 ? 2 * B - 1 : -2 * B; //negative num goes -1->2, -2->4, -3->6, -4->8... and so on

		edge[oppo(A)].push_back(B);
		edge[oppo(B)].push_back(A);
	}

	for (int i = 1; i <= 2 * N; i++) {
		if (d[i] == 0) dfs(i);
	}

	for (int i = 1; i <= N; i++) {
		if (sn[2 * i-1] == sn[2 * i]) {
			cout << "contradiction!" << " " << sn[i] << endl;
		}
	}
}

*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// This is Dijkstra
/*
#define MAX 1000
vpii edge[MAX]; // first is idx, second is weight of edge
bool visited[MAX];
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
		pq.pop();

		for (auto next : edge[cur]) {
			if (visited[next.first]) continue;
			visited[next.first] = 1;
			d[next.first] = d[cur] + next.second;
			pq.push(next);
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

	cin >> N;
	string str;
	while (cin >> str) {
		for (int i = 0; i < str.size() / 2; i++) {
			int a = str.at(2 * i)-'a';
			int b = str.at(2 * i+1)-'a';

			int c = a + b - N;
			
			if (c < 0) {
				c += 26;
			}
			else c %= 26;

			cout << (char)(c + 'a');
		}
		cout << " ";
	}
}