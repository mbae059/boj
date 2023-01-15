#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pb push_back
#define FOR(i, n) for(int i=0;i<(n);++i)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<vi> vii;
typedef vector<pii> vpii;

int T, N, K, M;
//ofstream out("temp.txt");

void print(int a, int b) {
	cout << a << " " << b << endl;
}

void print(pii a) {
	cout << a.first << " " << a.second << endl;
}

void print(int a) {
	cout << a << endl;
}

void print(vi& v) {
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

void merge(vector<int>& arr, int l, int mid, int r, int& ic) {
	vector<int> left, right;
	for (int i = l; i <= mid; i++) left.pb(arr[i]);
	for (int i = mid + 1; i <= r; i++) right.pb(arr[i]);

	int i = 0; int j = 0;
	int n1 = left.size();
	int n2 = right.size();

	int k = l;
	while (i < n1 && j < n2) {
		if (left[i] <= right[j]) {
			arr[k++] = (left[i++]);
		}
		else {
			arr[k++] = (right[j++]);
			ic += (n1 - i);
		}
	}
	while (i < n1) {
		arr[k++] = (left[i++]);
	}
	while (j < n2) {
		arr[k++] = (right[j++]);
	}
}

void mergesort(vector<int>& arr, int l, int r, int& ic) {
	if (l >= r) return;
	int mid = (l + r) / 2;
	mergesort(arr, l, mid, ic);
	mergesort(arr, mid + 1, r, ic);

	merge(arr, l, mid, r, ic);
}

int find_inversion_count(vector<int>& arr) {
	int n = arr.size();
	int ic = 0;
	mergesort(arr, 0, n - 1, ic);
	return ic;
}


/*
*
*
*
*
*
*
*
*
*
*
*
*
*
*/


bool F_W[502][502];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		F_W[a][b] = 1;
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (F_W[i][k] && F_W[k][j]) F_W[i][j] = 1;
			}
		}
	}
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		int cnt = 0;
		for (int j = 1; j <= N; j++) {
			if (F_W[i][j] == 1 || F_W[j][i] == 1) {
				cnt++;
			}
		}
		if (cnt == N - 1) answer++;
	}
	cout << answer;
}
