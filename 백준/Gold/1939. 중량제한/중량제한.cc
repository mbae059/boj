#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()

using namespace std;
using pii = pair<int, int>;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vull = vector<ull>;
using vvi = vector<vi>;
using vpii = vector<pii> ;
using vll = vector<ll>;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using tiii = tuple<int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
int T, N, K, M, S, H, W, Q; // S is for MCMF, network flow
#define MAX 10001
int parent[MAX]; //parent[MAX] should be 1, 2, 3...
int getParent(int num) {
    if (parent[num] == num) return num;
    return parent[num] = getParent(parent[num]);
}
void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a < b) parent[b] = a;
    else parent[a] = b;
}

bool isSameParent(int a, int b) {
    return getParent(a) == getParent(b);
}
class Edge {
public:
    int node[2];
    ll dis;
    Edge(int a, int b, ll _dis) {
        node[0] = a;
        node[1] = b;
        dis = _dis;
    }
    bool operator < (const Edge& edge) {
        return dis > edge.dis;
    }
};
vector<Edge> edge;
vector<pair<int,ll>> Kedge[MAX];
bool visited[MAX] {};
void Kruskal() { //MST
    cin >> N >> M; //N is node, M is edge, Node starts from 1 to N
    for (int i = 0; i < M; i++) {
        int s, e;
        ll dis;
        cin >> s >> e >> dis;
        edge.push_back(Edge(s, e, dis));
    }
    cin >> S >> T; //본문의 A섬, B섬
    sort(all(edge));
    for (int i = 1; i <= N; i++) { //setting nodes
        parent[i] = i;
    }
    for (int i = 0; i < edge.size() ; i++) {
        int nodeA = edge[i].node[0];
        int nodeB = edge[i].node[1];
        ll dis = edge[i].dis;
        if (!isSameParent(nodeA, nodeB)) {
            unionParent(nodeA, nodeB);
            //Kedge는 mst로만 이루어진 그래프를 정의
            Kedge[nodeA].pbk({nodeB, dis});
            Kedge[nodeB].pbk({nodeA, dis});
        }
    }
    //S에서 T로 가는 거리를 찾기 위해 BFS를 시행
    //Kedge를 통해 찾기 때문에 길은 유일함.
    //최대값의 최솟값을 찾기 위해 min을 사용하여 distance를 정의
    queue<pair<int, ll>> q;
    q.push({S, LLONG_MAX});
    visited[S] = 1;
    while(!q.empty()) {
        int cur = q.front().first;
        ll dis = q.front().second;
        q.pop();

        if(cur==T) {
            cout << dis;
            return;
        }
        for(auto next : Kedge[cur]) {
            int nextNode = next.first;
            ll nextDis = min(dis, next.second);
            if(visited[nextNode]) continue;
            q.push({nextNode, nextDis});
            visited[nextNode] = 1;
        }
    }
}

void Solve() {
    Kruskal();
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}