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
bool flag = 0;
vi x;
vi y;

vi answer;
vector<int> combination;
bool visited[1005];

int operate(int x) {
    stack<int> s;
    s.push(x);
    for(auto i : combination) {
        if(i==3) {
            s.push(s.top());
        }
        else {
            if(s.size()<2) return INF;
            int a = s.top();
            s.pop();
            int b = s.top();
            s.pop();
            if(i==1) {
                s.push(a+b);
            }
            if(i==2) {
                if(a==0) return INF;
                s.push(b/a);
            }
            if(i==4) {
                s.push(a*b);
            }
            if(i==5) {
                s.push(b-a);
            }
        }
        if(abs(s.top())>30000) return INF;
    }
    return s.top();
}
bool chk() {
    for(int i=0;i<N;i++) {
        int val = x[i];
        val = operate(val);
        
        if(val!=y[i]) return false;
    }

    return true;
}
void dfs(int cnt, int dup) { //implement with dfs(1, 0). N and K must be global variable
    if(dup>5) return;
    if(flag==0 && 2*dup==combination.size() && chk()) {
        // if(combination.size()==4 && combination[0]==3 && combination[1]==3 && combination[2]==4 && combination[3]==5) cout << 123;
        answer = combination;
        flag = 1;
        return;
    }
	if(cnt==K) {
        return;
	}
	
	for(int i=1;i<=5;i++) { //idx, N을 잘볼것
		combination.push_back(i);
        if(i==3) dfs(cnt+1, dup+1);
        else dfs(cnt+1, dup);
        if(flag) return;
		combination.pop_back();
	}
}
void Solve() {
    for(int cnt=1;;cnt++) {
        cin >> N;
        if(N==0) break;
        answer.clear();
        answer = {9,9,9,9,9,9,9,9,9,9};
        combination.clear();
        flag = 0;
        x.resize(N);
        y.resize(N);

        rep(i,0,N-1) cin >> x[i];
        rep(i,0,N-1) cin >> y[i];

        rep(i,0,10) {
            K = i;
            dfs(0, 0);
            if(flag) break;
        }

        if(flag==0) {
            cout << "Program " << cnt << endl;
            cout << "Impossible" << endl << endl;
        }
        else if(answer.empty()) {
            cout << "Program " << cnt << endl;
            cout << "Empty sequence" << endl << endl;
        }
        else {
            cout << "Program " << cnt << endl;
            for(auto i : answer) {
                if(i==1) {
                    cout << "ADD ";
                }
                else if(i==2) {
                    cout << "DIV ";
                }
                else if(i==3) {
                    cout << "DUP ";
                }
                else if(i==4) {
                    cout << "MUL ";
                }
                else if(i==5) {
                    cout << "SUB ";
                }
            }
            cout << endl << endl;
        }
    }
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}