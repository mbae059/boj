#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
int T, N, K, M;
//ofstream out("temp.txt");

int dust[50][50];
int dust_spread_second[50][50];
int filter_y;
int total_dust=0;
int filtered_dust=0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool in_range(int y, int x) {
	return x>=0 && x<M && y>=0 && y<N;
}

bool not_in_air_filter(int y, int x) {
	if(x==0) {
		if(y==filter_y || y==filter_y-1) return false;
	}
	return true;
}


bool can_spread(int y, int x) {
	if(in_range(y, x) && not_in_air_filter(y, x)) return true;
	else return false;
}

void spread_cell(int y, int x) {
	for(int i=0;i<4;i++) {
		int next_y = y+dy[i];
		int next_x = x+dx[i];
		if(can_spread(next_y, next_x)) {
			dust_spread_second[next_y][next_x]+=dust[y][x]/5;
			dust_spread_second[y][x] -= dust[y][x]/5;
		}
	}
}

void spread() {
	memset(dust_spread_second, 0, sizeof(dust_spread_second));
	//for each cell, keep track of dust spreading every second
	for(int i=0;i<N;i++) {
		for(int j=0;j<M;j++) {
			spread_cell(i, j);
		}
	}
	//calculate dust spreading with current dust
	for(int i=0;i<N;i++) {
		for(int j=0;j<M;j++) {
			dust[i][j] += dust_spread_second[i][j];
		}
	}
}

void up(int y, int x) {
	while(!(y==filter_y-1 || y==N-1)) {
		dust[y][x] = dust[y+1][x];
		y++;
	}
}

void left(int y, int x) {
	while(x!=M-1) {
		dust[y][x] = dust[y][x+1];
		x++;
	}
}

void down(int y, int x) {
	while(!(y==0 || y==filter_y)) {
		dust[y][x] = dust[y-1][x];
		y--;
	}
}

void right(int y, int x) {
	while(x!=0) {
		dust[y][x] = dust[y][x-1];
		x--;
	}
}
void upper_air() {
	down(filter_y-1, 0);
	//air filtered
	filtered_dust+=dust[filter_y-1][0];
	dust[filter_y-1][0] = 0;
	left(0, 0);
	up(0, M-1);
	right(filter_y-1, M-1);
}

void lower_air() {
	up(filter_y, 0);
	//air filtered
	filtered_dust+=dust[filter_y][0];
	dust[filter_y][0] = 0;
	left(N-1, 0);
	down(N-1, M-1);
	right(filter_y, M-1);
}
void activate() { //air conditioner working
	upper_air();
	lower_air();
}

void print() {
	for(int i=0;i<N;i++) {
		for(int j=0;j<M;j++) {
			cout << dust[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void flow_second() {
	spread();
	//print();
	activate();
	//print();
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> M >> T;
	
	for(int i=0;i<N;i++) {
		for(int j=0;j<M;j++) {
			cin >> dust[i][j];
			if(dust[i][j]==-1) filter_y = i;
			else total_dust+=dust[i][j];
		}
	}
	
	for(int i=0;i<T;i++) {
		//cout << i+1 << " second" << endl;
		flow_second();
	}
	
	cout << total_dust-filtered_dust;
}