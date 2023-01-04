#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
int T, N, K, M;
//ofstream out("temp.txt");

deque<int> v;
string commands;

void Input() {
	v.clear();

	cin >> commands;
	cin >> N;
	
	string str;
	cin >> str;

	int temp = 0;
	for (auto i : str) {
		if (i == '[' ) continue;

		if (i == ',' || i==']') {
			v.push_back(temp);
			temp = 0;
			continue;
		}
		temp *= 10;
		temp += (i-'0');
	}

	if (v.size() == 1 && v[0] == 0) v.clear();

}


void Solution() {
    bool R = 0;
    for(auto c : commands) {
        if(c=='R') {
            R = !R;
            continue;
        }

        if(v.empty()) {
            cout << "error" << endl;
            return;
        }
        if(R) {
            v.pop_back();
        }
        else v.pop_front();
    }
    if(R) {
        reverse(v.begin(), v.end());
    }
	cout << '[';
	
	for (int i = 0; i < v.size(); i++) {
		cout << v.at(i);
		if (i != v.size() - 1) {
			cout << ',';
		}
	}
	cout << ']' << endl;
}

void Solve() {
	Input();
	Solution();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;

	while (T--) {
		Solve();
	}
}