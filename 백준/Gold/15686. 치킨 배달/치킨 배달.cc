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

int G[51][51];
vector<pii> house;
vector<pii> chicken;
vector<pii> _chicken;
int min_d=INT_MAX;
bool make_per[14];

void solve() {
	int sumd=0;
	for(auto i : house) {
		int y = i.first;
		int x = i.second;
		
		int close_d=INT_MAX;
		for(auto j : _chicken) {
			int hy = j.first;
			int hx = j.second;
			
			int d = abs(hy-y)+abs(hx-x);
			close_d = min(close_d, d);
		}
		sumd+=close_d;
	}
	min_d = min(sumd, min_d);
}

void per(int idx, int cnt) {
	
	if(cnt==M) {
		solve();
		return;
	}
	
	for(int i=idx;i<chicken.size();i++) {
		if(make_per[i]==1) continue;
		
		make_per[i]=1;
		_chicken.push_back(chicken[i]);
		per(i+1, cnt+1);
		make_per[i]=0;
		_chicken.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> M;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cin >> G[i][j];
			if(G[i][j]==1) house.push_back({i,j});
			if(G[i][j]==2) chicken.push_back({i,j});
		}
	}
	
	per(0, 0);
	cout << min_d;
}