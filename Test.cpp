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

int V, E;
vector<vector<pair<int,int>>> v;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<bool> vis;

int ans = 0;

int main(void){
    // ios::sync_with_stdio(false); 
    // cin.tie(NULL);

    cin >> V >> E;
    v.resize(V+1);
    vis.resize(V+1, false);
    
    for(int i = 0; i < E; i++){
        int a, b, c;
        cin >> a >> b >> c;

        v[a].push_back(make_pair(b, c));
        v[b].push_back(make_pair(a, c));
    }

    pq.push(make_pair(0, 1));

    while(!pq.empty()){
        int cnode =pq.top().second;
        int dis = pq.top().first;
        pq.pop();
        if(vis[cnode]){
            continue;
        }

        vis[cnode] = true;
        ans += dis;
        

        for(pair<int, int> p : v[cnode]){
            if(!vis[p.first]){
                pq.push(make_pair(p.second, p.first));
            }
        }

    }

    cout << ans;
}

/*
1106

*/