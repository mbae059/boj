#include <bits/stdc++.h>
#define MAX 10024
using namespace std;

int N, M, K, T;
typedef long long ll;
typedef pair<int,int> pii;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef set<int> si;
typedef map<int, int> mii;
typedef queue<int> qi;

int v[MAX], s[4*MAX];
int segment(int node, int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return s[node] = v[nodeLeft];

    int mid = (nodeLeft+nodeRight)/2;

    return s[node] = segment(node*2, nodeLeft, mid) + segment(node*2+1, mid+1, nodeRight);
}

void update(int node, int nodeLeft, int nodeRight, int idx, int dif) { // dif is differece
    if(idx < nodeLeft || nodeRight < idx) return;
    s[node] += dif;
    if(nodeLeft == nodeRight) return;
    int mid = (nodeLeft+nodeRight)/2;
    update(node*2, nodeLeft, mid, idx, dif);
    update(node*2+1, mid+1, nodeRight, idx, dif);
}

int query(int node, int nodeLeft, int nodeRight, int left, int right) {
    if(left <= nodeLeft && nodeRight <= right) return s[node];

    if(nodeRight < left || right < nodeLeft) return 0;
    
    int mid = (nodeLeft+nodeRight)/2;

    return query(node*2, nodeLeft, mid, left, right) +query(node*2+1, mid+1, nodeRight, left, right);
}
int mine[MAX][MAX] {0,};


void Solve() {
    memset(mine, 0, sizeof(mine));
    cin >> N;
    int M=-1;
    while(N--) {
        int a, b;
        cin >> a >> b;
        for(int i=0;i<=10;i++) {
            for(int j=0;j<=10;j++) {
                mine[i+a][j+b]+=1;
                M = max(M, mine[i+a][j+b]);
            }
        }
    }
    cout << M << endl;
}
int main() {
    cin >> T;
    while(T--) {
        Solve();
    }
}