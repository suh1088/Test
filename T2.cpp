#include <bits/stdc++.h>

#define IMAX 0x7FFFFFFF
#define IMIN 0x80000000

using namespace std;
typedef long long ll;

int N;
vector<int> c1, c2;

vector<vector<int>> dp;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    cin >> N;

    c1.resize(N,0);
    c2.resize(N,0);
    dp.resize(N+1,vector<int>(N+1,-1));

    for(int i = 0;i<N;i++){
        cin >> c1[i];
    }
    for(int i = 0;i<N;i++){
        cin >> c2[i];
    }

    dp[0][0] = 0;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(c1[i] == c2[j]){
                dp[i+1][j+1] = max(dp[i][j], dp[i+1][j+1]);
            }
            else if(c1[i] < c2[j]){
                dp[i+1][j] = max(dp[i][j], dp[i+1][j]);
            }
            else if(c1[i] > c2[j]){
                dp[i][j+1] = max(dp[i][j] + c2[j], dp[i][j+1]);
            }
            dp[i+1][j+1] = max(dp[i][j], dp[i+1][j+1]);
        }
    }

    int ans = 0;

    for(int i=0;i<=N;i++){
        ans = max(ans, dp[i][N]);
        ans = max(ans, dp[N][i]);
    }

    cout << ans;
}   