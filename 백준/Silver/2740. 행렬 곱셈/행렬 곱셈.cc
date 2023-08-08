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
//matrix a is N*K, matrix b is K*M. row and column starts from 0. Modular operation could be applied
vector<vector<ll>> matrixMul(const vector<vector<ll>>& a, const vector<vector<ll>>& b, ll n, ll k, ll m) {
    vector<vector<ll>> ret(n, vector<ll>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            for(int x=0;x<k;x++) {
                ret[i][j] += a[i][x] * b[x][j];
            }
        }
    }
    return ret;
}

void print(vector<vector<ll>> a) {
    for(auto v : a) {
        for(auto i : v) cout << i << " ";
        cout << endl;
    }
}
void Solve() {
    cin >> N >> M;
    vector<vector<ll>> a(N, vll(M));
    rep(i,0,N-1) {
        rep(j,0,M-1) cin >> a[i][j];
    }
    cin >> M >> K;
    vector<vector<ll>> b(M, vll(K));
    rep(i,0,M-1) {
        rep(j,0,K-1) cin >> b[i][j];
    }

    auto answer = matrixMul(a,b,N,M,K);
    for(auto v : answer) {
        for(auto i : v) cout << i << " ";
        cout << endl;
    }
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}