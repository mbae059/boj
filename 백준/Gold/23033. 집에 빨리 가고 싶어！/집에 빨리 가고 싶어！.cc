#include <bits/stdc++.h>
#define pbk push_back
#define MAX 300003
#define p_q priority_queue
#define INF 987654321
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
int N, M, K;

struct info {
	int to;
	int dis;
	int delay;
};

vector<info> edge[MAX];
int d[MAX];

struct cmp {
	bool operator() (const pii& a, const pii& b) {
		return a.second > b.second;
	}
};

int dijkstra(int x) {
	p_q<pii, vpii, cmp> pq;

	pq.push({ 1, 0 });
	fill(d, d + MAX, INF);
	d[1] = 0;

	while (!pq.empty()) {
		int cur = pq.top().first;
		int dis = pq.top().second;
		pq.pop();
		if (d[cur] < dis) continue;

		for (auto next : edge[cur]) {
			int wait = dis % next.delay == 0 ? 0 : next.delay - dis % next.delay;
			int estimatedTime = wait + dis + next.dis;

			if (d[next.to] > estimatedTime) {
				d[next.to] = estimatedTime;
				pq.push({ next.to, estimatedTime });
				//out << cur << " " << dis << " " << next.to << " " << estimatedTime << " " << dis % next.delay << endl;
			}
		}
	}
	return d[N];
}

int main() {
	cin >> N >> M;
	
	for (int i = 0; i < M; i++) {
		int a, b, t, w;
		cin >> a >> b >> t >> w; //Consider time as distance for convenience
		edge[a].pbk({ b,t,w });
	}
	cout << dijkstra(1);
}