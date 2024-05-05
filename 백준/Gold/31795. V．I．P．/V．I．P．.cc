#include <bits/stdc++.h>
#define endl '\n'
using ll = long long;
#define int ll
using namespace std;
using vi = vector<int>;
using vvi = vector<vector<int>>;

int N, M, Q;
const int mod = 1e9+7;

void Solve() {
    cin >> N >> M >> Q;
    
    vi w(N+1);
    for(int i=1;i<=N;i++) cin >> w[i];

    vvi edge(N+1);
    vvi redge(N+1);
    vi inDegree(N+1);
    vi rinDegree(N+1);
    vi tinDegree(N+1);
    set<pair<int,int>> s;
    
    for(int i=1;i<=M;i++) {
        int a, b; cin >> a >> b;
        if(w[a]==w[b]) continue;
        if(w[a]>w[b]) swap(a,b);
        edge[a].push_back(b);
        redge[b].push_back(a);
        inDegree[b]++;
        rinDegree[a]++;
        s.insert({a,b});
    }

    vi dp1(N+1);
    vi dp2(N+1);
    fill(dp1.begin()+1, dp1.end(), 1);
    fill(dp2.begin()+1, dp2.end(), 1);

    auto dfs1 = [&](auto&& self, int cur) -> void {
        for(auto next : edge[cur]) {
            tinDegree[next]++;
            dp1[next] += dp1[cur];
            dp1[next] %= mod;
            if(tinDegree[next]==inDegree[next]) self(self, next);
        }
    };
    auto dfs2 = [&](auto&& self, int cur) -> void {
        for(auto next : redge[cur]) {
            tinDegree[next]++;
            dp2[next] += dp2[cur];
            dp2[next] %= mod;
            if(tinDegree[next]==rinDegree[next]) self(self, next);
        }
    };
    for(int i=1;i<=N;i++) {
        if(inDegree[i]) continue;
        dfs1(dfs1, i);
    }

    fill(tinDegree.begin(), tinDegree.end(), 0);

    for(int i=1;i<=N;i++) {
        if(rinDegree[i]) continue;
        dfs2(dfs2, i);
    }

    int answer=0;
    for(int i=1;i<=N;i++) {
        answer += dp1[i];
        answer %= mod;
    }

    while(Q--) {
        int a, b; cin >> a >> b;

        if(w[a]==w[b]) {
            cout << answer << endl;
            continue;
        }
        
        if(w[a]>w[b]) swap(a,b);

        if(s.contains({a,b})) cout << (answer - dp1[a] * dp2[b] % mod + mod)%mod << endl;
        else cout << (answer + dp1[a] * dp2[b]) % mod << endl;
    }

}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}
