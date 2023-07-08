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

int T, N, K, S, H, W, Q; // S is for MCMF, network flow
int dy[8] = {1,-1,0,0,1,1,-1,-1};
int dx[8] = {0,0,1,-1,1,-1,1,-1};
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
#define MAX 75001
ll a[MAX], s[4*MAX];
ll M = 75000;
ll merge(ll a, ll b) { //for operation of the segment tree
    return a+b;
}
ll segment(int node, int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return s[node] = a[nodeLeft];
    }
	int mid = (nodeLeft+nodeRight)/2;
    return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
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
ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s[node];
	int mid = (nodeLeft+nodeRight)/2;
    return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
}

void Solve() {
    cin >> N;
    vpll v;
    vll val1;
    vll val2;
    segment(1, 1, M);
    rep(i,1,N) {
        ll a, b; cin >> a >> b;
        v.pbk({a,b});
        val1.pbk(a);
        val2.pbk(b);
    }

    sort(all(val1));
    sort(all(val2));
    val1.erase(unique(all(val1)), val1.end());
    val2.erase(unique(all(val2)), val2.end());

    for(auto& p : v) {
        auto& [a, b] = p;
        a = lower_bound(all(val1), a) - val1.begin() + 1;
        b = lower_bound(all(val2), b) - val2.begin() + 1;
    }

    sort(all(v), [&](pll a, pll b) {
        if(a.second==b.second) return a.first > b.first;
        return a.second < b.second;
    });

    ll cnt = 0;
    rep(i,0,N-1) {
        cnt += query(1, v[i].first, M, 1, M);
        update(1, v[i].first, 1, M, 1);
    }
    cout << cnt << endl;
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--) Solve();
}