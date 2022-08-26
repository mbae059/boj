#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
int T, N;
int arr[1001][4];
int dp[1001][4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);
	
	cin >> N;
	for(int i=1;i<=N;i++) {
		for(int j=1;j<4;j++) cin >> arr[i][j];
	}
	
	for(int j=1;j<4;j++) dp[1][j] = arr[1][j];
	
	for(int i=2;i<=N;i++) {
		dp[i][1] = min(dp[i-1][2], dp[i-1][3]) + arr[i][1];
		dp[i][2] = min(dp[i-1][1], dp[i-1][3]) + arr[i][2];
		dp[i][3] = min(dp[i-1][2], dp[i-1][1]) + arr[i][3];
	}
	
	cout << min({dp[N][1], dp[N][2], dp[N][3]});
	
}