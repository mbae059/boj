#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;
int T;
vector<int> adjacent[20001];
int visited[20001];

int ans=INT_MAX;

void BFS() {
	for(int i=0;i<20001;i++) adjacent[i].clear();
	memset(visited, 0, sizeof(visited));
	
	int V, E;
	cin >> V >> E;
	for(int i=0;i<E;i++) {
		int b, e;
		cin >> b >> e;
		adjacent[b].push_back(e);
		adjacent[e].push_back(b);
	}
	
	for(int i=1;i<=V;i++) {
		if(visited[i]==0) {
			queue<int> q;
			q.push(i);
			visited[i]=1;
			
			while(!q.empty()) {
				int cur = q.front();
				q.pop();
				
				for(auto i : adjacent[cur]) {
					if(visited[i]==0) {
						visited[i] = -visited[cur];
						q.push(i);
					}
					else if(visited[i] * visited[cur]>0) {
						cout << "NO" << endl;
						return;
					}
				}
			}
		}
	}
	cout << "YES" << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);
	cin >> T;
	
	while(T--) {
		BFS();
	}
}