#include <bits/stdc++.h>
#define endl '\n'
#define INF INT_MAX
#define p_q priority_queue
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tiii;
typedef long long ll;
int T, N, K, M;
//ofstream out("temp.txt");

vector<ll>arr(1000001);
vector<ll>tree(4000001);

ll sum(int start, int end, int node, int l, int r) {
	if(l<=start && end <= r) return tree[node];
	else if(start>r || end<l) return 0;
	
	int mid = (start+end)/2;
	
	return sum(start, mid, node*2, l, r) + sum(mid+1, end, node*2+1, l, r);
}

void update(int start, int end, int node, int idx, ll dif) {
	if(!(start<=idx && idx<=end)) return;
	
	tree[node]+=dif;
	if(start==end) return;
	int mid = (start+end)/2;
	update(start, mid, node*2, idx, dif);
	update(mid+1, end, node*2+1, idx, dif);
}

ll make_tree(int start, int end, int node) {
	if(start==end) {
		return tree[node] = arr[start];
	}
	
	int mid = (start+end)/2;
	return tree[node] = make_tree(start, mid, node*2)+make_tree(mid+1, end, node*2+1);
}
	

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> M >> K;
	
	for(int i=0;i<N;i++) {
		cin >> arr[i];
	}
	make_tree(0,N-1, 1);
	
	for(int i=0;i<M+K;i++) {
		ll a, b, c;
		cin >> a >> b>> c;
		b--;
		if(a==1) {
			ll dif = c-arr[b];
			arr[b] = c;
			update(0, N-1, 1, b, dif);
		}
		else {
			c--;
			cout << sum(0, N-1, 1, b, c) << endl;
		}
	}
}