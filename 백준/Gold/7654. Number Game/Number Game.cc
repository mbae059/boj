#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
using vi = vector<int>;
int N;
void printWin() {
    cout << "Carl can win" << endl;
}
void printLose() {
    cout << "Carl can\'t win" << endl;
}
void Solve() {
    vi v(21);
	bool flag = 0;
    for(int i=1;i<=20;i++) {
		cin >> v[i];
        if(v[i]==0) return;
		if(i + v[i] != 21) flag = 1;
	}
    

	if((flag==0 && N % 21 == 0) || N == 21) printLose();
	else printWin();
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while(true) {
        cin >> N;
        if(N==0) break;
        Solve();
    }
}