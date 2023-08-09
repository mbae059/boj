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
#define MAX 2
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
const int mod = 1e9+7;
void Solve() {
    cin >> N;

    Matrix m = Matrix();
    m.m[0][0] = 1;
    m.m[0][1] = 1;
    m.m[1][0] = 1;

    auto x = m.power(N);
    cout << x.m[0][0] * x.m[0][1] % mod;

}
int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}