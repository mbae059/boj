#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()
using namespace std;
using ll = long long;
#define int ll
using pii = pair<int, int>;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii> ;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using qpii = queue<pii>;
using tiii = tuple<int, int, int> ; //get<0>(t);
using tiiii = tuple<int, int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
using vtiiii = vector<tiiii>;
using spii = set<pii>;
using qtiii = queue<tiii>;
int A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z;
int dy[8] = {1,-1,0,0,1,1,-1,-1};
int dx[8] = {0,0,1,-1,1,-1,1,-1};
//for tenary search
//mid1 = (2*l + r)/3;
//mid2 = (l + 2*r)/3;

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
#define MAX 100005
ll a[MAX], s[4*MAX];

ll merge(ll a, ll b) { //for operation of the segment tree
    return a+b;
}
ll segment(int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return a[nodeLeft];
    }
	int mid = (nodeLeft+nodeRight)/2;
    int lv = segment(nodeLeft, mid);
    int rv = segment(mid + 1, nodeRight);

    int l = mid;
    int r = mid+1;

    int h = min(a[l], a[r]);
    ll ret = max({lv, rv, 2*h});
    while(nodeLeft+1<=l && r+1<=nodeRight) {
        if(a[l-1]<a[r+1]) {
            r++;
        }
        else {
            l--;
        }
        h = min({h, a[l], a[r]});
        ret = max(ret, (r-l+1) * h);
    }
    while(nodeLeft+1<=l) {
        l--;
        h = min(h, a[l]);
        ret = max(ret, (r-l+1) * h);
    }
    while(r+1<=nodeRight) {
        r++;
        h = min(h, a[r]);
        ret = max(ret, (r-l+1) * h);
    }
    return ret;
}

void Solve() {
    while(true) {
        cin >> N;
        if(N==0) return;
        rep(i,1,N) cin >> a[i];
        cout << segment(1,N) << endl;
    }
}
int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}