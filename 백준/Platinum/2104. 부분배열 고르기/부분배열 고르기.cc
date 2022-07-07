#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<vi> vii;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef map<int, int> mii;
typedef set<int> si;
int T, N, K, M;
//ofstream out("temp.txt");

vll v;

ll solve(int nodeLeft, int nodeRight) {
    if(nodeLeft==nodeRight) return v[nodeLeft]*v[nodeLeft];

    int mid = (nodeLeft+nodeRight)/2;
    ll maxValue = max(solve(nodeLeft, mid), solve(mid+1, nodeRight));

    ll sum = v[mid]+v[mid+1];

    int l = mid;
    int r = mid+1;
	ll minValue = min(v[mid], v[mid+1]);

	maxValue = max(maxValue, minValue* sum);

    while(nodeLeft < l || r < nodeRight) {
        if(r<nodeRight && ((l==nodeLeft) || v[r+1] > v[l-1])) {
            sum += v[++r];
			minValue = min(minValue, v[r]);
        }
		else {
			sum += v[--l];
			minValue = min(minValue, v[l]);
		}
		maxValue = max(maxValue, minValue*sum);
    }
	return maxValue;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	cin >> N;
    v.resize(N);

    for(int i=0;i<N;i++) cin >> v[i];

	cout << solve(0,N-1);

}