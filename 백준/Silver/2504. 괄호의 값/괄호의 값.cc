#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
using namespace std;
typedef pair<int, char> pic;
typedef long long ll;
int T, N, K, M;
//ofstream out("temp.txt");

string str;
stack<char> s;
stack<pic> cal;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> str;
	unsigned long long ans = 0;

	stack<char> valid;


	int answer = 0, temp = 1;
	stack<char> s; 

	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == '(') {
			temp *= 2;
			s.push('(');
		}
		else if (str.at(i) == '[') {
			temp *= 3;
			s.push('[');
		}

		else if (str.at(i) == ')') {
			if (s.empty() || s.top() != '(') {
				answer = 0;
				break;
			}

			if (str.at(i - 1) == '(') {
				answer += temp;
				temp /= 2;
				s.pop();
			}
			else {
				temp /= 2;
				s.pop();
			}
		}

		else if (str.at(i) == ']') {
			if (s.empty() || s.top() != '[') {
				answer = 0;
				break;
			}

			if (str.at(i - 1) == '[') {
				answer += temp;
				temp /= 3;
				s.pop();
			}
			else {
				temp /= 3;
				s.pop();
			}
		}



	}

	if (!s.empty()) answer = 0;

	cout << answer;


}