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
using tlll = tuple<ll, ll, ll> ; //get<0>(t);
using vtiii = vector<tiii>;
using vtlll = vector<tlll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using spii = set<pii>;
using qtiii = queue<tiii>;
int A,B,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z;
int dy[8] = {1,-1,0,0,1,1,-1,-1};
int dx[8] = {0,0,1,-1,1,-1,1,-1};
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
vector<int> combination;
int answer = INF;
int d[101] {};
int C[101] {};
vi edge[101];
int inDegree[101] {};
int outDegree[101] {};
pii p = {0,0};
si s;
void topology() {
	fill(d+1, d+1+N, -1);
	qi q;
	d[1] = C[1];
	q.push(1);

	int tempinDegree[101] {};
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(auto next : edge[cur]) {
			if(s.find(next)==s.end()) d[next] = max(d[next], d[cur]+C[next]);
			else d[next] = max(d[next], d[cur]);
			tempinDegree[next]++;
			if(inDegree[next]==tempinDegree[next]) {
				q.push(next);
			}
		}
	}
	answer = min(answer, *max_element(d+1, d+1+N));
}
void dfs(int idx, int cnt) { //implement with dfs(1, 0). N and K must be global variable
	if(cnt==K) {
		topology();
		return;
	}
	for(int i=idx;i<=N;i++) { //idx, N을 잘볼것
		if(p.second==i) continue;
		s.insert(i);
		dfs(i+1, cnt+1); //be careful with i+1, cnt+1
		s.erase(i);
	}
}

void Solve() {
	cin >> N >> M >> K;
	rep(i,1,N) cin >> C[i];

	rep(i,1,M) {
		int a, b; cin >> a >> b;
		edge[a].pbk(b);
		inDegree[b]++;
	}
	qi q;
	q.push(1);
	int tempinDegree[101] {};
	int td[101] {};
	td[1] = C[1];
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		if(p.first < td[cur]) {
			p = {td[cur], cur};
		}
		for(auto next : edge[cur]) {
			tempinDegree[next]++;
			td[next] = max(td[next], td[cur] + C[next]);
			if(tempinDegree[next]==inDegree[next]) {
				q.push(next);
			}
		}
	}
	dfs(2,0);

	cout << answer;
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}