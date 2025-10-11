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

int N, K;
ll pri = 0;
priority_queue<pair<int, int>> gem;
multiset<int> bags;

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> N >> K;
    
    for(int i = 0; i < N; i++){
        int m, v;
        cin >> m >> v;
        gem.push(make_pair(v, m));
    }
    for(int i = 0; i < K; i++){
        int c;
        cin >> c;
        bags.insert(c);
    }

    while(!gem.empty()){
        pair<int, int> cgem = gem.top();
        int cm = cgem.second;

        auto it = bags.lower_bound(cm);
        if(it != bags.end()){
            pri += cgem.first;
            gem.pop();
            bags.erase(it);
        }
        else{
            gem.pop();
        }
    }

    cout << pri;
}

/*
1202

정렬하고 이진탐색 할바엔 그냥 멀티셋 쓰세요 제발....
이 간단한걸 지금까지 나만 몰랐네 ㅠㅠ
*/