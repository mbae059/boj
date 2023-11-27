#include <string>
#include <vector>

using namespace std;

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) {
    int cont = 0;
    int l = 0;
    int cur = health;
    for(int i=1;i<=attacks.back().front();i++) {
        if(attacks[l].front()==i) {
            cur -= attacks[l].back();
            if(cur<=0) return -1;
            l++;
            cont = 0;
        }
        else {
            cont++;
            cur = min(cur+bandage[1], health);
            if(cont==bandage[0]) {
                cont = 0;
                cur = min(cur +bandage[2], health);
            }
        }
    }
    return cur;
    
}