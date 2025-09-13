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

int T;

int main(void){
    // ios::sync_with_stdio(false); 
    // cin.tie(NULL);
    cin >> T;

    while(T--){
        int N, K, W, ans, start; // 개수, 순서규칙 개수, 목표
        cin >> N >> K;
        vector<int> time(N+1, 0); // 건축시간
        vector<int> par(N+1, 0); // 직전에 필요한 건물 수
        vector<vector<int>> order(N + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // 누적시간, 건물번호

        for(int i = 1; i <= N; i++){
            cin >> time[i];
        }

        for(int i = 0; i < K; i++){
            int a, b;
            cin >> a >> b;
            order[a].push_back(b);
            par[b]++;
            
        }

        cin >> W;

        for(int i = 1; i <= N; i++){
            if(par[i] == 0){
                par[i]++;
                pq.push(make_pair(time[i], i));
            }
        } //가장 먼저 건축 시작

        while(!pq.empty()){
            int finb = pq.top().second;
            int now = pq.top().first;
            pq.pop();

            par[finb]--;

            if(!par[finb] && finb == W){
                ans = now;
                break;
            }

            if(!par[finb]){
                for(int i : order[finb]){
                    pq.push(make_pair(now + time[i], i));
                }
            }
        }

        cout << ans << "\n";
    }
}

/*
1005

아이디어는 간단하지만 구현하는 과정이 귀찮다
*/