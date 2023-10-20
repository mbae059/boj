#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using tiii = tuple<int,int,int>;
using si = set<int>;
using pii = pair<int,int>;
using vvi = vector<vector<int>>;
using ll = long long;

ll N, K, ans;
const int mod = 1e9+7;

void Solve() {
    cin >> N >> K;

    ll dp[N + 5];
    int a[N+5], b[N+5];

    for(int i=1;i<=N;i++) cin >> a[i];

    dp[0] = 0;
    for (int i = 1; i <= N; ++i) {
        dp[i] = (dp[i - 1] * 2 + 1) % mod;
    }

    b[N] = K; 

    for (int i = N; i > 0; --i) {
        if (a[i] != b[i]) {
            set<int> tmp = {1,2,3};
            tmp.erase(a[i]);
            tmp.erase(b[i]);
            b[i-1] = *tmp.begin();
        } else {
            b[i - 1] = b[i];
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (a[i] != b[i]) {
            //cout << i << '\t';
            ans += dp[i - 1] + 1;
            ans %= mod;
        }
    }

    cout << ans;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solve();
}