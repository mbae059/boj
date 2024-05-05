#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void Solve() {
    int Q; cin >> Q;
    multiset<int> ms;
    while(Q--) {
        int op, p; cin >> op;
        if(op==1) {
            cin >> p;
            ms.insert(p);
        }
        else if(op==2) {
            cin >> p;
            if(ms.contains(p)) ms.erase(ms.find(p));
        }
        else {
            int answer=0;
            if(ms.empty()) {
                cout << 0 << endl;
                continue;
            }
            auto curIter = ms.begin();
            while(true) {
                auto nextIter = ms.lower_bound(*curIter * 2);
                if(nextIter==ms.end()) break;
                answer++;
                curIter = nextIter;
            }
            answer++;
            cout << answer << endl;
        }
    }
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}