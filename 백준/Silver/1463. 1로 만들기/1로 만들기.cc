#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int N;
int arr[1000000];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;
	int cnt=0;
	arr[1]=0;
	arr[2]=1;
	arr[3]=1;
	
	for(int i=4;i<=N;i++) {
		if(i%6==0) arr[i]=min({arr[i-1]+1, arr[i/2]+1, arr[i/3]+1});
		else if(i%3==0) arr[i] = min(arr[i/3]+1, arr[i-1]+1);
		else if(i%2==0) arr[i] = min(arr[i/2]+1, arr[i-1]+1);
		else arr[i]=arr[i-1]+1;
	}
	cout << arr[N];
}