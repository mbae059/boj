#include <bits/stdc++.h>
#define endl '\n'
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()   
using namespace std;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef long long ll;
int T, N, K, M, S; 

vpii v;
#define MAX 300003
int dp[MAX] {};
int limit[MAX] {};
void Solve() {
    cin >> N >> S;

    rep(i, 1, N) {
        int H, C; cin >> H >> C;

        v.pbk({H,C});
    }
    v.pbk({0,0});
    sort(all(v));

    rep(i, 1, N) {
        for(limit[i] = limit[i-1];limit[i] < i;limit[i]++) {
            if(v[i].first - v[limit[i]].first < S) {
                break;
            }
        }
        limit[i]--;

        dp[i] = max(dp[i-1], dp[limit[i]] + v.at(i).second);
        // cout << dp[i] << " ";
    }
    cout << dp[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
}