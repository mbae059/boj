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
/*
vector<int> combination;
bool visited[1005];
void dfs(int idx, int cnt) { //implement with dfs(1, 0). N and K must be global variable
	if(cnt==K) {
		for(auto i : combination) {
			cout << i << " ";
		}
		cout << endl;
		return;
	}
	
	for(int i=idx;i<=N;i++) { //idx, N을 잘볼것
		if(visited[i]==1) continue;
		
		visited[i]=1;
		combination.push_back(i);
		dfs(i+1, cnt+1); //be careful with i+1, cnt+1
		visited[i]=0;
		combination.pop_back();
	}
}
*/
/* Basic Info
A-Z is 26 char
<regex> header file is used for find patterns
*/

/* FOR COUNTING INVERSION, MERGE SORT VERSION
void merge(vector<int>& arr, int l, int mid, int r, int& ic) {
    vector<int> left, right;
    for (int i = l; i <= mid; i++) left.pbk(arr[i]);
    for (int i = mid + 1; i <= r; i++) right.pbk(arr[i]);
    int i = 0; int j = 0;
    int n1 = left.size();
    int n2 = right.size();
    int k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = (left[i++]);
        }
        else {
            arr[k++] = (right[j++]);
            ic += (n1 - i);
        }
    }
    while (i < n1) {
        arr[k++] = (left[i++]);
    }
    while (j < n2) {
        arr[k++] = (right[j++]);
    }
}
void mergesort(vector<int>& arr, int l, int r, int& ic) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergesort(arr, l, mid, ic);
    mergesort(arr, mid + 1, r, ic);
    merge(arr, l, mid, r, ic);
}
int find_inversion_count(vector<int>& arr) {
    int n = arr.size();
    int ic = 0;
    mergesort(arr, 0, n - 1, ic);
    return ic;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


// THIS IS SEGMENT TREE
#define MAX 1111111
ll v[MAX], s[4*MAX]; //v starts from 0, s starts from 1.
//nodeLeft and nodeRight always has to be 0 and N-1 as it is used in binary searching
ll segment(int node, int nodeLeft, int nodeRight) { // use when s, v is available and segment tree is about sum
    if (nodeLeft == nodeRight) {
        return s[node] = v[nodeLeft];
    }
	int mid = (nodeLeft+nodeRight)/2;
    return s[node] = segment(node * 2, nodeLeft, mid) + segment(node * 2 + 1, mid + 1, nodeRight);
}
void update(int node, int idx, int nodeLeft, int nodeRight, ll dif) { //Before this you have to do v[idx]+=dif;
    if (idx < nodeLeft || nodeRight < idx) return;
    s[node] += dif;
    if (nodeLeft == nodeRight) return;
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    update(node * 2, idx, nodeLeft, mid, dif);
    update(node * 2 + 1, idx, mid + 1, nodeRight, dif);
}
ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //l and r is the range.
    if (nodeRight < l || r < nodeLeft) return 0;
    if (l <= nodeLeft && nodeRight <= r) return s[node];
    int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
    return query(node * 2, l, r, nodeLeft, mid) + query(node * 2 + 1, l, r, mid + 1, nodeRight);
}
void Solve() {
    cin >> N >> M >> K;
    M+=K;
    rep(i,0,N-1) cin >> v[i];
    segment(1,0,N-1);
    while(M--) {
        ll a, b, c; cin >> a >> b >> c;
        if(a==1) {
            b--;
            ll dif = c-v[b];
            update(1,b,0,N-1,dif);
            v[b] = c;
        }
        else {
            b--; c--;
            cout << query(1,b,c,0,N-1) << endl;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}