#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <map>
#include <deque>
#include <set>

using namespace std;
typedef long long ll;

int N, fin, Min = 0x7FFFFFFF;
vector<vector<int>> wei;
vector<vector<int>> cost; // cur and situ

int bits_(int n){
    return 1 << n;
}

int dfs(int cur, int sit){
    if(sit == fin){
        if(wei[cur][0]){
            return wei[cur][0];
        }
        return 0x7FFFFFFF;
    }

    if(cost[cur][sit] != 0){
        return cost[cur][sit];
    }

    // sit |= bits_(cur);
    // cost[cur][sit] = c;

    int result = 0x7FFFFFFF;

    for(int i = 0; i < N; i++){
        int c;
        if(wei[cur][i] && !(sit&bits_(i))){
            c = dfs(i, sit | bits_(i));
            if(c != 0x7FFFFFFF){
                result = min(result, c + wei[cur][i]);
            }
        }
    }
    cost[cur][sit] = result;
    return result;
}

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> N;
    wei.resize(N, vector<int>(N, 0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> wei[i][j];
        }
    }
    fin = (1 << N) - 1;

    cost.resize(N, vector<int>(fin+1, 0));

    cout << dfs(0,1);
    
}

/*
2098

*/