#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    size_t Q;
    cin >> Q;

    set<size_t> un;
    map<size_t, pair<size_t, size_t>> data;
    size_t total = 0;
    vector<tuple<size_t, size_t, size_t>> students;

    while(Q--){
        size_t type, x;
        cin >> type >> x;
        if(type == 1){
            auto& [count, id_sum] = data[x];
            students.emplace_back(x, 0, -1);
            size_t id = students.size();
            auto& [n, sum, pre] = students[id-1];


            if(count == 0) {
                pre = total;
                un.insert(x);
            } else if(count == 1) {
                get<1>(students[id_sum - 1]) += total - get<2>(students[id_sum-1]);
                get<2>(students[id_sum-1]) = -1;
                un.erase(x);
            }
            
            ++count;
            id_sum += id;
        }else if(type == 2){
            auto& [n, sum, pre] = students[x-1];
            if(pre != -1) {
                sum += total - pre;
                pre = -1;
                un.erase(n);
            }
            auto& [count, id_sum] = data[n];
            id_sum -= x;
            if(--count == 1) {
                get<2>(students[id_sum-1]) = total;
                un.insert(n);
            }
        }else{
            if(un.size()){
                auto& [count, id_sum] = data[*un.rbegin()];
                assert(count == 1);
                get<1>(students[id_sum-1]) += x;
                ++total;
            }
        }
    }

    for(auto x:un){
        auto& [count, id_sum] = data[x];
        assert(count == 1);
        assert(get<2>(students[id_sum-1]) != -1);
        get<1>(students[id_sum - 1]) += total - get<2>(students[id_sum-1]);
    }

    for(auto [n, sum, pre]:students)
        cout << sum << "\n";
}