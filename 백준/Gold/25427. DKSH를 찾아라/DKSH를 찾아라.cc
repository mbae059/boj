#include <bits/stdc++.h>
#define rep(i, a, b) for (int i=a; i<=b; i++) 

using namespace std;
int N;
void Solve() {
    cin >> N;
    string str; cin >> str;
    str = '0' + str;
    vector<vector<int>> dp(5, vector<int>(N+1));

    rep(i,1,N) {
        char c = str[i];
        rep(j,1,4) {
            dp[j][i] = dp[j][i-1];
        }
        if(c=='D') {
            dp[1][i]++;
        }
        else if(c=='K') {
            dp[2][i] += dp[1][i];
        }
        else if(c=='S') {
            dp[3][i] += dp[2][i];
        }
        else if(c=='H') {
            dp[4][i] += dp[3][i];
        }
    }
    cout << dp[4][N];
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}