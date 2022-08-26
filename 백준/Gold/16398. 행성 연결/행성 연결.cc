#include <bits/stdc++.h>
#define MAX 1004
#define pbk push_back
#define p_q priority_queue
#define endl "\n"
#define INF 987654321
using namespace std;

typedef vector<int> vi;
typedef pair<int, int > pii;
typedef vector<vi> vvi;
typedef tuple<int, int,long long > tiii;


int N, M, T;
bool cmp(tiii a, tiii b) {
    return get<2>(a) < get<2>(b);
}

vector<tiii> v;
int parent[MAX];
int getParent(int x) {
    if(parent[x] == x) return x;
    return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);

    if(a < b) parent[b] = a;
    else parent[a] = b;
}

bool isSameParent(int a, int b) {
    return getParent(a) == getParent(b);
}
void Solve() {
    cin >> N;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            int temp;
            cin >> temp;
            if(i==j) continue;
            v.pbk({i,j,temp});
        }
    }
    sort(v.begin(), v.end(), cmp);
    for(int i=0;i<N;i++) parent[i] = i;
    long long sum=0;
    for(auto i : v) {
        int a = get<0>(i);
        int b = get<1>(i);
        int c = get<2>(i);

        //cout << a << " " << b << " " << c << endl;
        if(!isSameParent(a, b)) {
            sum+= c;
            unionParent(a,b);
            //cout << "SUM : " << sum << endl;
        }
    }
    cout << sum;
}

int main() {
    Solve();
}
