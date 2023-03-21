#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

long long solution(vector<int> sequence) {
    int N = sequence.size();
    
    vector<long long> s1, s2;

    s1.push_back(0);
    s2.push_back(0);

    int pulse1 = 1;
    int pulse2 = -1;
    for(int i=0;i<N;i++) {
        s1.push_back(sequence.at(i) * pulse1);
        pulse1 *= -1;

        s2.push_back(sequence.at(i) * pulse2);
        pulse2 *= -1;
    }

    vector<long long> dp1(N+1), dp2(N+1);
    
    long long answer = LLONG_MIN;
    for(int i=1;i<=N;i++) {
        dp1[i] = dp1[i-1] + s1[i];
        if(dp1[i]<0) dp1[i] = 0;
        
        dp2[i] = dp2[i-1] + s2[i];
        if(dp2[i]<0) dp2[i] = 0;

        answer = max({answer, dp1[i], dp2[i]});
    }

    return answer;
}
