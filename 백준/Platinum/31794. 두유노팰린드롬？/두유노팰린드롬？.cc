#include <bits/stdc++.h>
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define endl '\n'
#define pbk push_back

using namespace std;

#define int ll
using ll = long long;
using vi = vector<int>;

string preprocess(const string& str) { //to find even palindrome as well
    string temp;
    for(auto c : str) {
        temp.pbk('#');
        temp.pbk(c);
    }
    temp.pbk('#');
    return temp;
}

vi manacher(const string& str) {
    const string tstr = preprocess(str);
    vi ret(tstr.size());

    int r = 0, p = 0; //p is the value that maximize j+A[j]
    int sz = tstr.size();

    for (int i = 0; i < sz; i++) {
        if (i <= r) {
            ret[i] = min(ret[2 * p - i], r - i);
        }
        while (i-ret[i]-1>=0 && i+ret[i]+1<sz && tstr[i-ret[i]-1]==tstr[i+ret[i]+1]) {
            ret[i]++;
        }
        if (r < i + ret[i]) {
            r = i + ret[i];
            p = i;
        }
    }
    return ret;
}

void Solve() {
    string str; cin >> str;
    int N = str.size();

    auto a = manacher(str);    

    int imos[N+1] {};

    auto inRange = [&N](int n) -> bool {
        return 1<=n && n<=N;
    };
    for(int i=0;i<a.size();i++) {
        if(a[i]%2) {
            int idx = i/2+1;
            int idx1 = idx-a[i]/2;
            int idx2 = idx+1;
            int idx3 = idx1 + a[i]+1;
            if(inRange(idx1)) imos[idx1]+=1;
            if(inRange(idx2)) imos[idx2]-=2;
            if(inRange(idx3)) imos[idx3]+=1;
        }
        else {
            int idx1 = (i-a[i])/2 + 1;
            int idx2 = i/2+1;
            int idx3 = idx2+1;
            int idx4 = idx1 + a[i] + 1;
            if(inRange(idx1)) imos[idx1]++;
            if(inRange(idx2)) imos[idx2]--;
            if(inRange(idx3)) imos[idx3]--;
            if(inRange(idx4)) imos[idx4]++;
        }
    }
    rep(i,1,N) imos[i] += imos[i-1];
    rep(i,1,N) imos[i] += imos[i-1];

    int Q; cin >> Q;
    while(Q--) {
        int x; cin >> x;
        cout << imos[x] << endl;
    }
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
}