#include <bits/stdc++.h>
 
using namespace std;
void Solve() {
    int N, M; cin >> N >> M;

    deque<pair<int,int>> dq;
    for(int i=1;i<=M;i++) {
        int h1, h2; cin >> h1 >> h2;
        dq.push_back({h1,i});
        dq.push_back({h2,i});
    }
    sort(dq.begin(), dq.end());

    for(int i=1;i<N;i++) {
        dq.push_back(dq.front());
        dq.pop_front();
    }
    cout << dq.front().second;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}
