#include <iostream>
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>
using namespace std;
 
int N, M;
char map[15][15];
int answer = 0;
 
//위 오 아 왼
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
 
//(r,c)가 중심일 때, 가능한 십자가의 최대 크기
int getSize(int r, int c){  
    int ret = 0;
    while(1){
        bool flag = true;
        for(int i = 0; i<4; i++){
            int nr = r + dr[i]*ret;
            int nc = c + dc[i]*ret;
            if(nr<0 || nc<0 || nr>=N || nc>=M || map[nr][nc] != '#'){
                flag = false;
                break;
            }
        }
        if(flag) ret++;
        else break;
    }
    return ret - 1; //ret가 0부터 시작하므로, 처음 통과하면 ret=1이 되는데 이때 십자가의 크기는 0임 ('*' 한개짜리)
}
 
//중심이 (r,c)이고 크기가 K인 십자가를 만들거나(val='#') 십자가 원상복구(val='.')
void make_cross(int r, int c, int k, int val){ 
    for(int i = 0; i<=k; i++){
        for(int j = 0; j<4; j++){
            int nr = r + dr[j]*i;
            int nc = c + dc[j]*i;
            map[nr][nc] = val;
        }
    }
}
 
int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }
 
 
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(map[i][j] == '#'){
                int step1 = getSize(i,j);
                for (int k = 0; k <= step1; k++)    //첫번째 십자가 크기 1부터 max까지, 
                {
                    make_cross(i,j,k,'*');  //첫번째 십자가 표시
 
                    for(int r = 0; r<N; r++){
                        for(int c=0; c<M; c++){
                            if(map[r][c] == '#'){
                                int step2 = getSize(r,c); //각 크기에 대해 두번째 십자가 크기 구하기
                                int width1 = 4*k + 1;
                                int width2 = 4*step2 + 1;
                                answer = max(answer, width1*width2);
                            }
                        }
                    }
                    make_cross(i,j, k, '#');    //첫번째 십자가 원상복구
 
 
                }
            } 
        
            
        }
    }
    
   
    cout << answer;
 
    return 0;
}