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
typedef vector<vi> vii;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef map<int, int> mii;
typedef set<int> si;
typedef queue<int> qi;

int T, N, K, M,S;
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

#define MAX 10001
vii SCC;
int d[MAX]; //This
bool finished[MAX];
vi edge[MAX];
int id, SN; //mark sn[i]
stack<int> s;
int sn[MAX]; //sn[i] is SCC number to which it belongs to
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
		SCC.push_back(scc); 
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

int SCCsum[MAX] {};
void SCCbfs(int x) {
    qi q;
    q.push(x);
    SCCsum[x] = SCC[x].size();
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(auto next : SCCedge[cur]) {
            if(SCCsum[next] < SCCsum[cur] + SCC[next].size()) {
                SCCsum[next] = SCCsum[cur] + SCC[next].size();
                q.push(next);
            }
        }
    }
}

void Solve() {
    cin >> N >> M >> S >> T;
    while(M--) {
        int a, b;
        cin >> a >> b;
        edge[a].pbk(b);
    }
    for(int i=1;i<=N;i++) {
        if(d[i]==0) dfs(i);
    }
    SCCtopology_sort();
    SCCbfs(sn[S]);
    cout << SCCsum[sn[T]];
}
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

	Solve();
}