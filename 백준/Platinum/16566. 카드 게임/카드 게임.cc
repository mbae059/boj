#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()

using namespace std;
using vi = vector<int>;
using si = set<int>;
int N,M,K;

vi card;
vi q;
#define MAX 4000002
int parent[MAX]; //parent[MAX] should be 1, 2, 3...
int getParent(int num) {
    if (parent[num] == num) return num;
    return parent[num] = getParent(parent[num]);
}
void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a > b) parent[b] = a;
    else parent[a] = b;
}

bool isSameParent(int a, int b) {
    return getParent(a) == getParent(b);
}
void Solve() {
    cin >> N >> M >> K;
    card.pbk(-1);
    rep(i,1,M) {
        int temp; cin >> temp;
        card.pbk(temp);
    }
    sort(all(card));
    rep(i,1,K) {
        int temp; cin >> temp;
        q.pbk(temp);
    }
    rep(i,1,N) parent[i] = i;
    for(auto i : q) {
        auto idx = upper_bound(all(card), i)-card.begin();
        cout << card[getParent(idx)] << endl;
        unionParent(getParent(idx), getParent(idx)+1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}