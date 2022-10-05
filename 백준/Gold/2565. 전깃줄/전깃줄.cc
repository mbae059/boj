#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
int T, N;
pii arr[101];
int dp[1001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N;
	
	for(int i=1;i<=N;i++) cin >> arr[i].first >> arr[i].second;
	sort(arr+1, arr+N+1);
	
	int ans=0;
	for(int i=1;i<=N;i++) {
		for(int j=0;j<i;j++) {
			if(arr[i].second>arr[j].second) dp[i]=max(dp[i], dp[j]);
		}
		dp[i] +=1;
		ans = max(ans, dp[i]);
	}
	cout << N-ans;
}