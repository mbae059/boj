#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
int T, N, K, M;
//ofstream out("temp.txt");

vector<int> x, y;

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tempX, tempY;
		cin >> tempX >> tempY;
		x.push_back(tempX);
		y.push_back(tempY);
	}
}


void Solution() {
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());

	int martX = x.at(x.size() / 2);
	int martY = y.at(y.size() / 2);

	unsigned long long D = 0;
	for (auto d : x) {
		D += abs(d - martX);
	}

	for (auto d : y) {
		D += abs(d - martY);
	}

	cout << D;

}

void Solve() {
	Input();
	Solution();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Solve();
}