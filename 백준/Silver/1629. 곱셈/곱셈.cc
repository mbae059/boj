#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
ll a, b, c;

ll solve(ll a, ll b, ll c) {
	if(b==1) return a%c;
	
	ll _c = solve(a, b/2, c);
	_c =(_c*_c)%c;
	if(b%2) _c=(_c*a)%c;
	return _c;
}
	
int main() {
	cin >> a >> b >> c;
	cout << solve(a,b,c);
	
}