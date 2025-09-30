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

int N, M;
bool impos= false;
vector<vector<int>> order; // 개선 가능
vector<int> wait;

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> N >> M;
    order.resize(N+1);
    wait.resize(N+1, 0);
    for(int i = 0; i < M; i++){
        int n, a, b;
        cin >> n >> a;
        for(int j = 1; j < n; j++){
            cin >> b;

            // if(find(order[a].begin(), order[a].end(), b) == order[a].end()){
            //     wait[b]++;
            // }
            wait[b]++;
            order[a].push_back(b);

            a = b;
        }
    }
    // input done

    vector<int> ans;

    queue<int> q;
    for(int i = 1; i <= N; i++){
        if(wait[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        wait[cur] = -1;
        for(int i : order[cur]){
            wait[i]--;
            if(wait[i] == 0){
                q.push(i);
            }
        }
        ans.push_back(cur);
    }
    
    if(ans.size() == N){
        for(int i : ans){
            cout << i << "\n";
        }
    }
    else{
        cout << 0;
    }
}

/*
2623


*/