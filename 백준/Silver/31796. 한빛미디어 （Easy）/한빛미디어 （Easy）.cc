#include <bits/stdc++.h>

using namespace std;

void Solve() {
    int N; cin >> N;
    int a[N+1] {};
    for(int i=1;i<=N;i++) cin >> a[i];
    sort(a+1,a+1+N);

    int p = 0;
    int answer=0;
    for(int i=1;i<=N;i++) {
        if(p*2<=a[i]) {
            answer++;
            p = a[i];
        }
    }
    cout << answer;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}