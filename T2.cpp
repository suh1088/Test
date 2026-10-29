#include <bits/stdc++.h>

#define IMAX 0x7FFFFFFF
#define IMIN 0x80000000

using namespace std;
typedef long long ll;

int N, M;
vector<vector<int>> grid;

int dist(int x, int y, int a, int b){
    return abs(a-x)+abs(b-y);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    cin >> N >> M;

    grid.resize(N,vector<int>(N,0));
    int ans = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> grid[i][j];
        }
    }


    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            
            

            for(int k =0;k <= N; k++){ // k 범위
                int cost, gold=0, gn=0;
                cost = k*k+(k+1)*(k+1);
            

                for(int x = 0; x < N; x++){
                    for(int y = 0; y < N; y++){
                        if(dist(i,j,x,y) <= k && grid[x][y]){
                            gold += M;
                            gn++;
                        }
                    }
                }

                if(cost <= gold){
                    ans = max(ans, gn);
                }
            }
        }
    }

    cout << ans;
}   