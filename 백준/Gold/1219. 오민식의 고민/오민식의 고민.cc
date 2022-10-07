#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef set<int> si;
typedef queue<int> qi;
typedef vector<pair<ll, ll>> vpll;
int T, N, K, M, S;

#define MAX 51
bool inQ[MAX] {};
vpll edge[MAX];
ll d[MAX];
ll cycle[MAX] {};
ll earn[MAX] {};
bool visited[MAX] {};
si INFcycle;
void SPFA(int start) {
    fill(d+1, d+1+N, INF);
    qi q;
    d[start] = -earn[start];
    q.push(start);
    inQ[start] = 1;
    cycle[start] += 1;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        inQ[cur] = 0;
        for(auto next : edge[cur]) {
            if(d[next.first] > d[cur] + next.second-earn[next.first]) {
                d[next.first] = d[cur] + next.second-earn[next.first];
                if(!inQ[next.first]) {
                    cycle[next.first] += 1;
                    inQ[next.first] = 1;
                    if(cycle[next.first]>=N) {
                        INFcycle.insert(next.first);
                    }
                    else {
                        q.push(next.first);
                    }
                }
            }
        }
    }
}
bool FW[MAX][MAX] {};

void Solve() {
    cin >> N >> S >> T >> M;
    S++; T++;
    rep(i,1,M) {
        int a, b, v; cin >> a >> b >> v;
        a++; b++;
        edge[a].pbk({b,v});
        FW[a][b] = 1;
    }
    FW[S][S] = 1;
    rep(i,1,N) cin >> earn[i];

    SPFA(S);

    rep(k, 1, N) {
        rep(i, 1, N) {
            rep(j, 1, N) {
                FW[i][j] = FW[i][j] || (FW[i][k] && FW[k][j]);
            }
        }
    }
    bool flag = 0;
    for(auto i : INFcycle) {
        if(FW[i][T]) {
            flag=1;
            break;
        }
    }

    if(FW[S][T]==0) cout << "gg";
    else if(flag) cout << "Gee";
    else cout << -d[T];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
}