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
vi edge[51];
double w[51] {};
int inDegree[51] {};
double answer = 0;
void dfs(int cur) {
    for(auto next : edge[cur]) {
        w[next] += w[cur]/edge[cur].size();
        inDegree[next]--;
        if(inDegree[next]==0) dfs(next);
    }
}
void Solve() {
    cin >> N >> M;
    rep(i,1,M) {
        int a, b; cin >> a >> b;
        edge[a].pbk(b);
        inDegree[b]++;
    }
    w[1] = 100;
	vi v;
	rep(i,1,N) {
		if(inDegree[i]==0) v.pbk(i);
	}
	for(auto i : v) dfs(i);
    rep(i,1,N) {
        if(edge[i].empty()) answer = max(answer, w[i]);
    }
    cout << fixed << setprecision(6) << answer;
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}