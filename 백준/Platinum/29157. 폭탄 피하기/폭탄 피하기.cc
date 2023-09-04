#include <bits/stdc++.h>
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
using ll = long long;
#define int ll
using pii = pair<int, int>;
using vi = vector<int>;
using vpii = vector<pii> ;
int N,M,K;
ll modular(ll num, ll mod) {
    num%=mod;
    return num < 0 ? num+mod : num;
}
ll modAdd(ll a, ll b, ll mod) {
    return modular(a+b, mod);
}
ll modMul(ll a, ll b, ll mod) {
    return modular(a*b, mod);
}
ll modExp(ll a, ll b, ll mod) {
    ll ret = 1;
    while(b) {
        if(b&1) ret = modMul(ret, a, mod);
        a = modMul(a,a,mod);
        b>>=1;
    }
    return ret;
}
using mii = map<int,int>;
int factorial[2000001] {};
map<pii,int> mp;
const int mod = 1e9+7;
//길 구하는 공식. (n+m)! / (n! * m!)
// n! * m! 은 페르마 소정리로 없앰
int cal(int n, int m) {
    if(n>m) swap(n,m);
    return mp[{n,m}];
}
//modMul(a,b,mod)는 a*b % mod
//modExp(a,b,mod)는 (a^b) % mod
//modAdd(a,b,mod)는 (a+b)%mod
void print(vi& v) {
    for(auto i : v) cout << i << " ";
    cout << endl;
}
void print(vpii& v) {
    for(auto p : v) {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}
vpii v; 

void getInv() {
    vpii node;
    for(auto p : v) node.pbk(p);
    node.pbk({0,0});
    node.pbk({N,M});

    for(int i=0;i<node.size();i++) {
        for(int j=i+1;j<node.size();j++) {
            auto [x1,y1] = node[i];
            auto [x2,y2] = node[j];

            int n = abs(x1-x2);
            int m = abs(y1-y2);
            if(n>m) swap(n,m);
            int p = factorial[n+m];
            int q = modMul(factorial[n], factorial[m], mod);
            q = modExp(q, mod-2,mod);
            mp[{n,m}] = modMul(p,q,mod);
        }
    }
}
int32_t main() {
    cin >> N >> M >> K;
    //폭탄 입력 받음
    for(int i=1;i<=K;i++) {
        int a, b; cin >> a >> b;
        v.pbk({a,b});
    }
    //폭탄 정렬
    sort(all(v));
    //팩토리얼 전처리
    factorial[0] = 1;
    for(int i=1;i<=2000000;i++) {
        factorial[i] = modMul(factorial[i-1], i, mod);
    }
    //역원 구하기
    getInv();
    int answer=0;
    /*포함배제 시작
    중간에 폭탄이 없으면 (0,0) (N,M)을 더함
    중간에 폭탄이 하나 있으면 (0,0) (a,b) (N,M) 을 뺌
    중간에 폭탄이 두개 있으면 (0,0) (a,b) (c,d) (N,M)을 더함
    ...
    중간에 폭탄이 홀수개 있으면 (0,0) ... (N,M)을 뺌
    중간에 폭탄이 짝수개 있으면 (0,0) ... (N,M)을 더함
    */
    for(int bits=0;bits<(1<<K);bits++) {
        //비트에 따른 폭탄
        vpii g;
        g.pbk({0,0});
        for(int i=0;i<K;i++) {
            if(bits&(1<<i)) {
                g.pbk(v[i]);
            }
        }
        g.pbk({N,M});
        /*
        폭탄을 정렬해줬기 때문에 모든 폭탄은 반드시 x1<=x2가 된다.
        y1<=y2인지는 직접 체크해줘야함
        */
        [&] () {
            int product = 1;
            for(int i=1;i<g.size();i++) {
                auto [x1,y1] = g[i-1];
                auto [x2,y2] = g[i];
                //만약 y1>y2라면 그건 처리해주면 안됨.
                if(y1>y2) return;
                assert(x1<=x2 && y1<=y2);
                product = modMul(product, cal(x2-x1,y2-y1), mod);
            }
            //비트의 기우성에 따라 빼줄지 더해줄지 계산함.
            int cnt = popcount(uint64_t(bits));
            if(cnt%2) {
                answer = modAdd(answer, -product, mod);
            }
            else {
                answer = modAdd(answer, product, mod);
            }
        } ();
    }

    cout << answer;
}
