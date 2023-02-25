#include <bits/stdc++.h>
#define endl '\n'
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 

using namespace std;
using ll = long long;
using vll = vector<ll>;
#define MAX 1000003
ll N, M, K;
bool visited[MAX] {};
void Solve() {
    cin >> N >> M >> K;
    vll v(N+1);
    rep(i,1,N) cin >> v[i];
    
    if(M==0 || M==1) {
        cout << "YES";
        return;
    }
    rep(i,1,M) {
        ll a, b; cin >> a >> b;
        if(a>b) swap(a,b);
        if(a==1 && b==N) visited[a] = 1;
        else visited[b] = 1;
    }
    
    ll needs = 0;
    ll mn = v[1];
    ll first = 0;
    rep(i,2,N) {
        if(visited[i]) {
            if(first==0) first = mn;
            else {
                needs += mn;
            }
            mn = v[i];
        }
        else {
            mn = min(mn, v[i]);
        }
    }
    if(visited[1]) {
        needs += first;
        needs += mn;
    }
    else {
        needs += min(first, mn);
    }
    cout << (needs > K ? "NO" : "YES");
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}