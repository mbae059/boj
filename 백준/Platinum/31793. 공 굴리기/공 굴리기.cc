#include <bits/stdc++.h>
#define endl '\n'
#define int ll

using ll = long long;
using namespace std;

int pow2[63] {};

int N, Q;
void Solve() {
    cin >> N;
    cin >> Q;
    pow2[0] = 1;
    for(int i=1;i<=62;i++) pow2[i] = pow2[i-1] * 2;
    while(Q--) {
        int q; cin >> q;
        int n = N;
        while(q>pow2[n-1]) q-=pow2[n-1], n--;
        q--;
        int answer=1;
        int pre;
        if(n!=1) {
            pre = (q%2==0);
            answer = (answer<<1 | pre);
        }
        for(int i=2;i<=n-1;i++) {
            if(q%pow2[i]>=pow2[i-1]) {
                answer = (answer<<1 | !pre);
                pre = !pre;
            }
            else answer = (answer << 1 | pre);
        }
        cout << answer << endl;
    }
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
}