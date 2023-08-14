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
    return modular(a+b, mod);
}

ll modMul(ll a, ll b, ll mod) {
    return modular(a*b, mod);
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
struct Matrix {
    vvi m;
    int l;
    ll mod;
    Matrix(int l=10) : l(l) {
        m = vvi(l+1, vi(l+1));
        mod = 1e9+7;
    }
 
    void setEye() {
        for(int i=1;i<=l;i++) m[i][i]=1;
    }

    Matrix operator * (const Matrix& other) const {
        Matrix ret;
        for(int i=1;i<=l;i++) {
            for(int j=1;j<=l;j++) {
                for(int k=1;k<=l;k++) {
                    ret.m[i][j] += m[i][k] * other.m[k][j] % mod;
                    ret.m[i][j]%=mod;
                }
            }
        }
        return ret;
    }

    Matrix operator + (const Matrix& other) const {
        Matrix ret;
        for(int i=1;i<=l;i++) {
            for(int j=1;j<=l;j++) {
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
    void rotate90CC() {
        vvi after(l+1, vi(l+1));
        for(int i=1;i<=l;i++) {
            for(int j=1;j<=l;j++) { 
                after[i][j] = m[j][l-i+1];
            }
        }
        for(int i=1;i<=l;i++) {
            for(int j=1;j<=l;j++) {
                m[i][j] = after[i][j];
            }
        }
    }
    void transpose() {
        vvi after(l+1, vi(l+1));
        for(int i=1;i<=l;i++) {
            for(int j=1;j<=l;j++) {
                after[i][j] = m[j][i];
            }
        }
        for(int i=1;i<=l;i++) {
            for(int j=1;j<=l;j++) {
                m[i][j] = after[i][j];
            }
        }
    }
    void print(int N, int M) {
        for(int i=1;i<=N;i++) {
            for(int j=1;j<=M;j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
struct Segtree {
    vi a;
    vi s;
    int n;
    Segtree(int n) : n(n) {
        a.resize(n+1);
        s.resize(4*n+1);
    }
    int merge(int a, int b) {
        return a+b;
    }
    int segment(int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight) {
            return s[node] = a[nodeLeft];
        }
        int mid = (nodeLeft+nodeRight)/2;
        return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
    }
    void update(int node, int nodeLeft, int nodeRight, int idx, int num) {
        if (idx < nodeLeft || nodeRight < idx) return;
        if (nodeLeft == nodeRight) {
            s[node] = num;
            return;
        }
        int mid = (nodeLeft+nodeRight)/2;
        update(node * 2, idx, nodeLeft, mid, num);
        update(node * 2 + 1, idx, mid + 1, nodeRight, num);

        s[node] = merge(s[node * 2], s[node * 2 + 1]);
    }
    int query(int node, int l, int r, int nodeLeft, int nodeRight) {
        if(nodeRight<l || r<nodeLeft) return 0;
        if(l<=nodeLeft && nodeRight<=r) return s[node];
        int mid = nodeLeft+nodeRight>>1;
        return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
    }
    void print(int node, int nodeLeft, int nodeRight) {
        cout << nodeLeft << " " << nodeRight << " : " << s[node] << endl;
        if(nodeLeft==nodeRight) return;

        int mid = (nodeLeft + nodeRight) >> 1;
        print(node*2, nodeLeft, mid);
        print(node*2+1, mid+1, nodeRight);
    }
};

struct lazySegtree {
    vi a;
    vi s;
    vi lazy;
    int n;
    lazySegtree(int n) : n(n) {
        a.resize(n+1);
        s.resize(4*n+1);
        lazy.resize(4*n+1);
    }

    int merge(int a, int b) {
        return a+b;
    }
    int segment(int node, int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
        if (nodeLeft == nodeRight) {
            return s[node] = a[nodeLeft];
        }
        int mid = (nodeLeft+nodeRight)/2;
        return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
    }
    void propagation(int node, int l, int r) {
        if (lazy[node]) {
            s[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void update(int node, int l, int r, int nodeLeft, int nodeRight, int dif) { //This is for lazy propagation
        propagation(node, nodeLeft, nodeRight);
        if (nodeRight < l || r < nodeLeft) return;
        if (l <= nodeLeft && nodeRight <= r) {
            s[node] += (nodeRight-nodeLeft + 1) * dif;
            if (nodeLeft != nodeRight) {
                lazy[node * 2] += dif;
                lazy[node * 2 + 1] += dif;
            }
            return;
        }
        int mid = (nodeLeft+nodeRight)/2;
        update(node * 2, l, r, nodeLeft, mid, dif);
        update(node * 2 + 1, l, r, mid + 1, nodeRight, dif);
        s[node] = merge(s[node * 2], s[node * 2 + 1]);
    }
    ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //s should be vll
        propagation(node, nodeLeft, nodeRight);
        if (nodeRight < l || r < nodeLeft) return 0;
        if (l <= nodeLeft && nodeRight <= r) {
            return s[node];
        }
        int mid = (nodeLeft+nodeRight)/2;
        return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2+1, l, r, mid+1, nodeRight));
    }
};

struct DSU {
    vi parent;
    vi depth; //tree depth (maximum distance from root node)
    vi d;
    vi sz;
    DSU(int n=1) {
        parent = vi(n+1);
        depth = vi(n+1, 0);
        d = vi(n+1, 0);
        sz = vi(n+1, 0);
        iota(parent.begin()+1, parent.end(),1);
        fill(sz.begin()+1, sz.end(), 1);
    }
    int getParent(int num) { 
        if(num==parent[num]) return num;
        int p = getParent(parent[num]);
        // d[num] += d[parent[num]];
        return parent[num] = p;
    }
    
    //modify merge to get difference between a and b
    void merge(int a, int b, ll w=0) { 
        a = getParent(a);
        b = getParent(b);
        if(depth[a]<depth[b]) swap(a,b);
        if(depth[a]==depth[b]) depth[a]+=1;
        parent[b] = a;
        sz[a] += sz[b];
    }
};

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
vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
 
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}
vector<int> combination;
Matrix m;
bool visited[1005];
int answer=-1e9;
void dfs(int idx, int cnt) { //implement with dfs(1, 0). N and K must be global variable
	if(cnt==K) {
        int sum =0;
        for(int i=0;i<combination.size();i++) {
            for(int j=i+1;j<combination.size();j++) {
                int a= combination[i];
                int b= combination[j];

                sum += m.m[a][b];
            }
        }
        answer = max(answer,sum);
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

void Solve() {
    cin >> N >> K;
    m = Matrix(N);
    rep(i,1,N) {
        rep(j,1,N) {
            cin >> m.m[i][j];
        }
    }
    dfs(1,0);
    cout << answer;
}
int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}