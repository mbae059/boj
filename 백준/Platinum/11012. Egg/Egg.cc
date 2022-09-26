#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
using namespace std;
typedef long long ll;
typedef vector<int> vi;
int T, N, K, M;


struct Node {
	Node* l, * r;
	ll v;

	Node() {
		l = r = NULL;
		v = 0;
	}
};
#define MAX 100002
//When using MAX, root MAX and arr MAX is DIFFERENT!!!! KEEP IN MIND!!! 
Node* root[MAX];
vi xpos[MAX];

void build(Node* node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight) {
		node->v = 0;
		return;
	}
	int m = nodeLeft + (nodeRight - nodeLeft) / 2;

	node->l = new Node();
	node->r = new Node();

	build(node->l, nodeLeft, m);
	build(node->r, m + 1, nodeRight);

	node->v = node->l->v + node->r->v;
}

//doesn't update origin segment tree but updates new segment tree and connects it into a existing tree
Node* update(Node* now, int nodeLeft, int nodeRight, int idx, int value) {
	if (nodeRight < idx || idx < nodeLeft) return now;

	if (nodeLeft == nodeRight) {
		Node* leaf = new Node();
		leaf->v = now->v + value;
		return leaf;
	}

	int middle = nodeLeft + (nodeRight - nodeLeft) / 2;
	Node* leaf = new Node();
	leaf -> l = update(now->l, nodeLeft, middle, idx, value);
	leaf -> r = update(now->r, middle + 1, nodeRight, idx, value);


	leaf->v = leaf->l->v + leaf->r->v;
	return leaf;
}

ll query(Node* node, int nodeLeft, int nodeRight, int l, int r) { //want to know the addition of l~r
	if (nodeRight < l || r < nodeLeft) return 0;
	if (l <= nodeLeft && nodeRight <= r) return node->v;

	int middle = nodeLeft + (nodeRight - nodeLeft) / 2;

	return query(node->l, nodeLeft, middle, l, r) + query(node->r, middle + 1, nodeRight, l, r);
}

void Solve() {
	cin >> N >> M;
    
	rep(i, 1, N) {
		int x, y; cin >> x >> y;
		x++; y++;
		xpos[y].pbk(x);
	}

	root[0] = new Node();
	build(root[0], 0, MAX-1);

	rep(i, 1, MAX-1) {
		root[i] = root[i - 1];

		for (auto x : xpos[i]) {
			root[i] = update(root[i], 0, MAX-1, x, 1);
		}
	}

	ll answer = 0;
	rep(i, 1, M) {
		int xs, xe, ys, ye; cin >> xs >> xe >> ys >> ye;
		xs++; xe++; ys++; ye++;
		answer += query(root[ye], 0, MAX-1, xs, xe) - query(root[ys - 1], 0, MAX-1, xs, xe);
	}
	cout << answer << endl;

    rep(i, 0, MAX-1) {
        xpos[i].clear();
        root[i] = NULL;
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	while(T--) Solve();
}