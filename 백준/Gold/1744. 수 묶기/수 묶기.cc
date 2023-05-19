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
ll answer = 0;
vector<int> combination;
bool visited[1005];
vpll two;
vll one;

ll arr[55] {};
void chk() {
    ll sum = 0;
    for(auto i : one) {
        sum += i;
    }
    for(auto p : two) {
        sum += p.first * p.second;
    }
    answer = max(answer, sum);
}
void Solve() {
    cin >> N;
    rep(i,1,N) {
        cin >> arr[i];
        answer += arr[i];
    }
    sort(arr+1, arr+1+N);
    vi minus, plus;
    rep(i,1,N) {
        if(arr[i]<=0) minus.pbk(arr[i]);
        else plus.pbk(arr[i]);
    }
    sort(all(minus));
    sort(all(plus),greater<int>());

    ll sum = 0;
    for(int i=0;i<minus.size();) {
        if(i+1<minus.size()) {
            sum += minus[i] * minus[i+1];
            i+=2;
        }
        else {
            sum += minus[i];
            i++;
        }
    }
    for(int i=0;i<plus.size();) {
        if(plus[i]==1) {
            sum += plus[i];
            i++;
        }
        else if(i+1<plus.size() && plus[i+1]!=1) {
            sum += plus[i] * plus[i+1];
            i+=2;
        }
        else {
            sum += plus[i];
            i++;
        }
    }
    cout << max(answer, sum);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}