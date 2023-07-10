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
int T, N, K, M, S, H, W, Q; // S is for MCMF, network flow
int dy[8] = {1,-1,0,0,1,1,-1,-1};
int dx[8] = {0,0,1,-1,1,-1,1,-1};
//int to string : to_string
//string to int : stoi
//ofstream out("temp.txt");
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


// This is segment tree
#define MAX 2000001
ll s[4*MAX] {};

ll merge(ll a, ll b) { //for operation of the segment tree
    return a+b;
}
void update(int node, int idx, int nodeLeft, int nodeRight, ll dif) {
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s[node] += dif;
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update(node * 2, idx, nodeLeft, mid, dif);
    update(node * 2 + 1, idx, mid + 1, nodeRight, dif);
    s[node] = merge(s[node * 2], s[node * 2 + 1]);
}
ll query(int node, int nodeLeft, int nodeRight, int idx) { //l and r is the range.
    if(nodeLeft==nodeRight) return nodeLeft;
	int mid = (nodeLeft+nodeRight)/2;
    if(s[node*2]>=idx) return query(node*2, nodeLeft, mid, idx);
    else return query(node*2+1, mid+1, nodeRight, idx-s[node*2]);
}
void print(int node, int nodeLeft, int nodeRight) {
    cout << nodeLeft << " " << nodeRight << " : " << s[node] << endl;
    if(nodeLeft==nodeRight) return;

    int mid = (nodeLeft + nodeRight) >> 1;
    print(node*2, nodeLeft, mid);
    print(node*2+1, mid+1, nodeRight);
}
void Solve() {
    cin >> Q;
    N = 2000000;
    while(Q--) {
        int op, x; cin >> op >> x;
        if(op==1) {
            update(1,x,1,N,1);
        }
        else {
            int val = query(1,1,N,x);
            cout << val << endl;
            update(1,val,1,N,-1) ;
        }
    }
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}