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
#define MAX 66666
ll v[255555], s[4*MAX];
void update(int node, int idx, int nodeLeft, int nodeRight, ll dif) {
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s[node] += dif;
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update(node * 2, idx, nodeLeft, mid, dif);
    update(node * 2 + 1, idx, mid + 1, nodeRight, dif);

    s[node] = s[node * 2] + s[node * 2 + 1];
}
ll query(int node, int idx, int nodeLeft, int nodeRight) { //l and r is the range.
    // cout << nodeLeft << " " << nodeRight << " " << idx << endl;
    if (nodeLeft==nodeRight) return nodeLeft;
	int mid = (nodeLeft+nodeRight)/2;
    if(s[node*2]>=idx) return query(node*2, idx, nodeLeft, mid);
    else return query(node*2+1, idx-s[node*2], mid+1, nodeRight);
}
void Solve() {
    cin >> N >> K;
    rep(i,1,N) cin >> v[i];
    rep(i,1,K) {
        update(1, v[i], 0, 65535, 1);
    }
    ll sum = 0;
    sum += query(1, (K+1)/2, 0, 65535);
    for(int i=K+1;i<=N;i++) {
        update(1,v[i], 0, 65535, 1);
        update(1,v[i-K], 0, 65535, -1);
        sum += query(1, (K+1)/2, 0, 65535);
    }
    cout << sum;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}