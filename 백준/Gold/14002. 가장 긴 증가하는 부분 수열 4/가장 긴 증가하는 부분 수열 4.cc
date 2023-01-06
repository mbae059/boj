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
using tiii = tuple<int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
int T, N, K, M, S, H, W;

void LIS(vi& v) { //vector v's size is N
    vi dp(N);
    fill(all(dp), 1);
    rep(i,1,N-1) { // N
        rep(j,0,i-1) {
            if(v[j] <v[i]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
    }
    stack<int> s;
    int sz = *max_element(all(dp));
    cout << sz << endl;
    for(int i=N-1;i>=0;i--) {
        if(sz==dp[i]) {
            s.push(v[i]);
            sz--;
        }
    }
    while(!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}

void Solve() {
    cin >> N;
    vi v(N);
    rep(i,0,N-1) cin >> v[i];
    LIS(v);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
}