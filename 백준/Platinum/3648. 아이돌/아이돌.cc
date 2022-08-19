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

int T, N, K, M;

#define MAX 4401 
vii SCC;
int d[MAX];
bool finished[MAX];
vi edge[MAX];
int id, SN; //mark sn[i]
stack<int> s;
int sn[MAX];

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

int result[MAX] {}; //For finding value of each clause (x1, x2, x3)
pii p[MAX];
void sat2() { // (x1 or x2) and (Nx1 or x3) //Nx1->x2, Nx2->x1. x1->x3, Nx3->Nx1
    id=0, SN=0;
    SCC.clear();
    for(int i=0;i<MAX;i++) edge[i].clear();
    memset(d, 0, sizeof(d));
    memset(finished, 0, sizeof(finished));
    memset(sn, 0, sizeof(sn));
    memset(p, 0, sizeof(p));
	for (int i = 0; i < M; i++) {
		int A, B; //If num is negative #, then it is (not) positive num
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
			cout << "no" << endl;
            return;
		}
	}
	
	//For finding out value of each clause

	memset(result, -1, sizeof(result));
    
	for(int i=1;i<=2*N;i++) {
		p[i] = {sn[i], i};
	}
	sort(p+1, p+2*N+1);

	for(int i=2*N;i>0;i--) { //Start from the beginning of DAG 
		int node = p[i].second;
		int src = (node+1)/2;
		
		if(result[src] == -1) result[src] = node%2 ? 0 : 1; 
	}

    if(result[1]) cout << "yes";
    else cout << "no";
    cout << endl;
	
}
void Solve() {
    while(cin >> N >> M) {
        sat2();
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Solve();
}