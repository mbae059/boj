#include <bits/stdc++.h>

using namespace std;

vector<int> getPi(const string& pattern) {
    vector<int> pi(pattern.size());
    for(int i =1,j=0;i<pattern.size();i++) {
        while(j>0 && pattern[i]!=pattern[j]) j = pi[j-1];
        if(pattern[i]==pattern[j]) pi[i] = ++j;
    }
    return pi;
}

vector<vector<pair<int, char>>> edge;
// vector<vector<vector<int>>> dp;

int dfs(int cur, char c, int j, const string& pattern, const vector<int>& pi) {
    int ret = 0;

    map<char, pair<int, bool>> mp;
    for(auto [next, nc] : edge[cur]) {
        //cache 된 값 사용
        if(!mp.contains(nc)) {
            int tj = j;
            while(tj>0 && nc!=pattern[tj]) tj = pi[tj-1];
            if(nc==pattern[tj]) {
                tj++;
                if(tj==pattern.size()) {
                    tj = pi[tj-1];
                    mp[nc] = {tj, 1};
                }
                else mp[nc] = {tj, 0};
            }
        }
        auto [nj, flag] = mp[nc];
        if(flag) ret++;
        ret += dfs(next, nc, nj, pattern, pi);
    }
    return ret;
}

void Solve() {
    int N; cin >> N;
    edge.resize(N+1);

    for(int i=1;i<=N-1;i++) {
        int a,b; cin >> a >> b;
        char c; cin >> c;
        edge[a].push_back({b,c});
    }

    string pattern; cin >> pattern;
    auto pi = getPi(pattern);
    //'0'으로 한 이유는 첫 번째에서는 무조건 X 판정이 나도록...
    cout << dfs(1, '0', 0, pattern, pi);
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}