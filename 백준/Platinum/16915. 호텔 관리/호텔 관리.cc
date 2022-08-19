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

// THIS IS TARJAN ALGORITHM FOR SCC
#define MAX 200001
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
		SCC.push_back(scc); //SCC의 SN번째 그래프랑 대응된다
	}
	return parent;
}

int oppo(int num) { //This is for 2-sat
	return num % 2 ? num + 1 : num - 1;
}

bool open[MAX];
vi sw[MAX];
void sat2() { // (x1 or x2) and (Nx1 or x3) //Nx1->x2, Nx2->x1. x1->x3, Nx3->Nx1
	cin >> N >> M; // N is # of node, M is # of conditions
    for(int i=1;i<=N;i++) cin >> open[i];
    for(int i=1;i<=M;i++) {
        cin >> K;
        while(K--) {
            int room; cin >> room;
            sw[room].pbk(i);
        }
    }

    for(int i=1;i<=N;i++) {
		int A = sw[i].at(0);
		int B = sw[i].at(1);
        
        A = A > 0 ? 2 * A - 1 : -2 * A; //positive num goes 1->1, 2->3, 3->5, 4->7, 5->9... and so on
		B = B > 0 ? 2 * B - 1 : -2 * B; //negative num goes -1->2, -2->4, -3->6, -4->8... and so on
		
        if(open[i]) { 
            edge[A].pbk(B);
            edge[oppo(B)].pbk(oppo(A));
            edge[B].pbk(A);
            edge[oppo(A)].pbk(oppo(B));
        }
        else {
            edge[A].pbk(oppo(B));
            edge[B].pbk(oppo(A));
            edge[oppo(A)].pbk(B);
            edge[oppo(B)].pbk(A);
        }
	}
	for (int i = 1; i <= 2 * M; i++) { //node is 1~2*N
		if (d[i] == 0) dfs(i);
	}
	for (int i = 1; i <= M; i++) {
		if (sn[2 * i-1] == sn[2 * i]) {
			cout << 0;
            return;
		}
	}
    cout << 1;
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	sat2();
}