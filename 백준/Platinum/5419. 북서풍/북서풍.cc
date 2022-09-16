#include <bits/stdc++.h>
#define pbk push_back

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef long long ll;
int N, M,T,K;


vpii v;
vi press;
ll fenwick[75003];
void Update(int idx, int value) {
    while(idx <= 75000) {
        fenwick[idx] += value;
        idx += idx & -idx;
    }
}

ll sum(int idx) {
    ll ret=0;
    while(idx>0) {
        ret += fenwick[idx];
        idx -= idx & -idx;
    }
    return ret;
}
void Solve() {
    v.clear();
    press.clear();
    memset(fenwick, 0, sizeof(fenwick));

    int N; cin >> N;
    for(int i=0;i<N;i++) {
        int x,y; cin >> x >> y;
        v.pbk({x,y});
        press.pbk(y);
    }

    sort(v.begin(), v.end(), [](pii& a, pii& b) {
        if(a.first==b.first) return a.second > b.second;
        return a.first < b.first;
    });
    sort(press.begin(), press.end());
    press.erase(unique(press.begin(), press.end()), press.end());

    ll ans =0;
    for(int i=0;i<N;i++) {
        v[i].second = lower_bound(press.begin(), press.end(), v[i].second) - press.begin() + 1;
        ans += sum(75000) - sum(v[i].second-1);
        Update(v[i].second, 1);
    }
    cout << ans << endl;
}

int main() {
    cin >> T;
    while(T--) Solve();

}
