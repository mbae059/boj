#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, b, ans = 0;

    cin >> a >> b;

    for (int i = 0; i <= a + b; ++i) {
        int tmp = i + 1;
        
        if (a < i) {
            tmp -= (i - a);
        }

        if (b < i) {
            tmp -= (i - b);
        }

        ans += tmp;

    }

    cout << ans;
}

