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
int T, N, K, M;


int P,S;
#define MAX 500001
vii SCC;
int d[MAX];
bool finished[MAX];
vi edge[MAX];

int id=0, SN=0; //mark sn[i]
stack<int> s;
int sn[MAX]{}; //sn[i] is SCC number to which it belongs to. SN은 SCC number 라고 생각해주세요
int cash[MAX]{};
bool restaurant[MAX]{};
ll topologyCash[MAX]{};//각 SCC를 큰 정점으로 생각하고 그 정점의 돈을 다 합한 것들의 배열
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
        int sum=0;
		while (true) {
			int t = s.top();
			s.pop();
			scc.push_back(t);
			finished[t] = 1;
			sn[t] = SN;
            sum+=cash[t]; //여기서 SCC안에 있는 현금을 합함
			d[t] = x; 
			if (t == x) break;
		}
        topologyCash[SN]=sum; 
		SN++;
		SCC.push_back(scc);
	}
	return parent;
}

ll SNcash[MAX] {};
vi SNedge[MAX];
int inDegree[MAX]{};

void DfsCash(int x) { //x is scc number
	for(auto next : SNedge[x]) {
		SNcash[next] = max(SNcash[next], topologyCash[next] + SNcash[x]);
		inDegree[next]--;
		if(inDegree[next]==0) DfsCash(next);
	}
}

void Solve() {
    cin >> N >> M;
    while(M--) {
        int a, b;
        cin >> a >> b;
        edge[a].pbk(b);
    }
    for(int i=1;i<=N;i++) cin >> cash[i];

    for(int i=1;i<=N;i++) {
        if(d[i]==0) dfs(i);
    }

    cin >> S >> P;
    while(P--) {
        int r; cin >> r;
        restaurant[sn[r]]=1;
    }
	
	for(int i=1;i<=N;i++) { //generate SCC graph (topology)
		for(auto next : edge[i]) {
			if(sn[next]!=sn[i]) {
				SNedge[sn[i]].pbk(sn[next]);
				inDegree[sn[next]]+=1;
			}
		}
	}

	SNcash[sn[S]] = topologyCash[sn[S]]; 
	
	
	/* My version
	DfsCash(sn[S]);
	*/
///////////////////////////////////////// 
	queue<int> q;
	bool flag=false;
	for(int i=0;i<SN;i++) {
		if(inDegree[i]==0) q.push(i);
	}

	while(!q.empty()) {
		int cur = q.front();
		q.pop();

		if(cur == sn[S]) {
			flag=true;
		}
		for(auto next : SNedge[cur]) {
			if(flag) SNcash[next] = max(SNcash[next], SNcash[cur] + topologyCash[next]);
			inDegree[next]--;
			if(inDegree[next]==0) q.push(next);
		}
		
	}
	ll M=-1;

    for(int i=0;i<SN;i++) {
        if(restaurant[i]) M = max(M, SNcash[i]);
    }
    cout << M;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Solve();
}