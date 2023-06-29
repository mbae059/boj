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
int dir[8][2] = {{1,0},{-1,0}, {0,1}, {0,-1}, {1,1},{1,-1},{-1,1},{-1,-1}};
//ofstream out("temp.txt");
//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;
//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())
// unordered_map<char,int> dx = {{'D',0},{'L',-1},{'R',1},{'U',0}};
// unordered_map<char,int> dy = {{'D',1},{'L',0},{'R',0},{'U',-1}}
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
vector<int> combination;
bool visited[33];
vll v;
int C;
void dfs(int idx, int cnt, ll sum, vll& m) { //implement with dfs(1, 0). N and K must be global variable
	if(cnt==K) {
		return;
	}
	for(int i=idx;i<v.size();i++) { //idx, N을 잘볼것
		if(visited[i]==1) continue;
		
		visited[i]=1;
		m.pbk(sum + v[i]);
		dfs(i+1, cnt+1, sum+v[i], m); //be careful with i+1, cnt+1
		visited[i]=0;
	}
}
ll arr[33] {};
vll l, r;
void Solve() {
	cin >> N >> C;
	rep(i,1,N) {
		cin >> arr[i];
	}

	rep(i,1,N/2) v.pbk(arr[i]);
	K = v.size();
	dfs(0, 0, 0, l);

	v.clear();

	rep(i,N/2+1,N) v.pbk(arr[i]);
	K = v.size();
	dfs(0, 0, 0, r);

	ll answer = 0;
	l.pbk(0);
	r.pbk(0);

	sort(all(l));
	sort(all(r));

	for(auto i : l) {
		auto iter = upper_bound(all(r), C-i);
		answer += iter - r.begin();
	}
	cout << answer;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}