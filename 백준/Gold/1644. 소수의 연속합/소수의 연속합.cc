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
#define NUM 4000003
bool isPrime[NUM];
vector<int> prime;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N;
	
	for(int i=2;i<=sqrt(N);i++) {
		if(isPrime[i]==0) {
			int k=i*2;
			while(k<=N) {
				isPrime[k] = 1;
				k+=i;
			}
		}
	}
	if(N==1) {
		cout << 0;
		exit(0);
	}
	for(int i=2;i<=N;i++) {
		if(isPrime[i]==0) prime.push_back(i);
	}
	int s=0, e=0;
	int size = prime.size();
	int sum=prime[0];
	int cnt=0;
	while(s<size) {
		if(sum==N) {
			cnt++;
			s++;
			sum+=prime[s];
		}
		else if(sum<N) {
			s++;
			sum+=prime[s];
		}
		else {
			sum-=prime[e];
			e++;
		}
	}
	cout << cnt;
}