#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()

using namespace std;
using pii = pair<int, int>;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vull = vector<ull>;
using vvi = vector<vi>;
using vpii = vector<pii> ;
using vll = vector<ll>;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using tiii = tuple<int, int, int> ; //get<0>(t);
using vtiii = vector<tiii>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
int T, N, K, M, S, H, W, Q; // S is for MCMF, network flow
int dir[4][2] = {{1,0},{-1,0}, {0,1}, {0,-1}};
//ofstream out("temp.txt");
//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;
//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())

void print(pii a) {
    cout << a.first << " " << a.second << endl;
}

template <typename T>
void print(const T& a) {
    cout << a << endl;
}

template <typename T>
void print(vector<T>& v) {
    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}
bool inRange(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=M;
}
bool inRangeN(int y, int x) {
    return 1<=y && y<=N && 1<=x && x<=N;
}
// vector<int> combination;
// bool visited[1005];
// void dfs(int idx, int cnt) { //implement with dfs(1, 0). N and K must be global variable
// 	if(cnt==K) {
// 		for(auto i : combination) {
// 			cout << i << " ";
// 		}
// 		cout << endl;
// 		return;
// 	}
	
// 	for(int i=idx;i<=N;i++) { //idx, N을 잘볼것
// 		if(visited[i]==1) continue;
		
// 		visited[i]=1;
// 		combination.push_back(i);
// 		dfs(i+1, cnt+1); //be careful with i+1, cnt+1
// 		visited[i]=0;
// 		combination.pop_back();
// 	}
// }


char matrix[11][11] {};
bool visited[11][11] {};
int answer = 0;
map<pair<char, char>, int> mp;

void goNext(int, int);

void dfs(int y, int x) {
    if(y==N && x==M) {
        if(visited[N][M]) answer++;
        return;
    }
    if(visited[y][x]) {
        goNext(y,x);
        return;
    }
    if(x+1<=M && visited[y][x+1]==0) {
        char a = matrix[y][x];
        char b = matrix[y][x+1];
        if(a>b) swap(a,b);
        if(mp[{a,b}]==0) {
            mp[{a,b}] = 1;
            visited[y][x] = 1;
            visited[y][x+1] = 1;
            goNext(y,x);
            visited[y][x] = 0;
            visited[y][x+1] = 0;
            mp[{a,b}] = 0;
        }
    }
    
    if(y+1<=N && visited[y+1][x]==0) {
        char a = matrix[y][x];
        char b = matrix[y+1][x];
        if(a>b) swap(a,b);
        if(mp[{a,b}]==0) {
            mp[{a,b}] = 1;
            visited[y][x] = 1;
            visited[y+1][x] = 1;
            goNext(y,x);
            mp[{a,b}] = 0;
            visited[y][x] = 0;
            visited[y+1][x] = 0;
        }
    }
}
void goNext(int y, int x) {
    if(x==M) {
        dfs(y+1, 1);
    }
    else {
        dfs(y, x+1);
    }

}
void Solve() {
    N = 8;
    M = 7;
    rep(i,1,N) {
        rep(j,1,M) {
            cin >> matrix[i][j];
        }
    }

    rep(i,0,6) {
        rep(j,i,6) {
            char a = i+'0';
            char b = j+'0';
            mp[{a,b}] = 0;
        }
    }
    dfs(1,1);
    cout << answer;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}