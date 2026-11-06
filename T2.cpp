#include <bits/stdc++.h>

#define IMAX 0x7FFFFFFF
#define IMIN 0x80000000

using namespace std;
typedef long long ll;

int N, M;
vector<vector<int>> grid;
vector<vector<int>> sum;
vector<tuple<int, pair<int, int>, pair<int,int>>> recs;

int rec(int i, int j, int ii, int jj){
    int result = sum[ii][jj];

    if(i > 0) result -= sum[i-1][jj];
    if(j > 0) result -= sum[ii][j-1];
    if(i > 0 && j > 0) result += sum[i-1][j-1];

    return result;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    cin >> N >> M;

    grid.resize(N, vector<int>(M,0));
    sum.resize(N, vector<int>(M,0));

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int tmp;
            cin >> tmp;
            grid[i][j] = tmp>0?1:0;
        }
    }

    sum[0][0]=grid[0][0];

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(!i&&!j){
                continue;
            }
            else if(!i){
                sum[i][j]=sum[i][j-1] + grid[i][j];
            }
            else if(!j){
                sum[i][j]=sum[i-1][j] + grid[i][j];
            }
            else{
                sum[i][j]= sum[i-1][j]+ sum[i][j-1] + grid[i][j] - sum[i-1][j-1];
            }
        }
    }

    int ans = -1;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            for(int ii=i;ii<N;ii++){
                for(int jj=j;jj<M;jj++){
                    if(rec(i,j,ii,jj) == (ii-i + 1)*(jj-j+1)){
                        ans = max(ans, rec(i,j,ii,jj));
                    }
                }
            }
        }
    }

    cout << ans;
}   
