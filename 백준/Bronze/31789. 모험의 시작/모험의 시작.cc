#include <bits/stdc++.h>

using namespace std;

int N, X, S;
void Solve() {
    cin >> N;
    cin >> X >> S;
    for(int i=1;i<=N;i++) {
        int c, p; cin >> c >> p;
        if(c<=X && S<p) {
            cout << "YES";
            return;
        }
    }
    cout << "NO";
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}