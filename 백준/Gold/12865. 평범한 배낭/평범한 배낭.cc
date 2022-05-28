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

pii things[101];
int values[101][100001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> K;
	
	for(int i=1;i<=N;i++) {
		cin >> things[i].first >> things[i].second;
	}
	
	for(int i=1;i<=N;i++) {
		for(int j=0;j<=K;j++) {
			if(things[i].first>j) {
				values[i][j]=values[i-1][j];
			}
			else {
				values[i][j] = max(values[i-1][j], things[i].second+values[i-1][j-things[i].first]);
			}
		}
	}
	cout << values[N][K];			
}