#include <bits/stdc++.h>
#define rep(i, a, b) for (int i=a; i<=b; i++) 

using ll = long long;
#define int ll
using namespace std;
int N;
int dp[5][100001] {};
void Solve() {
    cin >> N;
    string str; cin >> str;
    str = '0' + str;

    rep(j,1,N) {
        char c = str[j];
        rep(i,1,4) {
            dp[i][j] = dp[i][j-1];
        }
        if(c=='D') dp[1][j]++;
        else if(c=='K') dp[2][j] += dp[1][j];
        else if(c=='S') dp[3][j] += dp[2][j];
        else if(c=='H') dp[4][j] += dp[3][j];
    }
    cout << dp[4][N];
}
int32_t main() {
    Solve();
}