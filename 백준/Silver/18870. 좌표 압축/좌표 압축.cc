#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef tuple<int, int, int> tiii;
int N;
tiii arr[1000005];

void print() {
	for(int i=0;i<N;i++) cout << get<2>(arr[i]) << endl;
}

bool cmp(tiii a, tiii b) {
	return get<1>(a) < get<1>(b);
}

int main() {
	cin >> N;
	for(int i=0;i<N;i++) {
		cin >> get<0>(arr[i]);
		get<1>(arr[i])=i;
	}
	sort(arr, arr+N);
	get<2>(arr[0])=0;
	for(int i=1;i<N;i++) {
		if(get<0>(arr[i]) > get<0>(arr[i-1])) get<2>(arr[i])=get<2>(arr[i-1])+1;
		else get<2>(arr[i]) = get<2>(arr[i-1]);
	}
	sort(arr, arr+N, cmp);
	print();
}