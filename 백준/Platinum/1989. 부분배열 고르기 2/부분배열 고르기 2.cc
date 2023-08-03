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
int A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z;
int dy[8] = {1,-1,0,0,1,1,-1,-1};
int dx[8] = {0,0,1,-1,1,-1,1,-1};
//vvi matrix(N, vector<int>(N));
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define MAX 100001
ll a[MAX], s[4*MAX];

tlll answer ={1,1,0};

void print(tlll x) {
    auto [a,b,c] = x;
    cout << c << endl;
    cout << a << " " << b << endl;
}
void setAnswer(ll l, ll r, ll val) {
    auto [a,b,c] = answer;
    if(c<val) answer = {l,r,val};
}
void segment(ll nodeLeft, ll nodeRight) {
    if (nodeLeft == nodeRight) {
        setAnswer(nodeLeft, nodeRight, a[nodeLeft] * a[nodeLeft]);
        return;
    }
	ll mid = (nodeLeft+nodeRight)/2;

    segment(nodeLeft,mid);
    segment(mid+1,nodeRight);

    ll l = mid;
    ll r = mid+1;

    ll h = min(a[l],a[r]);
    ll sum = a[l] + a[r];
    setAnswer(l, r, sum*h);
    while(nodeLeft+1<=l && r+1 <= nodeRight) {
        ll lval = (sum + a[l-1]) * min(h, a[l-1]);
        ll rval = (sum + a[r+1]) * min(h, a[r+1]);

        if(lval<rval) {
            r++;
            sum += a[r];
            h = min(h, a[r]);
            setAnswer(l,r,rval);
        }
        else {
            l--;
            sum += a[l];
            h = min(h, a[l]);
            setAnswer(l,r,lval);
        }

    }

    while(nodeLeft+1<=l) {
        l--;
        sum += a[l];
        h = min(h, a[l]);
        ll lval = sum * h;

        setAnswer(l, r, lval);
    }
    while(r+1<=nodeRight) {
        r++;
        sum += a[r];
        h = min(h, a[r]);
        ll rval = sum*h;
        setAnswer(l,r,rval);
    }
}

void Solve() {
    cin >> N;
    rep(i,1,N) cin >> a[i];
    segment(1,N);
    print(answer);
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}