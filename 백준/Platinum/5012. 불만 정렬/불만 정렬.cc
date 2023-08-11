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
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii> ;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using qpii = queue<pii>;
using tiii = tuple<int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
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

ll modAdd(ll a, ll b, ll mod) {
    return (a+b)%mod;
}

ll modMul(ll a, ll b, ll mod) {
    return a*b%mod;
}

ll modExp(ll a, ll b, ll mod) {
    ll ret = 1;
    while(b) {
        if(b&1) ret = modMul(ret, a, mod);
        a = modMul(a,a,mod);
        b>>=1;
    }
    return ret;
}
/*
#define MAX 20
struct Matrix {
    array<array<ll, MAX>, MAX> m;
    ll mod;
    Matrix() {
        for(int i=0;i<MAX;i++) {
            for(int j=0;j<MAX;j++) {
                m[i][j] = 0;
            }
        }
        mod = 1e9+7;
    }

    void setEye() {
        for(int i=0;i<MAX;i++) m[i][i]=1;
    }

    Matrix operator * (const Matrix& other) const {
        Matrix ret;
        for(int i=0;i<MAX;i++) {
            for(int j=0;j<MAX;j++) {
                for(int k=0;k<MAX;k++) {
                    ret.m[i][j] += m[i][k] * other.m[k][j] % mod;
                    ret.m[i][j]%=mod;
                }
            }
        }
        return ret;
    }

    Matrix operator + (const Matrix& other) const {
        Matrix ret;
        for(int i=0;i<MAX;i++) {
            for(int j=0;j<MAX;j++) {
                ret.m[i][j] = m[i][j] + other.m[i][j];
            }
        }
        return ret;
    }
    Matrix power(ll k) { //matrix = matrix.power(k);
        Matrix ret;
        if(k==0) {
            ret.setEye();
            return ret;
        }
        if(k==1) {
            return *this;
        }

        ret = power(k/2);
        ret = ret * ret;
        if(k&1) ret = ret * (*this);
        return ret;
    }
    void rotate90C() {
        array<array<ll, MAX>, MAX> after;
        for(int i=0;i<MAX;i++) {
            for(int j=0;j<MAX;j++) { 
                after[i][j] = m[MAX-j-1][i];
            }
        }
        m = after;
    }
    void print(int N, int M) {
        for(int i=0;i<N;i++) {
            for(int j=0;j<M;j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
*/
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

// This is segment tree
#define MAX 100001
ll a[MAX], s1[4*MAX], s2[4*MAX];

ll merge(ll a, ll b) { //for operation of the segment tree
    return a+b;
}
void update1(int node, int idx, int nodeLeft, int nodeRight) {
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s1[node]+=1;
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update1(node * 2, idx, nodeLeft, mid);
    update1(node * 2 + 1, idx, mid + 1, nodeRight);

    s1[node] = merge(s1[node * 2], s1[node * 2 + 1]);
}
ll query1(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s1[node];
	int mid = (nodeLeft+nodeRight)/2;
    return merge(query1(node * 2, l, r, nodeLeft, mid), query1(node * 2 + 1, l, r, mid + 1, nodeRight));
}
void update2(int node, int idx, int nodeLeft, int nodeRight, ll dif) {
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s2[node] += dif;
        return;
    }
    int mid = (nodeLeft+nodeRight)/2;
    update2(node * 2, idx, nodeLeft, mid, dif);
    update2(node * 2 + 1, idx, mid + 1, nodeRight, dif);

    s2[node] = merge(s2[node * 2], s2[node * 2 + 1]);
}
ll query2(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s2[node];
	int mid = (nodeLeft+nodeRight)/2;
    return merge(query2(node * 2, l, r, nodeLeft, mid), query2(node * 2 + 1, l, r, mid + 1, nodeRight));
}

void Solve() {
    cin >> N;
    rep(i,1,N) {
        cin >> a[i];
    }

    rep(i,1,N) {
        update2(1,a[i],1,N,1);
    }
    int answer=0;

    rep(i,1,N) {
        if(!(a[i]==N || a[i]==1)) answer += query1(1,a[i]+1, N,1,N) * query2(1,1,a[i]-1,1,N);
        update1(1,a[i],1,N);
        update2(1,a[i],1,N,-1);
    }
    cout << answer;
}
int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}