#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
ll T, N, K, M, S, H, W, Q; // S is for MCMF, network flow

// This is segment tree
#define MAX 200001
#define MOD 1000000007
pll a[MAX], s[4*MAX];

pll merge(pll a, pll b) { //for operation of the segment tree
    return {(a.first+b.first)%MOD, (a.second+b.second)%MOD};
}
void update(ll node, ll idx, ll nodeLeft, ll nodeRight, ll dif) {
    if (idx < nodeLeft || nodeRight < idx) return;
    if (nodeLeft == nodeRight) {
        s[node].first = (s[node].first + dif)%MOD;
        s[node].second = (nodeLeft * s[node].first) % MOD;
        return;
    }
    ll mid = (nodeLeft+nodeRight)/2;
    update(node * 2, idx, nodeLeft, mid, dif);
    update(node * 2 + 1, idx, mid + 1, nodeRight, dif);

    s[node] = merge(s[node * 2], s[node * 2 + 1]);
}
pll query(ll node, ll l, ll r, ll nodeLeft, ll nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return {0,0};
    if (l <= nodeLeft && nodeRight <= r) return s[node];
	ll mid = (nodeLeft+nodeRight)/2;
    return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
}

ll makePositive(ll num) {
    num%= MOD;
    return num < 0 ? num+MOD : num;
}
void Solve() {
    cin >> N;
    M = 199999;
    ll answer = 1;
    for(ll i=1;i<=N;i++) {
        ll x; cin >> x;
        auto l = query(1,0,x-1,0,M);
        auto r = query(1,x+1,M,0,M);
        
        if(i>=2) answer = answer * makePositive(x*l.first%MOD-l.second + r.second - x*r.first%MOD) % MOD;
        update(1, x, 0, M, 1);
    }
    assert(answer>=0);
    cout << answer;
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}