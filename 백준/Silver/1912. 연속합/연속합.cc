#include <bits/stdc++.h>

using namespace std;

int N;
int arr[100003];

int main() {
	cin >> N;
	int ans=INT_MIN;
	for(int i=1;i<=N;i++) {
		cin >> arr[i];
		if(arr[i]<arr[i-1]+arr[i]) arr[i] = arr[i-1]+arr[i];
		ans = max(ans, arr[i]);
	}
	cout << ans;
}